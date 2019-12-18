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
struct tty_struct {int /*<<< orphan*/ * ldisc; int /*<<< orphan*/  ldisc_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_assert_held_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_ldisc_close (struct tty_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_ldisc_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tty_ldisc_kill(struct tty_struct *tty)
{
	lockdep_assert_held_write(&tty->ldisc_sem);
	if (!tty->ldisc)
		return;
	/*
	 * Now kill off the ldisc
	 */
	tty_ldisc_close(tty, tty->ldisc);
	tty_ldisc_put(tty->ldisc);
	/* Force an oops if we mess this up */
	tty->ldisc = NULL;
}