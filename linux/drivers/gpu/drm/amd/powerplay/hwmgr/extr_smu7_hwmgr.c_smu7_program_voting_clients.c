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
struct smu7_hwmgr {int /*<<< orphan*/ * voting_rights_clients; } ;
struct pp_hwmgr {int /*<<< orphan*/  device; scalar_t__ backend; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGS_IND_REG__SMC ; 
 int /*<<< orphan*/  PHM_WRITE_INDIRECT_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RESET_BUSY_CNT ; 
 int /*<<< orphan*/  RESET_SCLK_CNT ; 
 int /*<<< orphan*/  SCLK_PWRMGT_CNTL ; 
 int /*<<< orphan*/  cgs_write_ind_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ixCG_FREQ_TRAN_VOTING_0 ; 

__attribute__((used)) static int smu7_program_voting_clients(struct pp_hwmgr *hwmgr)
{
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);
	int i;

	/* Clear reset for voting clients before enabling DPM */
	PHM_WRITE_INDIRECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			SCLK_PWRMGT_CNTL, RESET_SCLK_CNT, 0);
	PHM_WRITE_INDIRECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			SCLK_PWRMGT_CNTL, RESET_BUSY_CNT, 0);

	for (i = 0; i < 8; i++)
		cgs_write_ind_register(hwmgr->device, CGS_IND_REG__SMC,
					ixCG_FREQ_TRAN_VOTING_0 + i * 4,
					data->voting_rights_clients[i]);
	return 0;
}