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
typedef  long u_long ;

/* Variables and functions */

__attribute__((used)) static int div_ratio(u_long upper, u_long lower)
{
	if ((upper<<16L) < upper)
		upper = 0xffff0000L ;
	else
		upper <<= 16L ;
	if (!lower)
		return 0;
	return (int)(upper/lower) ;
}