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
struct TYPE_5__ {int hdr_first_byte; } ;
struct TYPE_6__ {TYPE_1__ common; } ;
struct TYPE_7__ {TYPE_2__ iscsi_hdr; } ;
union iscsi_cqe {TYPE_3__ cqe_common; } ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int u32 ;
struct qedi_ctx {int /*<<< orphan*/  dbg_ctx; } ;
struct qedi_conn {TYPE_4__* cls_conn; } ;
struct iscsi_task {int dummy; } ;
struct iscsi_conn {int dummy; } ;
struct TYPE_8__ {struct iscsi_conn* dd_data; } ;

/* Variables and functions */
#define  ISCSI_OPCODE_DATA_IN 134 
#define  ISCSI_OPCODE_LOGIN_RESPONSE 133 
#define  ISCSI_OPCODE_LOGOUT_RESPONSE 132 
#define  ISCSI_OPCODE_NOP_IN 131 
#define  ISCSI_OPCODE_SCSI_RESPONSE 130 
#define  ISCSI_OPCODE_TEXT_RESPONSE 129 
#define  ISCSI_OPCODE_TMF_RESPONSE 128 
 int /*<<< orphan*/  QEDI_ERR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  qedi_process_login_resp (struct qedi_ctx*,union iscsi_cqe*,struct iscsi_task*,struct qedi_conn*) ; 
 int /*<<< orphan*/  qedi_process_logout_resp (struct qedi_ctx*,union iscsi_cqe*,struct iscsi_task*,struct qedi_conn*) ; 
 int /*<<< orphan*/  qedi_process_nopin_mesg (struct qedi_ctx*,union iscsi_cqe*,struct iscsi_task*,struct qedi_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qedi_process_text_resp (struct qedi_ctx*,union iscsi_cqe*,struct iscsi_task*,struct qedi_conn*) ; 
 int /*<<< orphan*/  qedi_process_tmf_resp (struct qedi_ctx*,union iscsi_cqe*,struct iscsi_task*,struct qedi_conn*) ; 
 int /*<<< orphan*/  qedi_scsi_completion (struct qedi_ctx*,union iscsi_cqe*,struct iscsi_task*,struct iscsi_conn*) ; 

__attribute__((used)) static void qedi_mtask_completion(struct qedi_ctx *qedi,
				  union iscsi_cqe *cqe,
				  struct iscsi_task *task,
				  struct qedi_conn *conn, uint16_t que_idx)
{
	struct iscsi_conn *iscsi_conn;
	u32 hdr_opcode;

	hdr_opcode = cqe->cqe_common.iscsi_hdr.common.hdr_first_byte;
	iscsi_conn = conn->cls_conn->dd_data;

	switch (hdr_opcode) {
	case ISCSI_OPCODE_SCSI_RESPONSE:
	case ISCSI_OPCODE_DATA_IN:
		qedi_scsi_completion(qedi, cqe, task, iscsi_conn);
		break;
	case ISCSI_OPCODE_LOGIN_RESPONSE:
		qedi_process_login_resp(qedi, cqe, task, conn);
		break;
	case ISCSI_OPCODE_TMF_RESPONSE:
		qedi_process_tmf_resp(qedi, cqe, task, conn);
		break;
	case ISCSI_OPCODE_TEXT_RESPONSE:
		qedi_process_text_resp(qedi, cqe, task, conn);
		break;
	case ISCSI_OPCODE_LOGOUT_RESPONSE:
		qedi_process_logout_resp(qedi, cqe, task, conn);
		break;
	case ISCSI_OPCODE_NOP_IN:
		qedi_process_nopin_mesg(qedi, cqe, task, conn, que_idx);
		break;
	default:
		QEDI_ERR(&qedi->dbg_ctx, "unknown opcode\n");
	}
}