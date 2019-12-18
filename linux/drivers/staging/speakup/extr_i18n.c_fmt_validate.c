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
 int compare_specifiers (char**,char**) ; 
 char* next_specifier (char*) ; 

__attribute__((used)) static bool fmt_validate(char *template, char *user)
{
	bool valid = true;
	bool still_comparing = true;
	char *template_ptr = template;
	char *user_ptr = user;

	while (still_comparing && valid) {
		template_ptr = next_specifier(template_ptr);
		user_ptr = next_specifier(user_ptr);
		if (template_ptr && user_ptr) {
			/* Both have at least one more specifier. */
			valid = compare_specifiers(&template_ptr, &user_ptr);
		} else {
			/* No more format specifiers in one or both strings. */
			still_comparing = false;
			/* See if one has more specifiers than the other. */
			if (template_ptr || user_ptr)
				valid = false;
		}
	}
	return valid;
}