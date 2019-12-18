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
struct ipr_ioa_cfg {int dummy; } ;
struct ipr_cmnd {int /*<<< orphan*/  job_step; struct ipr_ioa_cfg* ioa_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER ; 
 int /*<<< orphan*/  IPR_PCII_IOA_TRANS_TO_OPER ; 
 int IPR_RC_JOB_CONTINUE ; 
 int /*<<< orphan*/  LEAVE ; 
 int /*<<< orphan*/  ipr_ioa_bringdown_done ; 
 int /*<<< orphan*/  ipr_mask_and_clear_interrupts (struct ipr_ioa_cfg*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipr_reset_quiesce_done(struct ipr_cmnd *ipr_cmd)
{
	struct ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;

	ENTER;
	ipr_cmd->job_step = ipr_ioa_bringdown_done;
	ipr_mask_and_clear_interrupts(ioa_cfg, ~IPR_PCII_IOA_TRANS_TO_OPER);
	LEAVE;
	return IPR_RC_JOB_CONTINUE;
}