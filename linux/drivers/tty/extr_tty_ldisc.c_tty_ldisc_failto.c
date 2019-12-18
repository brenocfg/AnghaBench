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
 scalar_t__ IS_ERR (struct tty_ldisc*) ; 
 int PTR_ERR (struct tty_ldisc*) ; 
 int /*<<< orphan*/  lockdep_assert_held_write (int /*<<< orphan*/ *) ; 
 struct tty_ldisc* tty_ldisc_get (struct tty_struct*,int) ; 
 int tty_ldisc_open (struct tty_struct*,struct tty_ldisc*) ; 
 int /*<<< orphan*/  tty_ldisc_put (struct tty_ldisc*) ; 
 int /*<<< orphan*/  tty_set_termios_ldisc (struct tty_struct*,int) ; 

__attribute__((used)) static int tty_ldisc_failto(struct tty_struct *tty, int ld)
{
	struct tty_ldisc *disc = tty_ldisc_get(tty, ld);
	int r;

	lockdep_assert_held_write(&tty->ldisc_sem);
	if (IS_ERR(disc))
		return PTR_ERR(disc);
	tty->ldisc = disc;
	tty_set_termios_ldisc(tty, ld);
	if ((r = tty_ldisc_open(tty, disc)) < 0)
		tty_ldisc_put(disc);
	return r;
}