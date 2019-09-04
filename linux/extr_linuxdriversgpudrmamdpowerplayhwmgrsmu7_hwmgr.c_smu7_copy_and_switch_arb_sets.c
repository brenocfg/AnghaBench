#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
struct pp_hwmgr {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_ARB_REQ ; 
 int EINVAL ; 
 int /*<<< orphan*/  MC_ARB_BURST_TIME ; 
 int /*<<< orphan*/  MC_ARB_CG ; 
#define  MC_CG_ARB_FREQ_F0 129 
#define  MC_CG_ARB_FREQ_F1 128 
 int PHM_READ_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHM_WRITE_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STATE0 ; 
 int /*<<< orphan*/  STATE1 ; 
 int cgs_read_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgs_write_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmMC_ARB_DRAM_TIMING ; 
 int /*<<< orphan*/  mmMC_ARB_DRAM_TIMING2 ; 
 int /*<<< orphan*/  mmMC_ARB_DRAM_TIMING2_1 ; 
 int /*<<< orphan*/  mmMC_ARB_DRAM_TIMING_1 ; 
 int /*<<< orphan*/  mmMC_CG_CONFIG ; 

__attribute__((used)) static int smu7_copy_and_switch_arb_sets(struct pp_hwmgr *hwmgr,
		uint32_t arb_src, uint32_t arb_dest)
{
	uint32_t mc_arb_dram_timing;
	uint32_t mc_arb_dram_timing2;
	uint32_t burst_time;
	uint32_t mc_cg_config;

	switch (arb_src) {
	case MC_CG_ARB_FREQ_F0:
		mc_arb_dram_timing  = cgs_read_register(hwmgr->device, mmMC_ARB_DRAM_TIMING);
		mc_arb_dram_timing2 = cgs_read_register(hwmgr->device, mmMC_ARB_DRAM_TIMING2);
		burst_time = PHM_READ_FIELD(hwmgr->device, MC_ARB_BURST_TIME, STATE0);
		break;
	case MC_CG_ARB_FREQ_F1:
		mc_arb_dram_timing  = cgs_read_register(hwmgr->device, mmMC_ARB_DRAM_TIMING_1);
		mc_arb_dram_timing2 = cgs_read_register(hwmgr->device, mmMC_ARB_DRAM_TIMING2_1);
		burst_time = PHM_READ_FIELD(hwmgr->device, MC_ARB_BURST_TIME, STATE1);
		break;
	default:
		return -EINVAL;
	}

	switch (arb_dest) {
	case MC_CG_ARB_FREQ_F0:
		cgs_write_register(hwmgr->device, mmMC_ARB_DRAM_TIMING, mc_arb_dram_timing);
		cgs_write_register(hwmgr->device, mmMC_ARB_DRAM_TIMING2, mc_arb_dram_timing2);
		PHM_WRITE_FIELD(hwmgr->device, MC_ARB_BURST_TIME, STATE0, burst_time);
		break;
	case MC_CG_ARB_FREQ_F1:
		cgs_write_register(hwmgr->device, mmMC_ARB_DRAM_TIMING_1, mc_arb_dram_timing);
		cgs_write_register(hwmgr->device, mmMC_ARB_DRAM_TIMING2_1, mc_arb_dram_timing2);
		PHM_WRITE_FIELD(hwmgr->device, MC_ARB_BURST_TIME, STATE1, burst_time);
		break;
	default:
		return -EINVAL;
	}

	mc_cg_config = cgs_read_register(hwmgr->device, mmMC_CG_CONFIG);
	mc_cg_config |= 0x0000000F;
	cgs_write_register(hwmgr->device, mmMC_CG_CONFIG, mc_cg_config);
	PHM_WRITE_FIELD(hwmgr->device, MC_ARB_CG, CG_ARB_REQ, arb_dest);

	return 0;
}