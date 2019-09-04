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
typedef  int u_char ;

/* Variables and functions */

void
iecpy(u_char *dest, u_char *iestart, int ieoffset)
{
	u_char *p;
	int l;

	p = iestart + ieoffset + 2;
	l = iestart[1] - ieoffset;
	while (l--)
		*dest++ = *p++;
	*dest++ = '\0';
}