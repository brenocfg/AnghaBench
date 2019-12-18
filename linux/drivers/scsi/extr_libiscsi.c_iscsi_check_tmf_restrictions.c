#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct iscsi_tm {int opcode; int /*<<< orphan*/  rtt; int /*<<< orphan*/  lun; } ;
struct iscsi_task {int /*<<< orphan*/  hdr_itt; int /*<<< orphan*/  itt; TYPE_2__* sc; struct iscsi_conn* conn; } ;
struct iscsi_conn {scalar_t__ tmf_state; TYPE_3__* session; struct iscsi_tm tmhdr; } ;
struct TYPE_6__ {int /*<<< orphan*/  fast_abort; } ;
struct TYPE_5__ {TYPE_1__* device; } ;
struct TYPE_4__ {int /*<<< orphan*/  lun; } ;

/* Variables and functions */
 int EACCES ; 
 int /*<<< orphan*/  ISCSI_DBG_SESSION (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ISCSI_OPCODE_MASK ; 
 int ISCSI_OP_SCSI_DATA_OUT ; 
 int ISCSI_OP_SCSI_TMFUNC ; 
#define  ISCSI_TM_FUNC_ABORT_TASK 130 
#define  ISCSI_TM_FUNC_LOGICAL_UNIT_RESET 129 
#define  ISCSI_TM_FUNC_TARGET_WARM_RESET 128 
 int ISCSI_TM_FUNC_VALUE (struct iscsi_tm*) ; 
 int /*<<< orphan*/  KERN_INFO ; 
 scalar_t__ TMF_INITIAL ; 
 int /*<<< orphan*/  iscsi_conn_printk (int /*<<< orphan*/ ,struct iscsi_conn*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsilun_to_int (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iscsi_check_tmf_restrictions(struct iscsi_task *task, int opcode)
{
	struct iscsi_conn *conn = task->conn;
	struct iscsi_tm *tmf = &conn->tmhdr;
	u64 hdr_lun;

	if (conn->tmf_state == TMF_INITIAL)
		return 0;

	if ((tmf->opcode & ISCSI_OPCODE_MASK) != ISCSI_OP_SCSI_TMFUNC)
		return 0;

	switch (ISCSI_TM_FUNC_VALUE(tmf)) {
	case ISCSI_TM_FUNC_LOGICAL_UNIT_RESET:
		/*
		 * Allow PDUs for unrelated LUNs
		 */
		hdr_lun = scsilun_to_int(&tmf->lun);
		if (hdr_lun != task->sc->device->lun)
			return 0;
		/* fall through */
	case ISCSI_TM_FUNC_TARGET_WARM_RESET:
		/*
		 * Fail all SCSI cmd PDUs
		 */
		if (opcode != ISCSI_OP_SCSI_DATA_OUT) {
			iscsi_conn_printk(KERN_INFO, conn,
					  "task [op %x itt "
					  "0x%x/0x%x] "
					  "rejected.\n",
					  opcode, task->itt,
					  task->hdr_itt);
			return -EACCES;
		}
		/*
		 * And also all data-out PDUs in response to R2T
		 * if fast_abort is set.
		 */
		if (conn->session->fast_abort) {
			iscsi_conn_printk(KERN_INFO, conn,
					  "task [op %x itt "
					  "0x%x/0x%x] fast abort.\n",
					  opcode, task->itt,
					  task->hdr_itt);
			return -EACCES;
		}
		break;
	case ISCSI_TM_FUNC_ABORT_TASK:
		/*
		 * the caller has already checked if the task
		 * they want to abort was in the pending queue so if
		 * we are here the cmd pdu has gone out already, and
		 * we will only hit this for data-outs
		 */
		if (opcode == ISCSI_OP_SCSI_DATA_OUT &&
		    task->hdr_itt == tmf->rtt) {
			ISCSI_DBG_SESSION(conn->session,
					  "Preventing task %x/%x from sending "
					  "data-out due to abort task in "
					  "progress\n", task->itt,
					  task->hdr_itt);
			return -EACCES;
		}
		break;
	}

	return 0;
}