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
struct se_cmd {scalar_t__ data_direction; scalar_t__ scsi_status; } ;
struct xcopy_pt_cmd {int /*<<< orphan*/  xpt_passthrough_sem; struct se_cmd se_cmd; } ;
typedef  scalar_t__ sense_reason_t ;

/* Variables and functions */
 scalar_t__ DMA_TO_DEVICE ; 
 int EINVAL ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__) ; 
 int /*<<< orphan*/  target_execute_cmd (struct se_cmd*) ; 
 scalar_t__ transport_generic_new_cmd (struct se_cmd*) ; 
 int /*<<< orphan*/  wait_for_completion_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int target_xcopy_issue_pt_cmd(struct xcopy_pt_cmd *xpt_cmd)
{
	struct se_cmd *se_cmd = &xpt_cmd->se_cmd;
	sense_reason_t sense_rc;

	sense_rc = transport_generic_new_cmd(se_cmd);
	if (sense_rc)
		return -EINVAL;

	if (se_cmd->data_direction == DMA_TO_DEVICE)
		target_execute_cmd(se_cmd);

	wait_for_completion_interruptible(&xpt_cmd->xpt_passthrough_sem);

	pr_debug("target_xcopy_issue_pt_cmd(): SCSI status: 0x%02x\n",
			se_cmd->scsi_status);

	return (se_cmd->scsi_status) ? -EINVAL : 0;
}