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
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int /*<<< orphan*/ * session; int /*<<< orphan*/  ctrl_lock; int /*<<< orphan*/ * pgrp; } ;
struct TYPE_9__ {TYPE_1__* signal; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/ * tty_old_pgrp; TYPE_2__* tty; } ;

/* Variables and functions */
 TYPE_4__* current ; 
 void* get_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  task_pgrp (TYPE_4__*) ; 
 int /*<<< orphan*/  task_session (TYPE_4__*) ; 
 int /*<<< orphan*/  tty_debug (struct tty_struct*,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* tty_kref_get (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_kref_put (TYPE_2__*) ; 

__attribute__((used)) static void __proc_set_tty(struct tty_struct *tty)
{
	unsigned long flags;

	spin_lock_irqsave(&tty->ctrl_lock, flags);
	/*
	 * The session and fg pgrp references will be non-NULL if
	 * tiocsctty() is stealing the controlling tty
	 */
	put_pid(tty->session);
	put_pid(tty->pgrp);
	tty->pgrp = get_pid(task_pgrp(current));
	spin_unlock_irqrestore(&tty->ctrl_lock, flags);
	tty->session = get_pid(task_session(current));
	if (current->signal->tty) {
		tty_debug(tty, "current tty %s not NULL!!\n",
			  current->signal->tty->name);
		tty_kref_put(current->signal->tty);
	}
	put_pid(current->signal->tty_old_pgrp);
	current->signal->tty = tty_kref_get(tty);
	current->signal->tty_old_pgrp = NULL;
}