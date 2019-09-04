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
 int xmon_getchar () ; 

char *xmon_gets(char *str, int nb)
{
	char *p;
	int c;

	for (p = str; p < str + nb - 1; ) {
		c = xmon_getchar();
		if (c == -1) {
			if (p == str)
				return NULL;
			break;
		}
		*p++ = c;
		if (c == '\n')
			break;
	}
	*p = 0;
	return str;
}