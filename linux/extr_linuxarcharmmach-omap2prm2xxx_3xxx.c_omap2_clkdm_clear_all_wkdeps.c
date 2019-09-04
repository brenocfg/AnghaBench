#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {TYPE_1__* ptr; } ;
struct clockdomain {TYPE_2__ pwrdm; struct clkdm_dep* wkdep_srcs; } ;
struct clkdm_dep {scalar_t__ wkdep_usecount; TYPE_3__* clkdm; scalar_t__ clkdm_name; } ;
struct TYPE_6__ {int dep_bit; } ;
struct TYPE_4__ {int /*<<< orphan*/  prcm_offs; } ;

/* Variables and functions */
 int /*<<< orphan*/  PM_WKDEP ; 
 int /*<<< orphan*/  omap2_prm_clear_mod_reg_bits (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int omap2_clkdm_clear_all_wkdeps(struct clockdomain *clkdm)
{
	struct clkdm_dep *cd;
	u32 mask = 0;

	for (cd = clkdm->wkdep_srcs; cd && cd->clkdm_name; cd++) {
		if (!cd->clkdm)
			continue; /* only happens if data is erroneous */

		/* PRM accesses are slow, so minimize them */
		mask |= 1 << cd->clkdm->dep_bit;
		cd->wkdep_usecount = 0;
	}

	omap2_prm_clear_mod_reg_bits(mask, clkdm->pwrdm.ptr->prcm_offs,
				     PM_WKDEP);
	return 0;
}