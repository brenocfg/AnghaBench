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
struct pp_smu_funcs_nv {int /*<<< orphan*/  pp_smu; int /*<<< orphan*/  (* set_pme_wa_enable ) (int /*<<< orphan*/ *) ;} ;
struct clk_mgr_internal {TYPE_1__* pp_smu; } ;
struct clk_mgr {int dummy; } ;
struct TYPE_2__ {struct pp_smu_funcs_nv nv_funcs; } ;

/* Variables and functions */
 struct clk_mgr_internal* TO_CLK_MGR_INTERNAL (struct clk_mgr*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

void dcn2_enable_pme_wa(struct clk_mgr *clk_mgr_base)
{
	struct clk_mgr_internal *clk_mgr = TO_CLK_MGR_INTERNAL(clk_mgr_base);
	struct pp_smu_funcs_nv *pp_smu = NULL;

	if (clk_mgr->pp_smu) {
		pp_smu = &clk_mgr->pp_smu->nv_funcs;

		if (pp_smu->set_pme_wa_enable)
			pp_smu->set_pme_wa_enable(&pp_smu->pp_smu);
	}
}