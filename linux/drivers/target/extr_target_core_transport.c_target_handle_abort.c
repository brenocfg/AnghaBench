#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct se_cmd {int transport_state; int se_cmd_flags; int tag; int* t_task_cdb; int /*<<< orphan*/  cmd_kref; TYPE_2__* se_tfo; TYPE_1__* se_tmr_req; int /*<<< orphan*/  se_dev; int /*<<< orphan*/  scsi_status; } ;
struct TYPE_4__ {int (* queue_status ) (struct se_cmd*) ;int /*<<< orphan*/  (* aborted_task ) (struct se_cmd*) ;int /*<<< orphan*/  (* queue_tm_rsp ) (struct se_cmd*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  response; } ;

/* Variables and functions */
 int CMD_T_TAS ; 
 int /*<<< orphan*/  SAM_STAT_TASK_ABORTED ; 
 int SCF_ACK_KREF ; 
 int SCF_SCSI_TMR_CDB ; 
 int /*<<< orphan*/  TMR_FUNCTION_REJECTED ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ kref_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int) ; 
 int stub1 (struct se_cmd*) ; 
 int /*<<< orphan*/  stub2 (struct se_cmd*) ; 
 int /*<<< orphan*/  stub3 (struct se_cmd*) ; 
 scalar_t__ target_put_sess_cmd (struct se_cmd*) ; 
 int /*<<< orphan*/  trace_target_cmd_complete (struct se_cmd*) ; 
 int /*<<< orphan*/  transport_cmd_check_stop_to_fabric (struct se_cmd*) ; 
 int /*<<< orphan*/  transport_handle_queue_full (struct se_cmd*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void target_handle_abort(struct se_cmd *cmd)
{
	bool tas = cmd->transport_state & CMD_T_TAS;
	bool ack_kref = cmd->se_cmd_flags & SCF_ACK_KREF;
	int ret;

	pr_debug("tag %#llx: send_abort_response = %d\n", cmd->tag, tas);

	if (tas) {
		if (!(cmd->se_cmd_flags & SCF_SCSI_TMR_CDB)) {
			cmd->scsi_status = SAM_STAT_TASK_ABORTED;
			pr_debug("Setting SAM_STAT_TASK_ABORTED status for CDB: 0x%02x, ITT: 0x%08llx\n",
				 cmd->t_task_cdb[0], cmd->tag);
			trace_target_cmd_complete(cmd);
			ret = cmd->se_tfo->queue_status(cmd);
			if (ret) {
				transport_handle_queue_full(cmd, cmd->se_dev,
							    ret, false);
				return;
			}
		} else {
			cmd->se_tmr_req->response = TMR_FUNCTION_REJECTED;
			cmd->se_tfo->queue_tm_rsp(cmd);
		}
	} else {
		/*
		 * Allow the fabric driver to unmap any resources before
		 * releasing the descriptor via TFO->release_cmd().
		 */
		cmd->se_tfo->aborted_task(cmd);
		if (ack_kref)
			WARN_ON_ONCE(target_put_sess_cmd(cmd) != 0);
		/*
		 * To do: establish a unit attention condition on the I_T
		 * nexus associated with cmd. See also the paragraph "Aborting
		 * commands" in SAM.
		 */
	}

	WARN_ON_ONCE(kref_read(&cmd->cmd_kref) == 0);

	transport_cmd_check_stop_to_fabric(cmd);
}