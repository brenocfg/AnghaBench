#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct pp_smu_funcs_nv {int /*<<< orphan*/  pp_smu; int /*<<< orphan*/  (* set_voltage_by_freq ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ;} ;
struct dc {TYPE_3__* res_pool; } ;
struct TYPE_10__ {unsigned int dispclk_khz; } ;
struct TYPE_11__ {TYPE_4__ clks; } ;
struct clk_mgr_internal {TYPE_5__ base; } ;
struct TYPE_12__ {int dispclk_khz; } ;
struct clk_mgr {TYPE_6__ clks; TYPE_1__* ctx; } ;
struct TYPE_9__ {TYPE_2__* pp_smu; } ;
struct TYPE_8__ {struct pp_smu_funcs_nv nv_funcs; } ;
struct TYPE_7__ {struct dc* dc; } ;

/* Variables and functions */
 int /*<<< orphan*/  PP_SMU_NV_DISPCLK ; 
 struct clk_mgr_internal* TO_CLK_MGR_INTERNAL (struct clk_mgr*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  update_display_clk (struct clk_mgr_internal*,unsigned int) ; 

__attribute__((used)) static void request_voltage_and_program_disp_clk(struct clk_mgr *clk_mgr_base, unsigned int khz)
{
	struct clk_mgr_internal *clk_mgr = TO_CLK_MGR_INTERNAL(clk_mgr_base);
	struct dc *dc = clk_mgr_base->ctx->dc;
	struct pp_smu_funcs_nv *pp_smu = NULL;
	bool going_up = clk_mgr->base.clks.dispclk_khz < khz;

	if (dc->res_pool->pp_smu)
		pp_smu = &dc->res_pool->pp_smu->nv_funcs;

	clk_mgr->base.clks.dispclk_khz = khz;

	if (going_up && pp_smu && pp_smu->set_voltage_by_freq)
		pp_smu->set_voltage_by_freq(&pp_smu->pp_smu, PP_SMU_NV_DISPCLK, clk_mgr_base->clks.dispclk_khz / 1000);

	update_display_clk(clk_mgr, khz);

	if (!going_up && pp_smu && pp_smu->set_voltage_by_freq)
		pp_smu->set_voltage_by_freq(&pp_smu->pp_smu, PP_SMU_NV_DISPCLK, clk_mgr_base->clks.dispclk_khz / 1000);
}