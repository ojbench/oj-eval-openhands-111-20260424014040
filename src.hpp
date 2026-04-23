#pragma once //include guard

#undef strtok

char *strtok(char * __restrict str, const char * __restrict delim);

char *strtok(char * __restrict str, const char * __restrict delim) {
    static char *saved_str = nullptr;
    
    // If str is not nullptr, start from str; otherwise continue from saved position
    if (str != nullptr) {
        saved_str = str;
    }
    
    // If saved_str is nullptr or points to end of string, return nullptr
    if (saved_str == nullptr || *saved_str == '\0') {
        return nullptr;
    }
    
    // Skip leading delimiters
    while (*saved_str != '\0') {
        bool is_delim = false;
        for (const char *d = delim; *d != '\0'; ++d) {
            if (*saved_str == *d) {
                is_delim = true;
                break;
            }
        }
        if (!is_delim) {
            break;
        }
        ++saved_str;
    }
    
    // If we reached end of string, return nullptr
    if (*saved_str == '\0') {
        return nullptr;
    }
    
    // Mark the start of the token
    char *token_start = saved_str;
    
    // Find the next delimiter
    while (*saved_str != '\0') {
        bool is_delim = false;
        for (const char *d = delim; *d != '\0'; ++d) {
            if (*saved_str == *d) {
                is_delim = true;
                break;
            }
        }
        if (is_delim) {
            *saved_str = '\0';  // Replace delimiter with null terminator
            ++saved_str;        // Move to next character
            return token_start;
        }
        ++saved_str;
    }
    
    // Reached end of string, return the last token
    return token_start;
}
