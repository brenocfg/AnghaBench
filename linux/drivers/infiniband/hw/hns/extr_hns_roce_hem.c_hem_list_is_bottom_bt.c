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

__attribute__((used)) static bool hem_list_is_bottom_bt(int hopnum, int bt_level)
{
	/*
	 * hopnum    base address table levels
	 * 0		L0(buf)
	 * 1		L0 -> buf
	 * 2		L0 -> L1 -> buf
	 * 3		L0 -> L1 -> L2 -> buf
	 */
	return bt_level >= (hopnum ? hopnum - 1 : hopnum);
}