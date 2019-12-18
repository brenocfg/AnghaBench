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
struct timer_list {int dummy; } ;
struct iscsi_conn {int nopin_timer_flags; int /*<<< orphan*/  nopin_timer_lock; } ;

/* Variables and functions */
 int ISCSI_TF_RUNNING ; 
 int ISCSI_TF_STOP ; 
 struct iscsi_conn* conn ; 
 struct iscsi_conn* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsit_add_nopin (struct iscsi_conn*,int) ; 
 int /*<<< orphan*/  iscsit_dec_conn_usage_count (struct iscsi_conn*) ; 
 int /*<<< orphan*/  iscsit_inc_conn_usage_count (struct iscsi_conn*) ; 
 int /*<<< orphan*/  nopin_timer ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void iscsit_handle_nopin_timeout(struct timer_list *t)
{
	struct iscsi_conn *conn = from_timer(conn, t, nopin_timer);

	iscsit_inc_conn_usage_count(conn);

	spin_lock_bh(&conn->nopin_timer_lock);
	if (conn->nopin_timer_flags & ISCSI_TF_STOP) {
		spin_unlock_bh(&conn->nopin_timer_lock);
		iscsit_dec_conn_usage_count(conn);
		return;
	}
	conn->nopin_timer_flags &= ~ISCSI_TF_RUNNING;
	spin_unlock_bh(&conn->nopin_timer_lock);

	iscsit_add_nopin(conn, 1);
	iscsit_dec_conn_usage_count(conn);
}