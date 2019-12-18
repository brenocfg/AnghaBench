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
typedef  int u8 ;
struct iscsi_hdr {int opcode; int /*<<< orphan*/  itt; int /*<<< orphan*/  ttt; } ;
struct iscsi_conn {int /*<<< orphan*/  conn_logout_comp; } ;
struct iscsi_cmd {int dummy; } ;
struct cxgbit_sock {struct iscsi_conn* conn; int /*<<< orphan*/  skb; } ;
struct cxgbit_lro_pdu_cb {scalar_t__ hdr; } ;

/* Variables and functions */
 int EINVAL ; 
 int HZ ; 
 int ISCSI_OPCODE_MASK ; 
#define  ISCSI_OP_LOGOUT 134 
#define  ISCSI_OP_NOOP_OUT 133 
#define  ISCSI_OP_SCSI_CMD 132 
#define  ISCSI_OP_SCSI_DATA_OUT 131 
#define  ISCSI_OP_SCSI_TMFUNC 130 
#define  ISCSI_OP_SNACK 129 
#define  ISCSI_OP_TEXT 128 
 int /*<<< orphan*/  ISCSI_REASON_BOOKMARK_NO_RESOURCES ; 
 int SECONDS_FOR_LOGOUT_COMP ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 struct iscsi_cmd* cxgbit_allocate_cmd (struct cxgbit_sock*) ; 
 int cxgbit_handle_iscsi_dataout (struct cxgbit_sock*) ; 
 int cxgbit_handle_nop_out (struct cxgbit_sock*,struct iscsi_cmd*) ; 
 int cxgbit_handle_scsi_cmd (struct cxgbit_sock*,struct iscsi_cmd*) ; 
 int cxgbit_handle_text_cmd (struct cxgbit_sock*,struct iscsi_cmd*) ; 
 struct cxgbit_lro_pdu_cb* cxgbit_rx_pdu_cb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_stack () ; 
 int iscsit_add_reject (struct iscsi_conn*,int /*<<< orphan*/ ,unsigned char*) ; 
 struct iscsi_cmd* iscsit_find_cmd_from_itt (struct iscsi_conn*,int /*<<< orphan*/ ) ; 
 int iscsit_handle_logout_cmd (struct iscsi_conn*,struct iscsi_cmd*,unsigned char*) ; 
 int iscsit_handle_snack (struct iscsi_conn*,unsigned char*) ; 
 int iscsit_handle_task_mgt_cmd (struct iscsi_conn*,struct iscsi_cmd*,unsigned char*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int cxgbit_target_rx_opcode(struct cxgbit_sock *csk)
{
	struct cxgbit_lro_pdu_cb *pdu_cb = cxgbit_rx_pdu_cb(csk->skb);
	struct iscsi_hdr *hdr = (struct iscsi_hdr *)pdu_cb->hdr;
	struct iscsi_conn *conn = csk->conn;
	struct iscsi_cmd *cmd = NULL;
	u8 opcode = (hdr->opcode & ISCSI_OPCODE_MASK);
	int ret = -EINVAL;

	switch (opcode) {
	case ISCSI_OP_SCSI_CMD:
		cmd = cxgbit_allocate_cmd(csk);
		if (!cmd)
			goto reject;

		ret = cxgbit_handle_scsi_cmd(csk, cmd);
		break;
	case ISCSI_OP_SCSI_DATA_OUT:
		ret = cxgbit_handle_iscsi_dataout(csk);
		break;
	case ISCSI_OP_NOOP_OUT:
		if (hdr->ttt == cpu_to_be32(0xFFFFFFFF)) {
			cmd = cxgbit_allocate_cmd(csk);
			if (!cmd)
				goto reject;
		}

		ret = cxgbit_handle_nop_out(csk, cmd);
		break;
	case ISCSI_OP_SCSI_TMFUNC:
		cmd = cxgbit_allocate_cmd(csk);
		if (!cmd)
			goto reject;

		ret = iscsit_handle_task_mgt_cmd(conn, cmd,
						 (unsigned char *)hdr);
		break;
	case ISCSI_OP_TEXT:
		if (hdr->ttt != cpu_to_be32(0xFFFFFFFF)) {
			cmd = iscsit_find_cmd_from_itt(conn, hdr->itt);
			if (!cmd)
				goto reject;
		} else {
			cmd = cxgbit_allocate_cmd(csk);
			if (!cmd)
				goto reject;
		}

		ret = cxgbit_handle_text_cmd(csk, cmd);
		break;
	case ISCSI_OP_LOGOUT:
		cmd = cxgbit_allocate_cmd(csk);
		if (!cmd)
			goto reject;

		ret = iscsit_handle_logout_cmd(conn, cmd, (unsigned char *)hdr);
		if (ret > 0)
			wait_for_completion_timeout(&conn->conn_logout_comp,
						    SECONDS_FOR_LOGOUT_COMP
						    * HZ);
		break;
	case ISCSI_OP_SNACK:
		ret = iscsit_handle_snack(conn, (unsigned char *)hdr);
		break;
	default:
		pr_err("Got unknown iSCSI OpCode: 0x%02x\n", opcode);
		dump_stack();
		break;
	}

	return ret;

reject:
	return iscsit_add_reject(conn, ISCSI_REASON_BOOKMARK_NO_RESOURCES,
				 (unsigned char *)hdr);
	return ret;
}