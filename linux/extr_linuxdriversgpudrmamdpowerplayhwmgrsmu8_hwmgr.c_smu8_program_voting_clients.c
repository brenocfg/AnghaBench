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
 int /*<<< orphan*/  SMU8_VOTINGRIGHTSCLIENTS_DFLT0 ; 
 int /*<<< orphan*/  cgs_write_ind_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixCG_FREQ_TRAN_VOTING_0 ; 

__attribute__((used)) static void smu8_program_voting_clients(struct pp_hwmgr *hwmgr)
{
	cgs_write_ind_register(hwmgr->device, CGS_IND_REG__SMC,
				ixCG_FREQ_TRAN_VOTING_0,
				SMU8_VOTINGRIGHTSCLIENTS_DFLT0);
}