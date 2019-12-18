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
struct iscsi_conn {scalar_t__ conn_state; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  connection_exit; } ;

/* Variables and functions */
 scalar_t__ TARG_CONN_STATE_CLEANUP_WAIT ; 
 scalar_t__ TARG_CONN_STATE_IN_LOGOUT ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  iscsit_close_connection (struct iscsi_conn*) ; 
 int /*<<< orphan*/  iscsit_handle_connection_cleanup (struct iscsi_conn*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void iscsit_take_action_for_connection_exit(struct iscsi_conn *conn, bool *conn_freed)
{
	*conn_freed = false;

	spin_lock_bh(&conn->state_lock);
	if (atomic_read(&conn->connection_exit)) {
		spin_unlock_bh(&conn->state_lock);
		return;
	}
	atomic_set(&conn->connection_exit, 1);

	if (conn->conn_state == TARG_CONN_STATE_IN_LOGOUT) {
		spin_unlock_bh(&conn->state_lock);
		iscsit_close_connection(conn);
		*conn_freed = true;
		return;
	}

	if (conn->conn_state == TARG_CONN_STATE_CLEANUP_WAIT) {
		spin_unlock_bh(&conn->state_lock);
		return;
	}

	pr_debug("Moving to TARG_CONN_STATE_CLEANUP_WAIT.\n");
	conn->conn_state = TARG_CONN_STATE_CLEANUP_WAIT;
	spin_unlock_bh(&conn->state_lock);

	iscsit_handle_connection_cleanup(conn);
	*conn_freed = true;
}