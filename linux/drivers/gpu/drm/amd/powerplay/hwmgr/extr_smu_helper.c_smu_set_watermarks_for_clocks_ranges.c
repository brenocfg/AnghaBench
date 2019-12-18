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
typedef  void* uint8_t ;
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct watermarks {TYPE_2__** WatermarkRow; } ;
struct dm_pp_wm_sets_with_clock_ranges_soc15 {int num_wm_dmif_sets; int num_wm_mcif_sets; TYPE_3__* wm_mcif_clocks_ranges; TYPE_1__* wm_dmif_clocks_ranges; } ;
struct TYPE_6__ {int wm_min_socclk_clk_in_khz; int wm_max_socclk_clk_in_khz; int wm_min_mem_clk_in_khz; int wm_max_mem_clk_in_khz; scalar_t__ wm_set_id; } ;
struct TYPE_5__ {void* WmSetting; void* MaxUclk; void* MinUclk; void* MaxClock; void* MinClock; } ;
struct TYPE_4__ {int wm_min_dcfclk_clk_in_khz; int wm_max_dcfclk_clk_in_khz; int wm_min_mem_clk_in_khz; int wm_max_mem_clk_in_khz; scalar_t__ wm_set_id; } ;

/* Variables and functions */
 int EINVAL ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 

int smu_set_watermarks_for_clocks_ranges(void *wt_table,
		struct dm_pp_wm_sets_with_clock_ranges_soc15 *wm_with_clock_ranges)
{
	uint32_t i;
	struct watermarks *table = wt_table;

	if (!table || !wm_with_clock_ranges)
		return -EINVAL;

	if (wm_with_clock_ranges->num_wm_dmif_sets > 4 || wm_with_clock_ranges->num_wm_mcif_sets > 4)
		return -EINVAL;

	for (i = 0; i < wm_with_clock_ranges->num_wm_dmif_sets; i++) {
		table->WatermarkRow[1][i].MinClock =
			cpu_to_le16((uint16_t)
			(wm_with_clock_ranges->wm_dmif_clocks_ranges[i].wm_min_dcfclk_clk_in_khz /
			1000));
		table->WatermarkRow[1][i].MaxClock =
			cpu_to_le16((uint16_t)
			(wm_with_clock_ranges->wm_dmif_clocks_ranges[i].wm_max_dcfclk_clk_in_khz /
			1000));
		table->WatermarkRow[1][i].MinUclk =
			cpu_to_le16((uint16_t)
			(wm_with_clock_ranges->wm_dmif_clocks_ranges[i].wm_min_mem_clk_in_khz /
			1000));
		table->WatermarkRow[1][i].MaxUclk =
			cpu_to_le16((uint16_t)
			(wm_with_clock_ranges->wm_dmif_clocks_ranges[i].wm_max_mem_clk_in_khz /
			1000));
		table->WatermarkRow[1][i].WmSetting = (uint8_t)
				wm_with_clock_ranges->wm_dmif_clocks_ranges[i].wm_set_id;
	}

	for (i = 0; i < wm_with_clock_ranges->num_wm_mcif_sets; i++) {
		table->WatermarkRow[0][i].MinClock =
			cpu_to_le16((uint16_t)
			(wm_with_clock_ranges->wm_mcif_clocks_ranges[i].wm_min_socclk_clk_in_khz /
			1000));
		table->WatermarkRow[0][i].MaxClock =
			cpu_to_le16((uint16_t)
			(wm_with_clock_ranges->wm_mcif_clocks_ranges[i].wm_max_socclk_clk_in_khz /
			1000));
		table->WatermarkRow[0][i].MinUclk =
			cpu_to_le16((uint16_t)
			(wm_with_clock_ranges->wm_mcif_clocks_ranges[i].wm_min_mem_clk_in_khz /
			1000));
		table->WatermarkRow[0][i].MaxUclk =
			cpu_to_le16((uint16_t)
			(wm_with_clock_ranges->wm_mcif_clocks_ranges[i].wm_max_mem_clk_in_khz /
			1000));
		table->WatermarkRow[0][i].WmSetting = (uint8_t)
				wm_with_clock_ranges->wm_mcif_clocks_ranges[i].wm_set_id;
	}
	return 0;
}