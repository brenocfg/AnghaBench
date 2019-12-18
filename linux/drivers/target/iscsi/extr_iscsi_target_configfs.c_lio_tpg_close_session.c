#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct se_session {struct iscsi_session* fabric_sess_ptr; } ;
struct se_portal_group {int /*<<< orphan*/  session_lock; } ;
struct iscsi_session {int time2retain_timer_flags; int /*<<< orphan*/  conn_lock; int /*<<< orphan*/  session_fall_back_to_erl0; int /*<<< orphan*/  session_reinstatement; int /*<<< orphan*/  session_logout; TYPE_1__* tpg; } ;
struct TYPE_2__ {struct se_portal_group tpg_se_tpg; } ;

/* Variables and functions */
 int ISCSI_TF_EXPIRED ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  iscsit_close_session (struct iscsi_session*) ; 
 int /*<<< orphan*/  iscsit_stop_session (struct iscsi_session*,int,int) ; 
 int /*<<< orphan*/  iscsit_stop_time2retain_timer (struct iscsi_session*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lio_tpg_close_session(struct se_session *se_sess)
{
	struct iscsi_session *sess = se_sess->fabric_sess_ptr;
	struct se_portal_group *se_tpg = &sess->tpg->tpg_se_tpg;

	spin_lock_bh(&se_tpg->session_lock);
	spin_lock(&sess->conn_lock);
	if (atomic_read(&sess->session_fall_back_to_erl0) ||
	    atomic_read(&sess->session_logout) ||
	    (sess->time2retain_timer_flags & ISCSI_TF_EXPIRED)) {
		spin_unlock(&sess->conn_lock);
		spin_unlock_bh(&se_tpg->session_lock);
		return;
	}
	atomic_set(&sess->session_reinstatement, 1);
	atomic_set(&sess->session_fall_back_to_erl0, 1);
	spin_unlock(&sess->conn_lock);

	iscsit_stop_time2retain_timer(sess);
	spin_unlock_bh(&se_tpg->session_lock);

	iscsit_stop_session(sess, 1, 1);
	iscsit_close_session(sess);
}