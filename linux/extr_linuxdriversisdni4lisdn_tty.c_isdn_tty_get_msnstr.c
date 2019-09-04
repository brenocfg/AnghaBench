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
 int ISDN_MSNLEN ; 

__attribute__((used)) static void
isdn_tty_get_msnstr(char *n, char **p)
{
	int limit = ISDN_MSNLEN - 1;

	while (((*p[0] >= '0' && *p[0] <= '9') ||
		/* Why a comma ??? */
		(*p[0] == ',') || (*p[0] == ':')) &&
	       (limit--))
		*n++ = *p[0]++;
	*n = '\0';
}