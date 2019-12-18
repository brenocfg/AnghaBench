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
 char* strchr (char*,char) ; 

__attribute__((used)) static char *next_specifier(char *input)
{
	int found = 0;
	char *next_percent = input;

	while (next_percent && !found) {
		next_percent = strchr(next_percent, '%');
		if (next_percent) {
			/* skip over doubled percent signs */
			while (next_percent[0] == '%' &&
			       next_percent[1] == '%')
				next_percent += 2;
			if (*next_percent == '%')
				found = 1;
			else if (*next_percent == '\0')
				next_percent = NULL;
		}
	}

	return next_percent;
}