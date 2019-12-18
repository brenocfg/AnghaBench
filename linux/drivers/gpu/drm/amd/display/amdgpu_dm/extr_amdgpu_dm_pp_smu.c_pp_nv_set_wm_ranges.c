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
struct smu_context {int /*<<< orphan*/  funcs; } ;
struct pp_smu_wm_range_sets {size_t num_reader_wm_sets; size_t num_writer_wm_sets; TYPE_2__* writer_wm_sets; TYPE_1__* reader_wm_sets; } ;
struct pp_smu {struct dc_context* dm; } ;
struct dm_pp_wm_sets_with_clock_ranges_soc15 {size_t num_wm_dmif_sets; size_t num_wm_mcif_sets; struct dm_pp_clock_range_for_mcif_wm_set_soc15* wm_mcif_clocks_ranges; struct dm_pp_clock_range_for_dmif_wm_set_soc15* wm_dmif_clocks_ranges; } ;
struct dm_pp_clock_range_for_mcif_wm_set_soc15 {int wm_set_id; int wm_max_socclk_clk_in_khz; int wm_min_socclk_clk_in_khz; int wm_max_mem_clk_in_khz; int wm_min_mem_clk_in_khz; } ;
struct dm_pp_clock_range_for_dmif_wm_set_soc15 {int wm_set_id; int wm_max_dcfclk_clk_in_khz; int wm_min_dcfclk_clk_in_khz; int wm_max_mem_clk_in_khz; int wm_min_mem_clk_in_khz; } ;
struct dc_context {struct amdgpu_device* driver_context; } ;
struct amdgpu_device {struct smu_context smu; } ;
typedef  size_t int32_t ;
typedef  enum pp_smu_status { ____Placeholder_pp_smu_status } pp_smu_status ;
struct TYPE_4__ {int wm_inst; int max_fill_clk_mhz; int min_fill_clk_mhz; int max_drain_clk_mhz; int min_drain_clk_mhz; } ;
struct TYPE_3__ {int wm_inst; int max_drain_clk_mhz; int min_drain_clk_mhz; int max_fill_clk_mhz; int min_fill_clk_mhz; } ;

/* Variables and functions */
 int PP_SMU_RESULT_OK ; 
 int PP_SMU_RESULT_UNSUPPORTED ; 
 void* WM_SET_A ; 
 scalar_t__ smu_set_watermarks_for_clock_ranges (struct smu_context*,struct dm_pp_wm_sets_with_clock_ranges_soc15*) ; 

enum pp_smu_status pp_nv_set_wm_ranges(struct pp_smu *pp,
		struct pp_smu_wm_range_sets *ranges)
{
	const struct dc_context *ctx = pp->dm;
	struct amdgpu_device *adev = ctx->driver_context;
	struct smu_context *smu = &adev->smu;
	struct dm_pp_wm_sets_with_clock_ranges_soc15 wm_with_clock_ranges;
	struct dm_pp_clock_range_for_dmif_wm_set_soc15 *wm_dce_clocks =
			wm_with_clock_ranges.wm_dmif_clocks_ranges;
	struct dm_pp_clock_range_for_mcif_wm_set_soc15 *wm_soc_clocks =
			wm_with_clock_ranges.wm_mcif_clocks_ranges;
	int32_t i;

	wm_with_clock_ranges.num_wm_dmif_sets = ranges->num_reader_wm_sets;
	wm_with_clock_ranges.num_wm_mcif_sets = ranges->num_writer_wm_sets;

	for (i = 0; i < wm_with_clock_ranges.num_wm_dmif_sets; i++) {
		if (ranges->reader_wm_sets[i].wm_inst > 3)
			wm_dce_clocks[i].wm_set_id = WM_SET_A;
		else
			wm_dce_clocks[i].wm_set_id =
					ranges->reader_wm_sets[i].wm_inst;
		wm_dce_clocks[i].wm_max_dcfclk_clk_in_khz =
			ranges->reader_wm_sets[i].max_drain_clk_mhz * 1000;
		wm_dce_clocks[i].wm_min_dcfclk_clk_in_khz =
			ranges->reader_wm_sets[i].min_drain_clk_mhz * 1000;
		wm_dce_clocks[i].wm_max_mem_clk_in_khz =
			ranges->reader_wm_sets[i].max_fill_clk_mhz * 1000;
		wm_dce_clocks[i].wm_min_mem_clk_in_khz =
			ranges->reader_wm_sets[i].min_fill_clk_mhz * 1000;
	}

	for (i = 0; i < wm_with_clock_ranges.num_wm_mcif_sets; i++) {
		if (ranges->writer_wm_sets[i].wm_inst > 3)
			wm_soc_clocks[i].wm_set_id = WM_SET_A;
		else
			wm_soc_clocks[i].wm_set_id =
					ranges->writer_wm_sets[i].wm_inst;
		wm_soc_clocks[i].wm_max_socclk_clk_in_khz =
			ranges->writer_wm_sets[i].max_fill_clk_mhz * 1000;
		wm_soc_clocks[i].wm_min_socclk_clk_in_khz =
			ranges->writer_wm_sets[i].min_fill_clk_mhz * 1000;
		wm_soc_clocks[i].wm_max_mem_clk_in_khz =
			ranges->writer_wm_sets[i].max_drain_clk_mhz * 1000;
		wm_soc_clocks[i].wm_min_mem_clk_in_khz =
			ranges->writer_wm_sets[i].min_drain_clk_mhz * 1000;
	}

	if (!smu->funcs)
		return PP_SMU_RESULT_UNSUPPORTED;

	/* 0: successful or smu.funcs->set_watermarks_for_clock_ranges = NULL;
	 * 1: fail
	 */
	if (smu_set_watermarks_for_clock_ranges(&adev->smu,
			&wm_with_clock_ranges))
		return PP_SMU_RESULT_UNSUPPORTED;

	return PP_SMU_RESULT_OK;
}