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

int
getcallref(u_char *p)
{
	int l, cr = 0;

	p++;			/* prot discr */
	if (*p & 0xfe)		/* wrong callref BRI only 1 octet*/
		return (-2);
	l = 0xf & *p++;		/* callref length */
	if (!l)			/* dummy CallRef */
		return (-1);
	cr = *p++;
	return (cr);
}