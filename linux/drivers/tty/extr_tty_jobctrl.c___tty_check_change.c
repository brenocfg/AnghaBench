#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int /*<<< orphan*/  ctrl_lock; struct pid* pgrp; } ;
struct pid {int dummy; } ;
struct TYPE_5__ {TYPE_1__* signal; } ;
struct TYPE_4__ {struct tty_struct* tty; } ;

/* Variables and functions */
 int EIO ; 
 int ERESTARTSYS ; 
 int SIGTTIN ; 
 int /*<<< orphan*/  TIF_SIGPENDING ; 
 TYPE_2__* current ; 
 scalar_t__ is_current_pgrp_orphaned () ; 
 scalar_t__ is_ignored (int) ; 
 int /*<<< orphan*/  kill_pgrp (struct pid*,int,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  set_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct pid* task_pgrp (TYPE_2__*) ; 
 int /*<<< orphan*/  tty_warn (struct tty_struct*,char*,int) ; 

int __tty_check_change(struct tty_struct *tty, int sig)
{
	unsigned long flags;
	struct pid *pgrp, *tty_pgrp;
	int ret = 0;

	if (current->signal->tty != tty)
		return 0;

	rcu_read_lock();
	pgrp = task_pgrp(current);

	spin_lock_irqsave(&tty->ctrl_lock, flags);
	tty_pgrp = tty->pgrp;
	spin_unlock_irqrestore(&tty->ctrl_lock, flags);

	if (tty_pgrp && pgrp != tty_pgrp) {
		if (is_ignored(sig)) {
			if (sig == SIGTTIN)
				ret = -EIO;
		} else if (is_current_pgrp_orphaned())
			ret = -EIO;
		else {
			kill_pgrp(pgrp, sig, 1);
			set_thread_flag(TIF_SIGPENDING);
			ret = -ERESTARTSYS;
		}
	}
	rcu_read_unlock();

	if (!tty_pgrp)
		tty_warn(tty, "sig=%d, tty->pgrp == NULL!\n", sig);

	return ret;
}