#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct scsi_cmnd {TYPE_2__* device; } ;
struct req_que {int num_outstanding_cmds; TYPE_3__** outstanding_cmds; } ;
struct qla_hw_data {int /*<<< orphan*/  hardware_lock; } ;
struct TYPE_9__ {scalar_t__ type; TYPE_1__* vha; } ;
typedef  TYPE_3__ srb_t ;
struct TYPE_10__ {scalar_t__ vp_idx; struct req_que* req; struct qla_hw_data* hw; } ;
typedef  TYPE_4__ scsi_qla_host_t ;
typedef  enum nexus_wait_type { ____Placeholder_nexus_wait_type } nexus_wait_type ;
struct TYPE_8__ {unsigned int id; int /*<<< orphan*/  lun; } ;
struct TYPE_7__ {scalar_t__ vp_idx; } ;

/* Variables and functions */
 struct scsi_cmnd* GET_CMD_SP (TYPE_3__*) ; 
 int QLA_SUCCESS ; 
 scalar_t__ SRB_SCSI_CMD ; 
#define  WAIT_HOST 130 
#define  WAIT_LUN 129 
#define  WAIT_TARGET 128 
 int qla2x00_eh_wait_on_command (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
qla2x00_eh_wait_for_pending_commands(scsi_qla_host_t *vha, unsigned int t,
	uint64_t l, enum nexus_wait_type type)
{
	int cnt, match, status;
	unsigned long flags;
	struct qla_hw_data *ha = vha->hw;
	struct req_que *req;
	srb_t *sp;
	struct scsi_cmnd *cmd;

	status = QLA_SUCCESS;

	spin_lock_irqsave(&ha->hardware_lock, flags);
	req = vha->req;
	for (cnt = 1; status == QLA_SUCCESS &&
		cnt < req->num_outstanding_cmds; cnt++) {
		sp = req->outstanding_cmds[cnt];
		if (!sp)
			continue;
		if (sp->type != SRB_SCSI_CMD)
			continue;
		if (vha->vp_idx != sp->vha->vp_idx)
			continue;
		match = 0;
		cmd = GET_CMD_SP(sp);
		switch (type) {
		case WAIT_HOST:
			match = 1;
			break;
		case WAIT_TARGET:
			match = cmd->device->id == t;
			break;
		case WAIT_LUN:
			match = (cmd->device->id == t &&
				cmd->device->lun == l);
			break;
		}
		if (!match)
			continue;

		spin_unlock_irqrestore(&ha->hardware_lock, flags);
		status = qla2x00_eh_wait_on_command(cmd);
		spin_lock_irqsave(&ha->hardware_lock, flags);
	}
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	return status;
}