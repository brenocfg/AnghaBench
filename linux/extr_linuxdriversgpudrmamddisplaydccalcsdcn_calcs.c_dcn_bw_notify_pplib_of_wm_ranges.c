#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pp_smu_wm_range_sets {TYPE_4__* reader_wm_sets; TYPE_4__* writer_wm_sets; void* num_writer_wm_sets; void* num_reader_wm_sets; int /*<<< orphan*/  member_0; } ;
struct pp_smu_funcs_rv {int /*<<< orphan*/  pp_smu; int /*<<< orphan*/  (* set_wm_ranges ) (int /*<<< orphan*/ *,struct pp_smu_wm_range_sets*) ;} ;
struct TYPE_7__ {scalar_t__ pplib_wm_report_mode; } ;
struct dc {TYPE_3__ debug; TYPE_2__* dcn_soc; TYPE_1__* res_pool; } ;
struct TYPE_8__ {int min_drain_clk_khz; int max_drain_clk_khz; int min_fill_clk_khz; int max_fill_clk_khz; void* wm_inst; } ;
struct TYPE_6__ {int fabric_and_dram_bandwidth_vmin0p65; int dcfclkv_min0p65; int socclk; } ;
struct TYPE_5__ {struct pp_smu_funcs_rv* pp_smu; } ;

/* Variables and functions */
 void* WM_A ; 
 void* WM_B ; 
 void* WM_C ; 
 void* WM_D ; 
 scalar_t__ WM_REPORT_OVERRIDE ; 
 void* WM_SET_COUNT ; 
 int /*<<< orphan*/  kernel_fpu_begin () ; 
 int /*<<< orphan*/  kernel_fpu_end () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct pp_smu_wm_range_sets*) ; 

void dcn_bw_notify_pplib_of_wm_ranges(struct dc *dc)
{
	struct pp_smu_funcs_rv *pp = dc->res_pool->pp_smu;
	struct pp_smu_wm_range_sets ranges = {0};
	int min_fclk_khz, min_dcfclk_khz, socclk_khz;
	const int overdrive = 5000000; /* 5 GHz to cover Overdrive */

	if (!pp->set_wm_ranges)
		return;

	kernel_fpu_begin();
	min_fclk_khz = dc->dcn_soc->fabric_and_dram_bandwidth_vmin0p65 * 1000000 / 32;
	min_dcfclk_khz = dc->dcn_soc->dcfclkv_min0p65 * 1000;
	socclk_khz = dc->dcn_soc->socclk * 1000;
	kernel_fpu_end();

	/* Now notify PPLib/SMU about which Watermarks sets they should select
	 * depending on DPM state they are in. And update BW MGR GFX Engine and
	 * Memory clock member variables for Watermarks calculations for each
	 * Watermark Set. Only one watermark set for dcn1 due to hw bug DEGVIDCN10-254.
	 */
	/* SOCCLK does not affect anytihng but writeback for DCN so for now we dont
	 * care what the value is, hence min to overdrive level
	 */
	ranges.num_reader_wm_sets = WM_SET_COUNT;
	ranges.num_writer_wm_sets = WM_SET_COUNT;
	ranges.reader_wm_sets[0].wm_inst = WM_A;
	ranges.reader_wm_sets[0].min_drain_clk_khz = min_dcfclk_khz;
	ranges.reader_wm_sets[0].max_drain_clk_khz = overdrive;
	ranges.reader_wm_sets[0].min_fill_clk_khz = min_fclk_khz;
	ranges.reader_wm_sets[0].max_fill_clk_khz = overdrive;
	ranges.writer_wm_sets[0].wm_inst = WM_A;
	ranges.writer_wm_sets[0].min_fill_clk_khz = socclk_khz;
	ranges.writer_wm_sets[0].max_fill_clk_khz = overdrive;
	ranges.writer_wm_sets[0].min_drain_clk_khz = min_fclk_khz;
	ranges.writer_wm_sets[0].max_drain_clk_khz = overdrive;

	if (dc->debug.pplib_wm_report_mode == WM_REPORT_OVERRIDE) {
		ranges.reader_wm_sets[0].wm_inst = WM_A;
		ranges.reader_wm_sets[0].min_drain_clk_khz = 300000;
		ranges.reader_wm_sets[0].max_drain_clk_khz = 5000000;
		ranges.reader_wm_sets[0].min_fill_clk_khz = 800000;
		ranges.reader_wm_sets[0].max_fill_clk_khz = 5000000;
		ranges.writer_wm_sets[0].wm_inst = WM_A;
		ranges.writer_wm_sets[0].min_fill_clk_khz = 200000;
		ranges.writer_wm_sets[0].max_fill_clk_khz = 5000000;
		ranges.writer_wm_sets[0].min_drain_clk_khz = 800000;
		ranges.writer_wm_sets[0].max_drain_clk_khz = 5000000;
	}

	ranges.reader_wm_sets[1] = ranges.writer_wm_sets[0];
	ranges.reader_wm_sets[1].wm_inst = WM_B;

	ranges.reader_wm_sets[2] = ranges.writer_wm_sets[0];
	ranges.reader_wm_sets[2].wm_inst = WM_C;

	ranges.reader_wm_sets[3] = ranges.writer_wm_sets[0];
	ranges.reader_wm_sets[3].wm_inst = WM_D;

	/* Notify PP Lib/SMU which Watermarks to use for which clock ranges */
	pp->set_wm_ranges(&pp->pp_smu, &ranges);
}