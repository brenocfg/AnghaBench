#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pl08x_bus_data {scalar_t__ buswidth; } ;
struct pl08x_lli_build_data {struct pl08x_bus_data dstbus; struct pl08x_bus_data srcbus; } ;
struct pl08x_driver_data {TYPE_1__* vd; } ;
struct TYPE_2__ {scalar_t__ ftdmac020; } ;

/* Variables and functions */
 int PL080_CONTROL_DST_INCR ; 
 int PL080_CONTROL_SRC_INCR ; 

__attribute__((used)) static void pl08x_choose_master_bus(struct pl08x_driver_data *pl08x,
				    struct pl08x_lli_build_data *bd,
				    struct pl08x_bus_data **mbus,
				    struct pl08x_bus_data **sbus,
				    u32 cctl)
{
	bool dst_incr;
	bool src_incr;

	/*
	 * The FTDMAC020 only supports memory-to-memory transfer, so
	 * source and destination always increase.
	 */
	if (pl08x->vd->ftdmac020) {
		dst_incr = true;
		src_incr = true;
	} else {
		dst_incr = !!(cctl & PL080_CONTROL_DST_INCR);
		src_incr = !!(cctl & PL080_CONTROL_SRC_INCR);
	}

	/*
	 * If either bus is not advancing, i.e. it is a peripheral, that
	 * one becomes master
	 */
	if (!dst_incr) {
		*mbus = &bd->dstbus;
		*sbus = &bd->srcbus;
	} else if (!src_incr) {
		*mbus = &bd->srcbus;
		*sbus = &bd->dstbus;
	} else {
		if (bd->dstbus.buswidth >= bd->srcbus.buswidth) {
			*mbus = &bd->dstbus;
			*sbus = &bd->srcbus;
		} else {
			*mbus = &bd->srcbus;
			*sbus = &bd->dstbus;
		}
	}
}