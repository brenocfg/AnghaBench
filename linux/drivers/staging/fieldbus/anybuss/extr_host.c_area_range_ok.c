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
typedef  scalar_t__ u16 ;

/* Variables and functions */

__attribute__((used)) static bool area_range_ok(u16 addr, size_t count, u16 area_start,
			  size_t area_sz)
{
	u16 area_end_ex = area_start + area_sz;
	u16 addr_end_ex;

	if (addr < area_start)
		return false;
	if (addr >= area_end_ex)
		return false;
	addr_end_ex = addr + count;
	if (addr_end_ex > area_end_ex)
		return false;
	return true;
}