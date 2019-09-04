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
 int /*<<< orphan*/  parse_n (char const*,unsigned long*,char const**) ; 

__attribute__((used)) static bool parse_xy(const char *s, unsigned long *x, unsigned long *y)
{
	unsigned long new_x = *x;
	unsigned long new_y = *y;

	for (;;) {
		if (!*s)
			return false;

		if (*s == ';')
			break;

		if (*s == 'x') {
			if (!parse_n(s + 1, &new_x, &s))
				return false;
		} else if (*s == 'y') {
			if (!parse_n(s + 1, &new_y, &s))
				return false;
		} else {
			return false;
		}
	}

	*x = new_x;
	*y = new_y;
	return true;
}