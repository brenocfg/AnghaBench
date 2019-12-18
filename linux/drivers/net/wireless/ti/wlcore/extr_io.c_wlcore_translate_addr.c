#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int start; int size; } ;
struct TYPE_7__ {int start; int size; } ;
struct TYPE_6__ {int start; int size; } ;
struct TYPE_5__ {int start; int size; } ;
struct wlcore_partition_set {TYPE_4__ mem2; TYPE_3__ reg; TYPE_2__ mem; TYPE_1__ mem3; } ;
struct wl1271 {struct wlcore_partition_set curr_part; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*,int) ; 

int wlcore_translate_addr(struct wl1271 *wl, int addr)
{
	struct wlcore_partition_set *part = &wl->curr_part;

	/*
	 * To translate, first check to which window of addresses the
	 * particular address belongs. Then subtract the starting address
	 * of that window from the address. Then, add offset of the
	 * translated region.
	 *
	 * The translated regions occur next to each other in physical device
	 * memory, so just add the sizes of the preceding address regions to
	 * get the offset to the new region.
	 */
	if ((addr >= part->mem.start) &&
	    (addr < part->mem.start + part->mem.size))
		return addr - part->mem.start;
	else if ((addr >= part->reg.start) &&
		 (addr < part->reg.start + part->reg.size))
		return addr - part->reg.start + part->mem.size;
	else if ((addr >= part->mem2.start) &&
		 (addr < part->mem2.start + part->mem2.size))
		return addr - part->mem2.start + part->mem.size +
			part->reg.size;
	else if ((addr >= part->mem3.start) &&
		 (addr < part->mem3.start + part->mem3.size))
		return addr - part->mem3.start + part->mem.size +
			part->reg.size + part->mem2.size;

	WARN(1, "HW address 0x%x out of range", addr);
	return 0;
}