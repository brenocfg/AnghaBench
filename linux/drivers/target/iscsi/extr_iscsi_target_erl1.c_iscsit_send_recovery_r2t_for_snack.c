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
struct iscsi_r2t {scalar_t__ sent_r2t; } ;
struct iscsi_cmd {int /*<<< orphan*/  conn; int /*<<< orphan*/  r2t_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISTATE_SEND_R2T ; 
 int /*<<< orphan*/  iscsit_add_cmd_to_immediate_queue (struct iscsi_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iscsit_send_recovery_r2t_for_snack(
	struct iscsi_cmd *cmd,
	struct iscsi_r2t *r2t)
{
	/*
	 * If the struct iscsi_r2t has not been sent yet, we can safely
	 * ignore retransmission
	 * of the R2TSN in question.
	 */
	spin_lock_bh(&cmd->r2t_lock);
	if (!r2t->sent_r2t) {
		spin_unlock_bh(&cmd->r2t_lock);
		return 0;
	}
	r2t->sent_r2t = 0;
	spin_unlock_bh(&cmd->r2t_lock);

	iscsit_add_cmd_to_immediate_queue(cmd, cmd->conn, ISTATE_SEND_R2T);

	return 0;
}