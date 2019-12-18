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
struct pp_smu_nv_clock_table {int dcfClockInKhz; int uClockInKhz; int fabricClockInKhz; int displayClockInKhz; int dppClockInKhz; int phyClockInKhz; int socClockInKhz; int dscClockInKhz; } ;
struct _vcs_dpi_soc_bounding_box_st {int num_states; TYPE_1__* clock_limits; } ;
struct TYPE_2__ {int dcfclk_mhz; int dram_speed_mts; int fabricclk_mhz; int dispclk_mhz; int dppclk_mhz; int phyclk_mhz; int socclk_mhz; int dscclk_mhz; } ;

/* Variables and functions */

__attribute__((used)) static void cap_soc_clocks(
		struct _vcs_dpi_soc_bounding_box_st *bb,
		struct pp_smu_nv_clock_table max_clocks)
{
	int i;

	// First pass - cap all clocks higher than the reported max
	for (i = 0; i < bb->num_states; i++) {
		if ((bb->clock_limits[i].dcfclk_mhz > (max_clocks.dcfClockInKhz / 1000))
				&& max_clocks.dcfClockInKhz != 0)
			bb->clock_limits[i].dcfclk_mhz = (max_clocks.dcfClockInKhz / 1000);

		if ((bb->clock_limits[i].dram_speed_mts > (max_clocks.uClockInKhz / 1000) * 16)
						&& max_clocks.uClockInKhz != 0)
			bb->clock_limits[i].dram_speed_mts = (max_clocks.uClockInKhz / 1000) * 16;

		if ((bb->clock_limits[i].fabricclk_mhz > (max_clocks.fabricClockInKhz / 1000))
						&& max_clocks.fabricClockInKhz != 0)
			bb->clock_limits[i].fabricclk_mhz = (max_clocks.fabricClockInKhz / 1000);

		if ((bb->clock_limits[i].dispclk_mhz > (max_clocks.displayClockInKhz / 1000))
						&& max_clocks.displayClockInKhz != 0)
			bb->clock_limits[i].dispclk_mhz = (max_clocks.displayClockInKhz / 1000);

		if ((bb->clock_limits[i].dppclk_mhz > (max_clocks.dppClockInKhz / 1000))
						&& max_clocks.dppClockInKhz != 0)
			bb->clock_limits[i].dppclk_mhz = (max_clocks.dppClockInKhz / 1000);

		if ((bb->clock_limits[i].phyclk_mhz > (max_clocks.phyClockInKhz / 1000))
						&& max_clocks.phyClockInKhz != 0)
			bb->clock_limits[i].phyclk_mhz = (max_clocks.phyClockInKhz / 1000);

		if ((bb->clock_limits[i].socclk_mhz > (max_clocks.socClockInKhz / 1000))
						&& max_clocks.socClockInKhz != 0)
			bb->clock_limits[i].socclk_mhz = (max_clocks.socClockInKhz / 1000);

		if ((bb->clock_limits[i].dscclk_mhz > (max_clocks.dscClockInKhz / 1000))
						&& max_clocks.dscClockInKhz != 0)
			bb->clock_limits[i].dscclk_mhz = (max_clocks.dscClockInKhz / 1000);
	}

	// Second pass - remove all duplicate clock states
	for (i = bb->num_states - 1; i > 1; i--) {
		bool duplicate = true;

		if (bb->clock_limits[i-1].dcfclk_mhz != bb->clock_limits[i].dcfclk_mhz)
			duplicate = false;
		if (bb->clock_limits[i-1].dispclk_mhz != bb->clock_limits[i].dispclk_mhz)
			duplicate = false;
		if (bb->clock_limits[i-1].dppclk_mhz != bb->clock_limits[i].dppclk_mhz)
			duplicate = false;
		if (bb->clock_limits[i-1].dram_speed_mts != bb->clock_limits[i].dram_speed_mts)
			duplicate = false;
		if (bb->clock_limits[i-1].dscclk_mhz != bb->clock_limits[i].dscclk_mhz)
			duplicate = false;
		if (bb->clock_limits[i-1].fabricclk_mhz != bb->clock_limits[i].fabricclk_mhz)
			duplicate = false;
		if (bb->clock_limits[i-1].phyclk_mhz != bb->clock_limits[i].phyclk_mhz)
			duplicate = false;
		if (bb->clock_limits[i-1].socclk_mhz != bb->clock_limits[i].socclk_mhz)
			duplicate = false;

		if (duplicate)
			bb->num_states--;
	}
}