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
struct se_session {int /*<<< orphan*/  sess_cmd_lock; int /*<<< orphan*/  cmd_count; int /*<<< orphan*/  sess_cmd_list; scalar_t__ sess_tearing_down; } ;
struct se_cmd {int /*<<< orphan*/  se_cmd_list; int /*<<< orphan*/  se_cmd_flags; int /*<<< orphan*/  cmd_kref; struct se_session* se_sess; } ;

/* Variables and functions */
 int EINVAL ; 
 int ESHUTDOWN ; 
 int /*<<< orphan*/  SCF_ACK_KREF ; 
 int /*<<< orphan*/  kref_get_unless_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_ref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  target_put_sess_cmd (struct se_cmd*) ; 

int target_get_sess_cmd(struct se_cmd *se_cmd, bool ack_kref)
{
	struct se_session *se_sess = se_cmd->se_sess;
	unsigned long flags;
	int ret = 0;

	/*
	 * Add a second kref if the fabric caller is expecting to handle
	 * fabric acknowledgement that requires two target_put_sess_cmd()
	 * invocations before se_cmd descriptor release.
	 */
	if (ack_kref) {
		if (!kref_get_unless_zero(&se_cmd->cmd_kref))
			return -EINVAL;

		se_cmd->se_cmd_flags |= SCF_ACK_KREF;
	}

	spin_lock_irqsave(&se_sess->sess_cmd_lock, flags);
	if (se_sess->sess_tearing_down) {
		ret = -ESHUTDOWN;
		goto out;
	}
	list_add_tail(&se_cmd->se_cmd_list, &se_sess->sess_cmd_list);
	percpu_ref_get(&se_sess->cmd_count);
out:
	spin_unlock_irqrestore(&se_sess->sess_cmd_lock, flags);

	if (ret && ack_kref)
		target_put_sess_cmd(se_cmd);

	return ret;
}