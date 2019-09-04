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
struct clockdomain {scalar_t__ clkdm_offs; int /*<<< orphan*/  cm_inst; int /*<<< orphan*/  prcm_partition; struct clkdm_dep* wkdep_srcs; } ;
struct clkdm_dep {scalar_t__ wkdep_usecount; TYPE_1__* clkdm; scalar_t__ clkdm_name; } ;
struct TYPE_2__ {int dep_bit; } ;

/* Variables and functions */
 scalar_t__ OMAP4_CM_STATICDEP ; 
 int /*<<< orphan*/  omap4_cminst_clear_inst_reg_bits (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int omap4_clkdm_clear_all_wkup_sleep_deps(struct clockdomain *clkdm)
{
	struct clkdm_dep *cd;
	u32 mask = 0;

	if (!clkdm->prcm_partition)
		return 0;

	for (cd = clkdm->wkdep_srcs; cd && cd->clkdm_name; cd++) {
		if (!cd->clkdm)
			continue; /* only happens if data is erroneous */

		mask |= 1 << cd->clkdm->dep_bit;
		cd->wkdep_usecount = 0;
	}

	omap4_cminst_clear_inst_reg_bits(mask, clkdm->prcm_partition,
					 clkdm->cm_inst, clkdm->clkdm_offs +
					 OMAP4_CM_STATICDEP);
	return 0;
}