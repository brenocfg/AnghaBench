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
struct device_node {int dummy; } ;
struct devbus_write_params {int ale_wr; int wr_low; int wr_high; } ;
struct devbus_read_params {int turn_off; int acc_first; int acc_next; int bus_width; int badr_skew; } ;
struct devbus {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ORION_ACC_FIRST_EXT_BIT ; 
 int ORION_ACC_FIRST_EXT_MASK ; 
 int ORION_ACC_FIRST_MASK ; 
 int ORION_ACC_FIRST_SHIFT ; 
 int ORION_ACC_NEXT_EXT_BIT ; 
 int ORION_ACC_NEXT_EXT_MASK ; 
 int ORION_ACC_NEXT_MASK ; 
 int ORION_ACC_NEXT_SHIFT ; 
 int ORION_ALE_WR_EXT_BIT ; 
 int ORION_ALE_WR_EXT_MASK ; 
 int ORION_ALE_WR_MASK ; 
 int ORION_ALE_WR_SHIFT ; 
 int ORION_BADR_SKEW_SHIFT ; 
 int ORION_DEV_WIDTH_SHIFT ; 
 int ORION_RESERVED ; 
 int ORION_TURN_OFF_EXT_BIT ; 
 int ORION_TURN_OFF_EXT_MASK ; 
 int ORION_TURN_OFF_MASK ; 
 int ORION_TURN_OFF_SHIFT ; 
 int ORION_WR_HIGH_EXT_BIT ; 
 int ORION_WR_HIGH_EXT_MASK ; 
 int ORION_WR_HIGH_MASK ; 
 int ORION_WR_HIGH_SHIFT ; 
 int ORION_WR_LOW_EXT_BIT ; 
 int ORION_WR_LOW_EXT_MASK ; 
 int ORION_WR_LOW_MASK ; 
 int ORION_WR_LOW_SHIFT ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void devbus_orion_set_timing_params(struct devbus *devbus,
					  struct device_node *node,
					  struct devbus_read_params *r,
					  struct devbus_write_params *w)
{
	u32 value;

	/*
	 * The hardware designers found it would be a good idea to
	 * split most of the values in the register into two fields:
	 * one containing all the low-order bits, and another one
	 * containing just the high-order bit. For all of those
	 * fields, we have to split the value into these two parts.
	 */
	value =	(r->turn_off   & ORION_TURN_OFF_MASK)  << ORION_TURN_OFF_SHIFT  |
		(r->acc_first  & ORION_ACC_FIRST_MASK) << ORION_ACC_FIRST_SHIFT |
		(r->acc_next   & ORION_ACC_NEXT_MASK)  << ORION_ACC_NEXT_SHIFT  |
		(w->ale_wr     & ORION_ALE_WR_MASK)    << ORION_ALE_WR_SHIFT    |
		(w->wr_low     & ORION_WR_LOW_MASK)    << ORION_WR_LOW_SHIFT    |
		(w->wr_high    & ORION_WR_HIGH_MASK)   << ORION_WR_HIGH_SHIFT   |
		r->bus_width                           << ORION_DEV_WIDTH_SHIFT |
		((r->turn_off  & ORION_TURN_OFF_EXT_MASK)  ? ORION_TURN_OFF_EXT_BIT  : 0) |
		((r->acc_first & ORION_ACC_FIRST_EXT_MASK) ? ORION_ACC_FIRST_EXT_BIT : 0) |
		((r->acc_next  & ORION_ACC_NEXT_EXT_MASK)  ? ORION_ACC_NEXT_EXT_BIT  : 0) |
		((w->ale_wr    & ORION_ALE_WR_EXT_MASK)    ? ORION_ALE_WR_EXT_BIT    : 0) |
		((w->wr_low    & ORION_WR_LOW_EXT_MASK)    ? ORION_WR_LOW_EXT_BIT    : 0) |
		((w->wr_high   & ORION_WR_HIGH_EXT_MASK)   ? ORION_WR_HIGH_EXT_BIT   : 0) |
		(r->badr_skew << ORION_BADR_SKEW_SHIFT) |
		ORION_RESERVED;

	writel(value, devbus->base);
}