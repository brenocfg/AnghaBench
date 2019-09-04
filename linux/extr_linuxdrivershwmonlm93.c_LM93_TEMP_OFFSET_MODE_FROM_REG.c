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
typedef  int u8 ;

/* Variables and functions */

__attribute__((used)) static int LM93_TEMP_OFFSET_MODE_FROM_REG(u8 sfc2, int nr)
{
	/* mode: 0 => 1C/bit, nonzero => 0.5C/bit */
	return sfc2 & (nr < 2 ? 0x10 : 0x20);
}