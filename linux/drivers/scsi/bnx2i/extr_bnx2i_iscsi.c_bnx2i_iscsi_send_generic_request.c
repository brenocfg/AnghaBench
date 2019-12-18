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
struct iscsi_task {TYPE_3__* hdr; struct bnx2i_cmd* dd_data; } ;
struct TYPE_4__ {int req_buf_size; char* req_buf; } ;
struct bnx2i_conn {TYPE_2__* cls_conn; TYPE_1__ gen_pdu; } ;
struct bnx2i_cmd {struct bnx2i_conn* conn; } ;
struct TYPE_6__ {int opcode; } ;
struct TYPE_5__ {int /*<<< orphan*/  dd_data; } ;

/* Variables and functions */
 int ISCSI_OPCODE_MASK ; 
#define  ISCSI_OP_LOGIN 132 
#define  ISCSI_OP_LOGOUT 131 
#define  ISCSI_OP_NOOP_OUT 130 
#define  ISCSI_OP_SCSI_TMFUNC 129 
#define  ISCSI_OP_TEXT 128 
 int /*<<< orphan*/  KERN_ALERT ; 
 int /*<<< orphan*/  bnx2i_iscsi_prep_generic_pdu_bd (struct bnx2i_conn*) ; 
 int /*<<< orphan*/  bnx2i_send_iscsi_login (struct bnx2i_conn*,struct iscsi_task*) ; 
 int bnx2i_send_iscsi_logout (struct bnx2i_conn*,struct iscsi_task*) ; 
 int bnx2i_send_iscsi_nopout (struct bnx2i_conn*,struct iscsi_task*,char*,int,int) ; 
 int bnx2i_send_iscsi_text (struct bnx2i_conn*,struct iscsi_task*) ; 
 int bnx2i_send_iscsi_tmf (struct bnx2i_conn*,struct iscsi_task*) ; 
 int /*<<< orphan*/  iscsi_conn_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int bnx2i_iscsi_send_generic_request(struct iscsi_task *task)
{
	struct bnx2i_cmd *cmd = task->dd_data;
	struct bnx2i_conn *bnx2i_conn = cmd->conn;
	int rc = 0;
	char *buf;
	int data_len;

	bnx2i_iscsi_prep_generic_pdu_bd(bnx2i_conn);
	switch (task->hdr->opcode & ISCSI_OPCODE_MASK) {
	case ISCSI_OP_LOGIN:
		bnx2i_send_iscsi_login(bnx2i_conn, task);
		break;
	case ISCSI_OP_NOOP_OUT:
		data_len = bnx2i_conn->gen_pdu.req_buf_size;
		buf = bnx2i_conn->gen_pdu.req_buf;
		if (data_len)
			rc = bnx2i_send_iscsi_nopout(bnx2i_conn, task,
						     buf, data_len, 1);
		else
			rc = bnx2i_send_iscsi_nopout(bnx2i_conn, task,
						     NULL, 0, 1);
		break;
	case ISCSI_OP_LOGOUT:
		rc = bnx2i_send_iscsi_logout(bnx2i_conn, task);
		break;
	case ISCSI_OP_SCSI_TMFUNC:
		rc = bnx2i_send_iscsi_tmf(bnx2i_conn, task);
		break;
	case ISCSI_OP_TEXT:
		rc = bnx2i_send_iscsi_text(bnx2i_conn, task);
		break;
	default:
		iscsi_conn_printk(KERN_ALERT, bnx2i_conn->cls_conn->dd_data,
				  "send_gen: unsupported op 0x%x\n",
				  task->hdr->opcode);
	}
	return rc;
}