#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct se_cmd {int transport_state; TYPE_4__* se_dev; TYPE_3__* se_tfo; int /*<<< orphan*/ * t_task_cdb; int /*<<< orphan*/  orig_fe_lun; TYPE_2__* se_sess; int /*<<< orphan*/  scsi_status; int /*<<< orphan*/  work; int /*<<< orphan*/  (* transport_complete_callback ) (struct se_cmd*,int,int*) ;} ;
typedef  int sense_reason_t ;
struct TYPE_5__ {int emulate_ua_intlck_ctrl; } ;
struct TYPE_8__ {TYPE_1__ dev_attrib; } ;
struct TYPE_7__ {int (* queue_status ) (struct se_cmd*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  se_node_acl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASCQ_2CH_PREVIOUS_RESERVATION_CONFLICT_STATUS ; 
 int CMD_T_ABORTED ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAM_STAT_BUSY ; 
 int /*<<< orphan*/  SAM_STAT_RESERVATION_CONFLICT ; 
 int /*<<< orphan*/  SAM_STAT_TASK_SET_FULL ; 
#define  TCM_ADDRESS_OUT_OF_RANGE 150 
#define  TCM_CHECK_CONDITION_ABORT_CMD 149 
#define  TCM_CHECK_CONDITION_NOT_READY 148 
#define  TCM_CHECK_CONDITION_UNIT_ATTENTION 147 
#define  TCM_COPY_TARGET_DEVICE_NOT_REACHABLE 146 
#define  TCM_INVALID_CDB_FIELD 145 
#define  TCM_INVALID_PARAMETER_LIST 144 
#define  TCM_LOGICAL_BLOCK_APP_TAG_CHECK_FAILED 143 
#define  TCM_LOGICAL_BLOCK_GUARD_CHECK_FAILED 142 
#define  TCM_LOGICAL_BLOCK_REF_TAG_CHECK_FAILED 141 
#define  TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE 140 
#define  TCM_LUN_BUSY 139 
#define  TCM_NON_EXISTENT_LUN 138 
#define  TCM_OUT_OF_RESOURCES 137 
#define  TCM_PARAMETER_LIST_LENGTH_ERROR 136 
#define  TCM_RESERVATION_CONFLICT 135 
#define  TCM_TOO_MANY_SEGMENT_DESCS 134 
#define  TCM_TOO_MANY_TARGET_DESCS 133 
#define  TCM_UNKNOWN_MODE_PAGE 132 
#define  TCM_UNSUPPORTED_SCSI_OPCODE 131 
#define  TCM_UNSUPPORTED_SEGMENT_DESC_TYPE_CODE 130 
#define  TCM_UNSUPPORTED_TARGET_DESC_TYPE_CODE 129 
#define  TCM_WRITE_PROTECTED 128 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct se_cmd*,int,int*) ; 
 int stub2 (struct se_cmd*) ; 
 int /*<<< orphan*/  target_abort_work ; 
 int /*<<< orphan*/  target_completion_wq ; 
 int /*<<< orphan*/  target_show_cmd (char*,struct se_cmd*) ; 
 int /*<<< orphan*/  target_ua_allocate_lun (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_target_cmd_complete (struct se_cmd*) ; 
 int /*<<< orphan*/  transport_cmd_check_stop_to_fabric (struct se_cmd*) ; 
 int /*<<< orphan*/  transport_complete_task_attr (struct se_cmd*) ; 
 int /*<<< orphan*/  transport_handle_queue_full (struct se_cmd*,TYPE_4__*,int,int) ; 
 int transport_send_check_condition_and_sense (struct se_cmd*,int,int /*<<< orphan*/ ) ; 

void transport_generic_request_failure(struct se_cmd *cmd,
		sense_reason_t sense_reason)
{
	int ret = 0, post_ret;

	pr_debug("-----[ Storage Engine Exception; sense_reason %d\n",
		 sense_reason);
	target_show_cmd("-----[ ", cmd);

	/*
	 * For SAM Task Attribute emulation for failed struct se_cmd
	 */
	transport_complete_task_attr(cmd);

	if (cmd->transport_complete_callback)
		cmd->transport_complete_callback(cmd, false, &post_ret);

	if (cmd->transport_state & CMD_T_ABORTED) {
		INIT_WORK(&cmd->work, target_abort_work);
		queue_work(target_completion_wq, &cmd->work);
		return;
	}

	switch (sense_reason) {
	case TCM_NON_EXISTENT_LUN:
	case TCM_UNSUPPORTED_SCSI_OPCODE:
	case TCM_INVALID_CDB_FIELD:
	case TCM_INVALID_PARAMETER_LIST:
	case TCM_PARAMETER_LIST_LENGTH_ERROR:
	case TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE:
	case TCM_UNKNOWN_MODE_PAGE:
	case TCM_WRITE_PROTECTED:
	case TCM_ADDRESS_OUT_OF_RANGE:
	case TCM_CHECK_CONDITION_ABORT_CMD:
	case TCM_CHECK_CONDITION_UNIT_ATTENTION:
	case TCM_CHECK_CONDITION_NOT_READY:
	case TCM_LOGICAL_BLOCK_GUARD_CHECK_FAILED:
	case TCM_LOGICAL_BLOCK_APP_TAG_CHECK_FAILED:
	case TCM_LOGICAL_BLOCK_REF_TAG_CHECK_FAILED:
	case TCM_COPY_TARGET_DEVICE_NOT_REACHABLE:
	case TCM_TOO_MANY_TARGET_DESCS:
	case TCM_UNSUPPORTED_TARGET_DESC_TYPE_CODE:
	case TCM_TOO_MANY_SEGMENT_DESCS:
	case TCM_UNSUPPORTED_SEGMENT_DESC_TYPE_CODE:
		break;
	case TCM_OUT_OF_RESOURCES:
		cmd->scsi_status = SAM_STAT_TASK_SET_FULL;
		goto queue_status;
	case TCM_LUN_BUSY:
		cmd->scsi_status = SAM_STAT_BUSY;
		goto queue_status;
	case TCM_RESERVATION_CONFLICT:
		/*
		 * No SENSE Data payload for this case, set SCSI Status
		 * and queue the response to $FABRIC_MOD.
		 *
		 * Uses linux/include/scsi/scsi.h SAM status codes defs
		 */
		cmd->scsi_status = SAM_STAT_RESERVATION_CONFLICT;
		/*
		 * For UA Interlock Code 11b, a RESERVATION CONFLICT will
		 * establish a UNIT ATTENTION with PREVIOUS RESERVATION
		 * CONFLICT STATUS.
		 *
		 * See spc4r17, section 7.4.6 Control Mode Page, Table 349
		 */
		if (cmd->se_sess &&
		    cmd->se_dev->dev_attrib.emulate_ua_intlck_ctrl == 2) {
			target_ua_allocate_lun(cmd->se_sess->se_node_acl,
					       cmd->orig_fe_lun, 0x2C,
					ASCQ_2CH_PREVIOUS_RESERVATION_CONFLICT_STATUS);
		}

		goto queue_status;
	default:
		pr_err("Unknown transport error for CDB 0x%02x: %d\n",
			cmd->t_task_cdb[0], sense_reason);
		sense_reason = TCM_UNSUPPORTED_SCSI_OPCODE;
		break;
	}

	ret = transport_send_check_condition_and_sense(cmd, sense_reason, 0);
	if (ret)
		goto queue_full;

check_stop:
	transport_cmd_check_stop_to_fabric(cmd);
	return;

queue_status:
	trace_target_cmd_complete(cmd);
	ret = cmd->se_tfo->queue_status(cmd);
	if (!ret)
		goto check_stop;
queue_full:
	transport_handle_queue_full(cmd, cmd->se_dev, ret, false);
}