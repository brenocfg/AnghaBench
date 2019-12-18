#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct dm_pp_clock_levels {size_t num_levels; int* clocks_in_khz; } ;
struct dc_context {struct amdgpu_device* driver_context; } ;
struct TYPE_9__ {TYPE_3__* funcs; } ;
struct TYPE_7__ {TYPE_1__* pp_funcs; void* pp_handle; } ;
struct amdgpu_device {TYPE_4__ smu; TYPE_2__ powerplay; } ;
struct amd_pp_simple_clock_info {int engine_max_clock; int memory_max_clock; int /*<<< orphan*/  level; int /*<<< orphan*/  member_0; } ;
struct amd_pp_clocks {int /*<<< orphan*/  member_0; } ;
typedef  enum dm_pp_clock_type { ____Placeholder_dm_pp_clock_type } dm_pp_clock_type ;
struct TYPE_8__ {scalar_t__ get_max_high_clocks; scalar_t__ get_clock_by_type; } ;
struct TYPE_6__ {scalar_t__ (* get_display_mode_validation_clocks ) (void*,struct amd_pp_simple_clock_info*) ;scalar_t__ (* get_clock_by_type ) (void*,int /*<<< orphan*/ ,struct amd_pp_clocks*) ;} ;

/* Variables and functions */
 int DM_PP_CLOCK_TYPE_ENGINE_CLK ; 
 int DM_PP_CLOCK_TYPE_MEMORY_CLK ; 
 int /*<<< orphan*/  DRM_INFO (char*,...) ; 
 int /*<<< orphan*/  dc_to_pp_clock_type (int) ; 
 int /*<<< orphan*/  get_default_clock_levels (int,struct dm_pp_clock_levels*) ; 
 int /*<<< orphan*/  pp_to_dc_clock_levels (struct amd_pp_clocks*,struct dm_pp_clock_levels*,int) ; 
 scalar_t__ smu_get_clock_by_type (TYPE_4__*,int /*<<< orphan*/ ,struct amd_pp_clocks*) ; 
 scalar_t__ smu_get_max_high_clocks (TYPE_4__*,struct amd_pp_simple_clock_info*) ; 
 scalar_t__ stub1 (void*,int /*<<< orphan*/ ,struct amd_pp_clocks*) ; 
 scalar_t__ stub2 (void*,struct amd_pp_simple_clock_info*) ; 

bool dm_pp_get_clock_levels_by_type(
		const struct dc_context *ctx,
		enum dm_pp_clock_type clk_type,
		struct dm_pp_clock_levels *dc_clks)
{
	struct amdgpu_device *adev = ctx->driver_context;
	void *pp_handle = adev->powerplay.pp_handle;
	struct amd_pp_clocks pp_clks = { 0 };
	struct amd_pp_simple_clock_info validation_clks = { 0 };
	uint32_t i;

	if (adev->powerplay.pp_funcs && adev->powerplay.pp_funcs->get_clock_by_type) {
		if (adev->powerplay.pp_funcs->get_clock_by_type(pp_handle,
			dc_to_pp_clock_type(clk_type), &pp_clks)) {
		/* Error in pplib. Provide default values. */
			return true;
		}
	} else if (adev->smu.funcs && adev->smu.funcs->get_clock_by_type) {
		if (smu_get_clock_by_type(&adev->smu,
					  dc_to_pp_clock_type(clk_type),
					  &pp_clks)) {
			get_default_clock_levels(clk_type, dc_clks);
			return true;
		}
	}

	pp_to_dc_clock_levels(&pp_clks, dc_clks, clk_type);

	if (adev->powerplay.pp_funcs && adev->powerplay.pp_funcs->get_display_mode_validation_clocks) {
		if (adev->powerplay.pp_funcs->get_display_mode_validation_clocks(
						pp_handle, &validation_clks)) {
			/* Error in pplib. Provide default values. */
			DRM_INFO("DM_PPLIB: Warning: using default validation clocks!\n");
			validation_clks.engine_max_clock = 72000;
			validation_clks.memory_max_clock = 80000;
			validation_clks.level = 0;
		}
	} else if (adev->smu.funcs && adev->smu.funcs->get_max_high_clocks) {
		if (smu_get_max_high_clocks(&adev->smu, &validation_clks)) {
			DRM_INFO("DM_PPLIB: Warning: using default validation clocks!\n");
			validation_clks.engine_max_clock = 72000;
			validation_clks.memory_max_clock = 80000;
			validation_clks.level = 0;
		}
	}

	DRM_INFO("DM_PPLIB: Validation clocks:\n");
	DRM_INFO("DM_PPLIB:    engine_max_clock: %d\n",
			validation_clks.engine_max_clock);
	DRM_INFO("DM_PPLIB:    memory_max_clock: %d\n",
			validation_clks.memory_max_clock);
	DRM_INFO("DM_PPLIB:    level           : %d\n",
			validation_clks.level);

	/* Translate 10 kHz to kHz. */
	validation_clks.engine_max_clock *= 10;
	validation_clks.memory_max_clock *= 10;

	/* Determine the highest non-boosted level from the Validation Clocks */
	if (clk_type == DM_PP_CLOCK_TYPE_ENGINE_CLK) {
		for (i = 0; i < dc_clks->num_levels; i++) {
			if (dc_clks->clocks_in_khz[i] > validation_clks.engine_max_clock) {
				/* This clock is higher the validation clock.
				 * Than means the previous one is the highest
				 * non-boosted one. */
				DRM_INFO("DM_PPLIB: reducing engine clock level from %d to %d\n",
						dc_clks->num_levels, i);
				dc_clks->num_levels = i > 0 ? i : 1;
				break;
			}
		}
	} else if (clk_type == DM_PP_CLOCK_TYPE_MEMORY_CLK) {
		for (i = 0; i < dc_clks->num_levels; i++) {
			if (dc_clks->clocks_in_khz[i] > validation_clks.memory_max_clock) {
				DRM_INFO("DM_PPLIB: reducing memory clock level from %d to %d\n",
						dc_clks->num_levels, i);
				dc_clks->num_levels = i > 0 ? i : 1;
				break;
			}
		}
	}

	return true;
}