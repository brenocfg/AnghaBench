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
struct pp_smu_wm_range_sets {int num_reader_wm_sets; int num_writer_wm_sets; TYPE_6__* writer_wm_sets; TYPE_5__* reader_wm_sets; } ;
struct TYPE_10__ {TYPE_3__* entries; } ;
struct TYPE_8__ {TYPE_1__* entries; } ;
struct clk_bw_params {TYPE_4__ clk_table; TYPE_2__ wm_table; } ;
struct TYPE_12__ {void* max_drain_clk_mhz; void* min_drain_clk_mhz; void* max_fill_clk_mhz; void* min_fill_clk_mhz; int /*<<< orphan*/  wm_inst; } ;
struct TYPE_11__ {scalar_t__ wm_type; void* max_fill_clk_mhz; void* max_drain_clk_mhz; void* min_fill_clk_mhz; void* min_drain_clk_mhz; int /*<<< orphan*/  wm_inst; } ;
struct TYPE_9__ {void* fclk_mhz; } ;
struct TYPE_7__ {scalar_t__ wm_type; int /*<<< orphan*/  wm_inst; int /*<<< orphan*/  valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 void* PP_SMU_WM_SET_RANGE_CLK_UNCONSTRAINED_MAX ; 
 void* PP_SMU_WM_SET_RANGE_CLK_UNCONSTRAINED_MIN ; 
 int /*<<< orphan*/  WM_A ; 
 int WM_SET_COUNT ; 
 scalar_t__ WM_TYPE_PSTATE_CHG ; 

void build_watermark_ranges(struct clk_bw_params *bw_params, struct pp_smu_wm_range_sets *ranges)
{
	int i, num_valid_sets;

	num_valid_sets = 0;

	for (i = 0; i < WM_SET_COUNT; i++) {
		/* skip empty entries, the smu array has no holes*/
		if (!bw_params->wm_table.entries[i].valid)
			continue;

		ranges->reader_wm_sets[num_valid_sets].wm_inst = bw_params->wm_table.entries[i].wm_inst;
		ranges->reader_wm_sets[num_valid_sets].wm_type = bw_params->wm_table.entries[i].wm_type;;
		/* We will not select WM based on dcfclk, so leave it as unconstrained */
		ranges->reader_wm_sets[num_valid_sets].min_drain_clk_mhz = PP_SMU_WM_SET_RANGE_CLK_UNCONSTRAINED_MIN;
		ranges->reader_wm_sets[num_valid_sets].max_drain_clk_mhz = PP_SMU_WM_SET_RANGE_CLK_UNCONSTRAINED_MAX;
		/* fclk wil be used to select WM*/

		if (ranges->reader_wm_sets[num_valid_sets].wm_type == WM_TYPE_PSTATE_CHG) {
			if (i == 0)
				ranges->reader_wm_sets[num_valid_sets].min_fill_clk_mhz = 0;
			else {
				/* add 1 to make it non-overlapping with next lvl */
				ranges->reader_wm_sets[num_valid_sets].min_fill_clk_mhz = bw_params->clk_table.entries[i - 1].fclk_mhz + 1;
			}
			ranges->reader_wm_sets[num_valid_sets].max_fill_clk_mhz = bw_params->clk_table.entries[i].fclk_mhz;

		} else {
			/* unconstrained for memory retraining */
			ranges->reader_wm_sets[num_valid_sets].min_fill_clk_mhz = PP_SMU_WM_SET_RANGE_CLK_UNCONSTRAINED_MIN;
			ranges->reader_wm_sets[num_valid_sets].max_fill_clk_mhz = PP_SMU_WM_SET_RANGE_CLK_UNCONSTRAINED_MAX;

			/* Modify previous watermark range to cover up to max */
			ranges->reader_wm_sets[num_valid_sets - 1].max_fill_clk_mhz = PP_SMU_WM_SET_RANGE_CLK_UNCONSTRAINED_MAX;
		}
		num_valid_sets++;
	}

	ASSERT(num_valid_sets != 0); /* Must have at least one set of valid watermarks */
	ranges->num_reader_wm_sets = num_valid_sets;

	/* modify the min and max to make sure we cover the whole range*/
	ranges->reader_wm_sets[0].min_drain_clk_mhz = PP_SMU_WM_SET_RANGE_CLK_UNCONSTRAINED_MIN;
	ranges->reader_wm_sets[0].min_fill_clk_mhz = PP_SMU_WM_SET_RANGE_CLK_UNCONSTRAINED_MIN;
	ranges->reader_wm_sets[ranges->num_reader_wm_sets - 1].max_drain_clk_mhz = PP_SMU_WM_SET_RANGE_CLK_UNCONSTRAINED_MAX;
	ranges->reader_wm_sets[ranges->num_reader_wm_sets - 1].max_fill_clk_mhz = PP_SMU_WM_SET_RANGE_CLK_UNCONSTRAINED_MAX;

	/* This is for writeback only, does not matter currently as no writeback support*/
	ranges->num_writer_wm_sets = 1;
	ranges->writer_wm_sets[0].wm_inst = WM_A;
	ranges->writer_wm_sets[0].min_fill_clk_mhz = PP_SMU_WM_SET_RANGE_CLK_UNCONSTRAINED_MIN;
	ranges->writer_wm_sets[0].max_fill_clk_mhz = PP_SMU_WM_SET_RANGE_CLK_UNCONSTRAINED_MAX;
	ranges->writer_wm_sets[0].min_drain_clk_mhz = PP_SMU_WM_SET_RANGE_CLK_UNCONSTRAINED_MIN;
	ranges->writer_wm_sets[0].max_drain_clk_mhz = PP_SMU_WM_SET_RANGE_CLK_UNCONSTRAINED_MAX;

}