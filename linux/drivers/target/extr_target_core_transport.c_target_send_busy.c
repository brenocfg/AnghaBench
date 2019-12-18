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
struct se_cmd {int se_cmd_flags; TYPE_1__* se_tfo; int /*<<< orphan*/  scsi_status; } ;
struct TYPE_2__ {int (* queue_status ) (struct se_cmd*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SAM_STAT_BUSY ; 
 int SCF_SCSI_TMR_CDB ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int stub1 (struct se_cmd*) ; 
 int /*<<< orphan*/  trace_target_cmd_complete (struct se_cmd*) ; 

int target_send_busy(struct se_cmd *cmd)
{
	WARN_ON_ONCE(cmd->se_cmd_flags & SCF_SCSI_TMR_CDB);

	cmd->scsi_status = SAM_STAT_BUSY;
	trace_target_cmd_complete(cmd);
	return cmd->se_tfo->queue_status(cmd);
}