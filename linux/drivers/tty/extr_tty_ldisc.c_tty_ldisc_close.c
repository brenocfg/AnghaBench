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
struct tty_struct {int /*<<< orphan*/  flags; int /*<<< orphan*/  ldisc_sem; } ;
struct tty_ldisc {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* close ) (struct tty_struct*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TTY_LDISC_OPEN ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct tty_struct*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_ldisc_debug (struct tty_struct*,char*,struct tty_ldisc*) ; 

__attribute__((used)) static void tty_ldisc_close(struct tty_struct *tty, struct tty_ldisc *ld)
{
	lockdep_assert_held_write(&tty->ldisc_sem);
	WARN_ON(!test_bit(TTY_LDISC_OPEN, &tty->flags));
	clear_bit(TTY_LDISC_OPEN, &tty->flags);
	if (ld->ops->close)
		ld->ops->close(tty);
	tty_ldisc_debug(tty, "%p: closed\n", ld);
}