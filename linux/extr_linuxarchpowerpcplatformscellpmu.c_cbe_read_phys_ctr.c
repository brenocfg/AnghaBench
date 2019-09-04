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
 int NR_PHYS_CTRS ; 
 int /*<<< orphan*/  READ_MMIO_UPPER32 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ_SHADOW_REG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  counter_value_in_latch ; 
 int /*<<< orphan*/ * pm_ctr ; 

u32 cbe_read_phys_ctr(u32 cpu, u32 phys_ctr)
{
	u32 val_in_latch, val = 0;

	if (phys_ctr < NR_PHYS_CTRS) {
		READ_SHADOW_REG(val_in_latch, counter_value_in_latch);

		/* Read the latch or the actual counter, whichever is newer. */
		if (val_in_latch & (1 << phys_ctr)) {
			READ_SHADOW_REG(val, pm_ctr[phys_ctr]);
		} else {
			READ_MMIO_UPPER32(val, pm_ctr[phys_ctr]);
		}
	}

	return val;
}