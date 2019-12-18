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
 int /*<<< orphan*/  CGS_IND_REG__SMC ; 
 int /*<<< orphan*/  PHM_WRITE_INDIRECT_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RESET_BUSY_CNT ; 
 int /*<<< orphan*/  RESET_SCLK_CNT ; 
 int /*<<< orphan*/  SCLK_PWRMGT_CNTL ; 
 int /*<<< orphan*/  cgs_write_ind_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ixCG_FREQ_TRAN_VOTING_0 ; 

__attribute__((used)) static int smu7_clear_voting_clients(struct pp_hwmgr *hwmgr)
{
	int i;

	/* Reset voting clients before disabling DPM */
	PHM_WRITE_INDIRECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			SCLK_PWRMGT_CNTL, RESET_SCLK_CNT, 1);
	PHM_WRITE_INDIRECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			SCLK_PWRMGT_CNTL, RESET_BUSY_CNT, 1);

	for (i = 0; i < 8; i++)
		cgs_write_ind_register(hwmgr->device, CGS_IND_REG__SMC,
				ixCG_FREQ_TRAN_VOTING_0 + i * 4, 0);

	return 0;
}