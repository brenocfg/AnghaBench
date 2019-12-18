#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int /*<<< orphan*/  ctrl_lock; struct pid* pgrp; struct pid* session; TYPE_1__* driver; } ;
struct pid {int dummy; } ;
struct TYPE_9__ {TYPE_3__* sighand; TYPE_2__* signal; } ;
struct TYPE_8__ {int /*<<< orphan*/  siglock; } ;
struct TYPE_7__ {int /*<<< orphan*/  tty; struct pid* tty_old_pgrp; int /*<<< orphan*/  leader; } ;
struct TYPE_6__ {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGCONT ; 
 int /*<<< orphan*/  SIGHUP ; 
 scalar_t__ TTY_DRIVER_TYPE_PTY ; 
 TYPE_4__* current ; 
 struct tty_struct* get_current_tty () ; 
 int /*<<< orphan*/  kill_pgrp (struct pid*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_pid (struct pid*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  session_clear_tty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  task_session (TYPE_4__*) ; 
 int /*<<< orphan*/  tasklist_lock ; 
 struct pid* tty_get_pgrp (struct tty_struct*) ; 
 struct tty_struct* tty_kref_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_vhangup_session (struct tty_struct*) ; 

void disassociate_ctty(int on_exit)
{
	struct tty_struct *tty;

	if (!current->signal->leader)
		return;

	tty = get_current_tty();
	if (tty) {
		if (on_exit && tty->driver->type != TTY_DRIVER_TYPE_PTY) {
			tty_vhangup_session(tty);
		} else {
			struct pid *tty_pgrp = tty_get_pgrp(tty);
			if (tty_pgrp) {
				kill_pgrp(tty_pgrp, SIGHUP, on_exit);
				if (!on_exit)
					kill_pgrp(tty_pgrp, SIGCONT, on_exit);
				put_pid(tty_pgrp);
			}
		}
		tty_kref_put(tty);

	} else if (on_exit) {
		struct pid *old_pgrp;
		spin_lock_irq(&current->sighand->siglock);
		old_pgrp = current->signal->tty_old_pgrp;
		current->signal->tty_old_pgrp = NULL;
		spin_unlock_irq(&current->sighand->siglock);
		if (old_pgrp) {
			kill_pgrp(old_pgrp, SIGHUP, on_exit);
			kill_pgrp(old_pgrp, SIGCONT, on_exit);
			put_pid(old_pgrp);
		}
		return;
	}

	spin_lock_irq(&current->sighand->siglock);
	put_pid(current->signal->tty_old_pgrp);
	current->signal->tty_old_pgrp = NULL;

	tty = tty_kref_get(current->signal->tty);
	if (tty) {
		unsigned long flags;
		spin_lock_irqsave(&tty->ctrl_lock, flags);
		put_pid(tty->session);
		put_pid(tty->pgrp);
		tty->session = NULL;
		tty->pgrp = NULL;
		spin_unlock_irqrestore(&tty->ctrl_lock, flags);
		tty_kref_put(tty);
	}

	spin_unlock_irq(&current->sighand->siglock);
	/* Now clear signal->tty under the lock */
	read_lock(&tasklist_lock);
	session_clear_tty(task_session(current));
	read_unlock(&tasklist_lock);
}