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
typedef  int u64 ;
struct cvm_mmc_slot {int cached_switch; } ;

/* Variables and functions */

__attribute__((used)) static bool switch_val_changed(struct cvm_mmc_slot *slot, u64 new_val)
{
	/* Match BUS_ID, HS_TIMING, BUS_WIDTH, POWER_CLASS, CLK_HI, CLK_LO */
	u64 match = 0x3001070fffffffffull;

	return (slot->cached_switch & match) != (new_val & match);
}