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
struct tty_struct {struct tty_ldisc* ldisc; int /*<<< orphan*/  ldisc_sem; } ;
struct tty_ldisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ IS_ERR (struct tty_ldisc*) ; 
 int N_TTY ; 
 int PTR_ERR (struct tty_ldisc*) ; 
 int /*<<< orphan*/  lockdep_assert_held_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_ldisc_close (struct tty_struct*,struct tty_ldisc*) ; 
 struct tty_ldisc* tty_ldisc_get (struct tty_struct*,int) ; 
 int tty_ldisc_open (struct tty_struct*,struct tty_ldisc*) ; 
 int /*<<< orphan*/  tty_ldisc_put (struct tty_ldisc*) ; 
 int /*<<< orphan*/  tty_set_termios_ldisc (struct tty_struct*,int) ; 

int tty_ldisc_reinit(struct tty_struct *tty, int disc)
{
	struct tty_ldisc *ld;
	int retval;

	lockdep_assert_held_write(&tty->ldisc_sem);
	ld = tty_ldisc_get(tty, disc);
	if (IS_ERR(ld)) {
		BUG_ON(disc == N_TTY);
		return PTR_ERR(ld);
	}

	if (tty->ldisc) {
		tty_ldisc_close(tty, tty->ldisc);
		tty_ldisc_put(tty->ldisc);
	}

	/* switch the line discipline */
	tty->ldisc = ld;
	tty_set_termios_ldisc(tty, disc);
	retval = tty_ldisc_open(tty, tty->ldisc);
	if (retval) {
		tty_ldisc_put(tty->ldisc);
		tty->ldisc = NULL;
	}
	return retval;
}