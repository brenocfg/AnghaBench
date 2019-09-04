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
typedef  int u32 ;

/* Variables and functions */

int mv78xx0_core_index(void)
{
	u32 extra;

	/*
	 * Read Extra Features register.
	 */
	__asm__("mrc p15, 1, %0, c15, c1, 0" : "=r" (extra));

	return !!(extra & 0x00004000);
}