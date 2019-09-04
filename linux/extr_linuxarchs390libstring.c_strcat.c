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

char *strcat(char *dest, const char *src)
{
	register int r0 asm("0") = 0;
	unsigned long dummy;
	char *ret = dest;

	asm volatile ("0: srst  %0,%1\n"
		      "   jo    0b\n"
		      "1: mvst  %0,%2\n"
		      "   jo    1b"
		      : "=&a" (dummy), "+a" (dest), "+a" (src)
		      : "d" (r0), "0" (0UL) : "cc", "memory" );
	return ret;
}