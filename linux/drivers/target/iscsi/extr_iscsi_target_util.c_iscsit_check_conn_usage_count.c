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
struct iscsi_conn {scalar_t__ conn_usage_count; int conn_waiting_on_uc; int /*<<< orphan*/  conn_usage_lock; int /*<<< orphan*/  conn_waiting_on_uc_comp; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void iscsit_check_conn_usage_count(struct iscsi_conn *conn)
{
	spin_lock_bh(&conn->conn_usage_lock);
	if (conn->conn_usage_count != 0) {
		conn->conn_waiting_on_uc = 1;
		spin_unlock_bh(&conn->conn_usage_lock);

		wait_for_completion(&conn->conn_waiting_on_uc_comp);
		return;
	}
	spin_unlock_bh(&conn->conn_usage_lock);
}