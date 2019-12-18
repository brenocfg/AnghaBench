#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ktermios {int dummy; } ;
struct tty_struct {int /*<<< orphan*/  termios_rwsem; struct ktermios termios; TYPE_2__* ops; TYPE_1__* driver; } ;
struct tty_ldisc {TYPE_3__* ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* set_termios ) (struct tty_struct*,struct ktermios*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  (* set_termios ) (struct tty_struct*,struct ktermios*) ;} ;
struct TYPE_4__ {scalar_t__ type; scalar_t__ subtype; } ;

/* Variables and functions */
 scalar_t__ PTY_TYPE_MASTER ; 
 scalar_t__ TTY_DRIVER_TYPE_PTY ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct tty_struct*,struct ktermios*) ; 
 int /*<<< orphan*/  stub2 (struct tty_struct*,struct ktermios*) ; 
 int /*<<< orphan*/  tty_ldisc_deref (struct tty_ldisc*) ; 
 struct tty_ldisc* tty_ldisc_ref (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_termios_copy_hw (struct ktermios*,struct ktermios*) ; 
 int /*<<< orphan*/  unset_locked_termios (struct tty_struct*,struct ktermios*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int tty_set_termios(struct tty_struct *tty, struct ktermios *new_termios)
{
	struct ktermios old_termios;
	struct tty_ldisc *ld;

	WARN_ON(tty->driver->type == TTY_DRIVER_TYPE_PTY &&
		tty->driver->subtype == PTY_TYPE_MASTER);
	/*
	 *	Perform the actual termios internal changes under lock.
	 */


	/* FIXME: we need to decide on some locking/ordering semantics
	   for the set_termios notification eventually */
	down_write(&tty->termios_rwsem);
	old_termios = tty->termios;
	tty->termios = *new_termios;
	unset_locked_termios(tty, &old_termios);

	if (tty->ops->set_termios)
		tty->ops->set_termios(tty, &old_termios);
	else
		tty_termios_copy_hw(&tty->termios, &old_termios);

	ld = tty_ldisc_ref(tty);
	if (ld != NULL) {
		if (ld->ops->set_termios)
			ld->ops->set_termios(tty, &old_termios);
		tty_ldisc_deref(ld);
	}
	up_write(&tty->termios_rwsem);
	return 0;
}