#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  memmove (char*,char*,scalar_t__) ; 
 char* skip_spaces (char*) ; 
 char* strim (char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static inline void strim_all(char *str)
{
	char *s;

	s = strim(str);
	if (s != str)
		memmove(str, s, strlen(s));
	while (*str) {
		if (!isspace(*str++))
			continue;
		if (isspace(*str)) {
			s = skip_spaces(str);
			memmove(str, s, strlen(s) + 1);
		}
	}
}