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
struct TYPE_4__ {int /*<<< orphan*/  set_wm_ranges; int /*<<< orphan*/  get_dpm_clock_table; } ;
struct TYPE_3__ {int /*<<< orphan*/  ver; } ;
struct pp_smu_funcs {TYPE_2__ rn_funcs; TYPE_1__ ctx; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PP_SMU_VER_RN ; 
 int /*<<< orphan*/  dummy_get_dpm_clock_table ; 
 int /*<<< orphan*/  dummy_set_wm_ranges ; 
 struct pp_smu_funcs* kzalloc (int,int /*<<< orphan*/ ) ; 

struct pp_smu_funcs *dcn21_pp_smu_create(struct dc_context *ctx)
{
	struct pp_smu_funcs *pp_smu = kzalloc(sizeof(*pp_smu), GFP_KERNEL);

	pp_smu->ctx.ver = PP_SMU_VER_RN;

	pp_smu->rn_funcs.get_dpm_clock_table = dummy_get_dpm_clock_table;
	pp_smu->rn_funcs.set_wm_ranges = dummy_set_wm_ranges;

	return pp_smu;
}