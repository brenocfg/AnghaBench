#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mpu_rate {long rate; int flags; unsigned long xtal; int /*<<< orphan*/  pll_rate; int /*<<< orphan*/  ckctl_val; int /*<<< orphan*/  dpllctl_val; } ;
struct clk {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  rate; } ;
struct TYPE_3__ {unsigned long rate; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_2__* ck_dpll1_p ; 
 TYPE_1__* ck_ref_p ; 
 int cpu_mask ; 
 struct mpu_rate* omap1_rate_table ; 
 int /*<<< orphan*/  omap_sram_reprogram_clock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int omap1_select_table_rate(struct clk *clk, unsigned long rate)
{
	/* Find the highest supported frequency <= rate and switch to it */
	struct mpu_rate * ptr;
	unsigned long ref_rate;

	ref_rate = ck_ref_p->rate;

	for (ptr = omap1_rate_table; ptr->rate; ptr++) {
		if (!(ptr->flags & cpu_mask))
			continue;

		if (ptr->xtal != ref_rate)
			continue;

		/* Can check only after xtal frequency check */
		if (ptr->rate <= rate)
			break;
	}

	if (!ptr->rate)
		return -EINVAL;

	/*
	 * In most cases we should not need to reprogram DPLL.
	 * Reprogramming the DPLL is tricky, it must be done from SRAM.
	 */
	omap_sram_reprogram_clock(ptr->dpllctl_val, ptr->ckctl_val);

	/* XXX Do we need to recalculate the tree below DPLL1 at this point? */
	ck_dpll1_p->rate = ptr->pll_rate;

	return 0;
}