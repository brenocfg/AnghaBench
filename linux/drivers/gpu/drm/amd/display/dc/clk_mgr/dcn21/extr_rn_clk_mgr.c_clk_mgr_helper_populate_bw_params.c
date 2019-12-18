#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct hw_asic_id {scalar_t__ vram_type; int vram_width; } ;
struct dpm_clocks {TYPE_6__* FClocks; TYPE_3__* SocClocks; TYPE_2__* MemClocks; TYPE_1__* DcfClocks; } ;
struct TYPE_16__ {TYPE_7__* entries; } ;
struct TYPE_13__ {int num_entries; TYPE_4__* entries; } ;
struct clk_bw_params {scalar_t__ vram_type; int num_channels; TYPE_8__ wm_table; TYPE_5__ clk_table; } ;
struct TYPE_15__ {int wm_inst; int valid; int /*<<< orphan*/  wm_type; int /*<<< orphan*/  pstate_latency_us; } ;
struct TYPE_14__ {scalar_t__ Freq; int /*<<< orphan*/  Vol; } ;
struct TYPE_12__ {scalar_t__ fclk_mhz; int /*<<< orphan*/  voltage; int /*<<< orphan*/  socclk_mhz; int /*<<< orphan*/  memclk_mhz; int /*<<< orphan*/  dcfclk_mhz; } ;
struct TYPE_11__ {int /*<<< orphan*/  Freq; } ;
struct TYPE_10__ {int /*<<< orphan*/  Freq; } ;
struct TYPE_9__ {int /*<<< orphan*/  Freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int DDR4_DRAM_WIDTH ; 
 int /*<<< orphan*/  LPDDR_MEM_RETRAIN_LATENCY ; 
 scalar_t__ LpDdr4MemType ; 
 int MAX_NUM_DPM_LVL ; 
 int PP_SMU_NUM_FCLK_DPM_LEVELS ; 
 size_t WM_D ; 
 int WM_SET_COUNT ; 
 int /*<<< orphan*/  WM_TYPE_PSTATE_CHG ; 
 int /*<<< orphan*/  WM_TYPE_RETRAINING ; 

void clk_mgr_helper_populate_bw_params(struct clk_bw_params *bw_params, struct dpm_clocks *clock_table, struct hw_asic_id *asic_id)
{
	int i;

	ASSERT(PP_SMU_NUM_FCLK_DPM_LEVELS <= MAX_NUM_DPM_LVL);

	for (i = 0; i < PP_SMU_NUM_FCLK_DPM_LEVELS; i++) {
		if (clock_table->FClocks[i].Freq == 0)
			break;

		bw_params->clk_table.entries[i].dcfclk_mhz = clock_table->DcfClocks[i].Freq;
		bw_params->clk_table.entries[i].fclk_mhz = clock_table->FClocks[i].Freq;
		bw_params->clk_table.entries[i].memclk_mhz = clock_table->MemClocks[i].Freq;
		bw_params->clk_table.entries[i].socclk_mhz = clock_table->SocClocks[i].Freq;
		bw_params->clk_table.entries[i].voltage = clock_table->FClocks[i].Vol;
	}
	bw_params->clk_table.num_entries = i;

	bw_params->vram_type = asic_id->vram_type;
	bw_params->num_channels = asic_id->vram_width / DDR4_DRAM_WIDTH;

	for (i = 0; i < WM_SET_COUNT; i++) {
		bw_params->wm_table.entries[i].wm_inst = i;

		if (clock_table->FClocks[i].Freq == 0) {
			bw_params->wm_table.entries[i].valid = false;
			continue;
		}

		bw_params->wm_table.entries[i].wm_type = WM_TYPE_PSTATE_CHG;
		bw_params->wm_table.entries[i].valid = true;
	}

	if (bw_params->vram_type == LpDdr4MemType) {
		/*
		 * WM set D will be re-purposed for memory retraining
		 */
		bw_params->wm_table.entries[WM_D].pstate_latency_us = LPDDR_MEM_RETRAIN_LATENCY;
		bw_params->wm_table.entries[WM_D].wm_inst = WM_D;
		bw_params->wm_table.entries[WM_D].wm_type = WM_TYPE_RETRAINING;
		bw_params->wm_table.entries[WM_D].valid = true;
	}

}