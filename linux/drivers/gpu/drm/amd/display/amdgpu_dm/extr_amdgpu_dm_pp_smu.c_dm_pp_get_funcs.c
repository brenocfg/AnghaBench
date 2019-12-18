#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct dc_context* dm; } ;
struct TYPE_10__ {int /*<<< orphan*/  set_pstate_handshake_support; int /*<<< orphan*/  get_uclk_dpm_states; int /*<<< orphan*/  get_maximum_sustainable_clocks; int /*<<< orphan*/  set_hard_min_uclk_by_freq; int /*<<< orphan*/ * set_pme_wa_enable; int /*<<< orphan*/  set_wm_ranges; int /*<<< orphan*/  set_voltage_by_freq; int /*<<< orphan*/  set_min_deep_sleep_dcfclk; int /*<<< orphan*/  set_hard_min_dcfclk_by_freq; int /*<<< orphan*/  set_display_count; TYPE_4__ pp_smu; } ;
struct TYPE_8__ {int /*<<< orphan*/  ver; } ;
struct TYPE_6__ {struct dc_context* dm; } ;
struct TYPE_7__ {int /*<<< orphan*/  set_hard_min_fclk_by_freq; int /*<<< orphan*/  set_hard_min_dcfclk_by_freq; int /*<<< orphan*/  set_min_deep_sleep_dcfclk; int /*<<< orphan*/  set_display_count; int /*<<< orphan*/  set_pme_wa_enable; int /*<<< orphan*/  set_wm_ranges; TYPE_1__ pp_smu; } ;
struct pp_smu_funcs {TYPE_5__ nv_funcs; TYPE_3__ ctx; TYPE_2__ rv_funcs; } ;
struct dc_context {int dce_version; } ;

/* Variables and functions */
#define  DCN_VERSION_1_0 130 
#define  DCN_VERSION_1_01 129 
#define  DCN_VERSION_2_0 128 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  PP_SMU_VER_NV ; 
 int /*<<< orphan*/  PP_SMU_VER_RV ; 
 int /*<<< orphan*/  pp_nv_get_maximum_sustainable_clocks ; 
 int /*<<< orphan*/  pp_nv_get_uclk_dpm_states ; 
 int /*<<< orphan*/  pp_nv_set_display_count ; 
 int /*<<< orphan*/  pp_nv_set_hard_min_dcefclk_by_freq ; 
 int /*<<< orphan*/  pp_nv_set_hard_min_uclk_by_freq ; 
 int /*<<< orphan*/  pp_nv_set_min_deep_sleep_dcfclk ; 
 int /*<<< orphan*/  pp_nv_set_pstate_handshake_support ; 
 int /*<<< orphan*/  pp_nv_set_voltage_by_freq ; 
 int /*<<< orphan*/  pp_nv_set_wm_ranges ; 
 int /*<<< orphan*/  pp_rv_set_active_display_count ; 
 int /*<<< orphan*/  pp_rv_set_hard_min_dcefclk_by_freq ; 
 int /*<<< orphan*/  pp_rv_set_hard_min_fclk_by_freq ; 
 int /*<<< orphan*/  pp_rv_set_min_deep_sleep_dcfclk ; 
 int /*<<< orphan*/  pp_rv_set_pme_wa_enable ; 
 int /*<<< orphan*/  pp_rv_set_wm_ranges ; 

void dm_pp_get_funcs(
		struct dc_context *ctx,
		struct pp_smu_funcs *funcs)
{
	switch (ctx->dce_version) {
	case DCN_VERSION_1_0:
	case DCN_VERSION_1_01:
		funcs->ctx.ver = PP_SMU_VER_RV;
		funcs->rv_funcs.pp_smu.dm = ctx;
		funcs->rv_funcs.set_wm_ranges = pp_rv_set_wm_ranges;
		funcs->rv_funcs.set_pme_wa_enable = pp_rv_set_pme_wa_enable;
		funcs->rv_funcs.set_display_count =
				pp_rv_set_active_display_count;
		funcs->rv_funcs.set_min_deep_sleep_dcfclk =
				pp_rv_set_min_deep_sleep_dcfclk;
		funcs->rv_funcs.set_hard_min_dcfclk_by_freq =
				pp_rv_set_hard_min_dcefclk_by_freq;
		funcs->rv_funcs.set_hard_min_fclk_by_freq =
				pp_rv_set_hard_min_fclk_by_freq;
		break;
#ifdef CONFIG_DRM_AMD_DC_DCN2_0
	case DCN_VERSION_2_0:
		funcs->ctx.ver = PP_SMU_VER_NV;
		funcs->nv_funcs.pp_smu.dm = ctx;
		funcs->nv_funcs.set_display_count = pp_nv_set_display_count;
		funcs->nv_funcs.set_hard_min_dcfclk_by_freq =
				pp_nv_set_hard_min_dcefclk_by_freq;
		funcs->nv_funcs.set_min_deep_sleep_dcfclk =
				pp_nv_set_min_deep_sleep_dcfclk;
		funcs->nv_funcs.set_voltage_by_freq =
				pp_nv_set_voltage_by_freq;
		funcs->nv_funcs.set_wm_ranges = pp_nv_set_wm_ranges;

		/* todo set_pme_wa_enable cause 4k@6ohz display not light up */
		funcs->nv_funcs.set_pme_wa_enable = NULL;
		/* todo debug waring message */
		funcs->nv_funcs.set_hard_min_uclk_by_freq = pp_nv_set_hard_min_uclk_by_freq;
		/* todo  compare data with window driver*/
		funcs->nv_funcs.get_maximum_sustainable_clocks = pp_nv_get_maximum_sustainable_clocks;
		/*todo  compare data with window driver */
		funcs->nv_funcs.get_uclk_dpm_states = pp_nv_get_uclk_dpm_states;
		funcs->nv_funcs.set_pstate_handshake_support = pp_nv_set_pstate_handshake_support;
		break;
#endif
	default:
		DRM_ERROR("smu version is not supported !\n");
		break;
	}
}