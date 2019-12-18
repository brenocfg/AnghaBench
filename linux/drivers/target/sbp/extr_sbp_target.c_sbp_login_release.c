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
struct sbp_session {int /*<<< orphan*/  lock; } ;
struct sbp_login_descriptor {int /*<<< orphan*/  link; int /*<<< orphan*/  tgt_agt; struct sbp_session* sess; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct sbp_login_descriptor*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sbp_session_release (struct sbp_session*,int) ; 
 int /*<<< orphan*/  sbp_target_agent_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sbp_login_release(struct sbp_login_descriptor *login,
	bool cancel_work)
{
	struct sbp_session *sess = login->sess;

	/* FIXME: abort/wait on tasks */

	sbp_target_agent_unregister(login->tgt_agt);

	if (sess) {
		spin_lock_bh(&sess->lock);
		list_del(&login->link);
		spin_unlock_bh(&sess->lock);

		sbp_session_release(sess, cancel_work);
	}

	kfree(login);
}