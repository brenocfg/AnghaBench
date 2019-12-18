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
typedef  scalar_t__ u8 ;
struct se_cmd {int se_cmd_flags; int data_length; int residual_count; } ;

/* Variables and functions */
 scalar_t__ SAM_STAT_GOOD ; 
 int SCF_TREAT_READ_AS_NORMAL ; 
 int SCF_UNDERFLOW_BIT ; 
 int /*<<< orphan*/  target_complete_cmd (struct se_cmd*,scalar_t__) ; 

void target_complete_cmd_with_length(struct se_cmd *cmd, u8 scsi_status, int length)
{
	if ((scsi_status == SAM_STAT_GOOD ||
	     cmd->se_cmd_flags & SCF_TREAT_READ_AS_NORMAL) &&
	    length < cmd->data_length) {
		if (cmd->se_cmd_flags & SCF_UNDERFLOW_BIT) {
			cmd->residual_count += cmd->data_length - length;
		} else {
			cmd->se_cmd_flags |= SCF_UNDERFLOW_BIT;
			cmd->residual_count = cmd->data_length - length;
		}

		cmd->data_length = length;
	}

	target_complete_cmd(cmd, scsi_status);
}