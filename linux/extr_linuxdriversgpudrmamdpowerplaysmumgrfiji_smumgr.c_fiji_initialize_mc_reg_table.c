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
struct pp_hwmgr {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  cgs_read_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgs_write_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmMC_SEQ_CAS_TIMING ; 
 int /*<<< orphan*/  mmMC_SEQ_CAS_TIMING_LP ; 
 int /*<<< orphan*/  mmMC_SEQ_MISC_TIMING2 ; 
 int /*<<< orphan*/  mmMC_SEQ_MISC_TIMING2_LP ; 
 int /*<<< orphan*/  mmMC_SEQ_PMG_TIMING ; 
 int /*<<< orphan*/  mmMC_SEQ_PMG_TIMING_LP ; 
 int /*<<< orphan*/  mmMC_SEQ_RAS_TIMING ; 
 int /*<<< orphan*/  mmMC_SEQ_RAS_TIMING_LP ; 
 int /*<<< orphan*/  mmMC_SEQ_RD_CTL_D0 ; 
 int /*<<< orphan*/  mmMC_SEQ_RD_CTL_D0_LP ; 
 int /*<<< orphan*/  mmMC_SEQ_RD_CTL_D1 ; 
 int /*<<< orphan*/  mmMC_SEQ_RD_CTL_D1_LP ; 
 int /*<<< orphan*/  mmMC_SEQ_WR_CTL_D1 ; 
 int /*<<< orphan*/  mmMC_SEQ_WR_CTL_D1_LP ; 

__attribute__((used)) static int fiji_initialize_mc_reg_table(struct pp_hwmgr *hwmgr)
{

	/* Program additional LP registers
	 * that are no longer programmed by VBIOS
	 */
	cgs_write_register(hwmgr->device, mmMC_SEQ_RAS_TIMING_LP,
			cgs_read_register(hwmgr->device, mmMC_SEQ_RAS_TIMING));
	cgs_write_register(hwmgr->device, mmMC_SEQ_CAS_TIMING_LP,
			cgs_read_register(hwmgr->device, mmMC_SEQ_CAS_TIMING));
	cgs_write_register(hwmgr->device, mmMC_SEQ_MISC_TIMING2_LP,
			cgs_read_register(hwmgr->device, mmMC_SEQ_MISC_TIMING2));
	cgs_write_register(hwmgr->device, mmMC_SEQ_WR_CTL_D1_LP,
			cgs_read_register(hwmgr->device, mmMC_SEQ_WR_CTL_D1));
	cgs_write_register(hwmgr->device, mmMC_SEQ_RD_CTL_D0_LP,
			cgs_read_register(hwmgr->device, mmMC_SEQ_RD_CTL_D0));
	cgs_write_register(hwmgr->device, mmMC_SEQ_RD_CTL_D1_LP,
			cgs_read_register(hwmgr->device, mmMC_SEQ_RD_CTL_D1));
	cgs_write_register(hwmgr->device, mmMC_SEQ_PMG_TIMING_LP,
			cgs_read_register(hwmgr->device, mmMC_SEQ_PMG_TIMING));

	return 0;
}