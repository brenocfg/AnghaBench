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
struct iscsi_nopout {scalar_t__ itt; scalar_t__ exp_statsn; int opcode; scalar_t__ ttt; int /*<<< orphan*/  cmdsn; } ;
struct iscsi_conn {int /*<<< orphan*/  cmd_lock; int /*<<< orphan*/  conn_cmd_list; } ;
struct iscsi_cmd {int /*<<< orphan*/  i_state; int /*<<< orphan*/  i_conn_node; } ;

/* Variables and functions */
 int CMDSN_ERROR_CANNOT_RECOVER ; 
 int CMDSN_LOWER_THAN_EXP ; 
 int EINVAL ; 
 int ISCSI_OP_IMMEDIATE ; 
 int /*<<< orphan*/  ISCSI_REASON_PROTOCOL_ERROR ; 
 int /*<<< orphan*/  ISTATE_REMOVE ; 
 scalar_t__ RESERVED_ITT ; 
 int /*<<< orphan*/  be32_to_cpu (scalar_t__) ; 
 scalar_t__ cpu_to_be32 (int) ; 
 int /*<<< orphan*/  iscsit_ack_from_expstatsn (struct iscsi_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsit_add_cmd_to_immediate_queue (struct iscsi_cmd*,struct iscsi_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsit_add_cmd_to_response_queue (struct iscsi_cmd*,struct iscsi_conn*,int /*<<< orphan*/ ) ; 
 int iscsit_add_reject (struct iscsi_conn*,int /*<<< orphan*/ ,unsigned char*) ; 
 struct iscsi_cmd* iscsit_find_cmd_from_ttt (struct iscsi_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsit_free_cmd (struct iscsi_cmd*,int) ; 
 int iscsit_sequence_cmd (struct iscsi_conn*,struct iscsi_cmd*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsit_start_nopin_timer (struct iscsi_conn*) ; 
 int /*<<< orphan*/  iscsit_stop_nopin_response_timer (struct iscsi_conn*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int iscsit_process_nop_out(struct iscsi_conn *conn, struct iscsi_cmd *cmd,
			   struct iscsi_nopout *hdr)
{
	struct iscsi_cmd *cmd_p = NULL;
	int cmdsn_ret = 0;
	/*
	 * Initiator is expecting a NopIN ping reply..
	 */
	if (hdr->itt != RESERVED_ITT) {
		if (!cmd)
			return iscsit_add_reject(conn, ISCSI_REASON_PROTOCOL_ERROR,
						(unsigned char *)hdr);

		spin_lock_bh(&conn->cmd_lock);
		list_add_tail(&cmd->i_conn_node, &conn->conn_cmd_list);
		spin_unlock_bh(&conn->cmd_lock);

		iscsit_ack_from_expstatsn(conn, be32_to_cpu(hdr->exp_statsn));

		if (hdr->opcode & ISCSI_OP_IMMEDIATE) {
			iscsit_add_cmd_to_response_queue(cmd, conn,
							 cmd->i_state);
			return 0;
		}

		cmdsn_ret = iscsit_sequence_cmd(conn, cmd,
				(unsigned char *)hdr, hdr->cmdsn);
                if (cmdsn_ret == CMDSN_LOWER_THAN_EXP)
			return 0;
		if (cmdsn_ret == CMDSN_ERROR_CANNOT_RECOVER)
			return -1;

		return 0;
	}
	/*
	 * This was a response to a unsolicited NOPIN ping.
	 */
	if (hdr->ttt != cpu_to_be32(0xFFFFFFFF)) {
		cmd_p = iscsit_find_cmd_from_ttt(conn, be32_to_cpu(hdr->ttt));
		if (!cmd_p)
			return -EINVAL;

		iscsit_stop_nopin_response_timer(conn);

		cmd_p->i_state = ISTATE_REMOVE;
		iscsit_add_cmd_to_immediate_queue(cmd_p, conn, cmd_p->i_state);

		iscsit_start_nopin_timer(conn);
		return 0;
	}
	/*
	 * Otherwise, initiator is not expecting a NOPIN is response.
	 * Just ignore for now.
	 */

	if (cmd)
		iscsit_free_cmd(cmd, false);

        return 0;
}