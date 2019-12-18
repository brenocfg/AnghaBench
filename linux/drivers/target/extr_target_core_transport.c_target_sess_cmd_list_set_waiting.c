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
struct se_session {int sess_tearing_down; int /*<<< orphan*/  cmd_count; int /*<<< orphan*/  sess_cmd_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  percpu_ref_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void target_sess_cmd_list_set_waiting(struct se_session *se_sess)
{
	unsigned long flags;

	spin_lock_irqsave(&se_sess->sess_cmd_lock, flags);
	se_sess->sess_tearing_down = 1;
	spin_unlock_irqrestore(&se_sess->sess_cmd_lock, flags);

	percpu_ref_kill(&se_sess->cmd_count);
}