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
struct TYPE_2__ {int /*<<< orphan*/  c_line; } ;
struct tty_struct {int /*<<< orphan*/  count; TYPE_1__ termios; int /*<<< orphan*/  ldisc; int /*<<< orphan*/  flags; struct tty_driver* driver; } ;
struct tty_ldisc {int dummy; } ;
struct tty_driver {scalar_t__ type; scalar_t__ subtype; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EAGAIN ; 
 int EBUSY ; 
 int EIO ; 
 int HZ ; 
 scalar_t__ PTY_TYPE_MASTER ; 
 scalar_t__ TTY_DRIVER_TYPE_PTY ; 
 int /*<<< orphan*/  TTY_EXCLUSIVE ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_ldisc_deref (struct tty_ldisc*) ; 
 int tty_ldisc_lock (struct tty_struct*,int) ; 
 struct tty_ldisc* tty_ldisc_ref_wait (struct tty_struct*) ; 
 int tty_ldisc_reinit (struct tty_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_ldisc_unlock (struct tty_struct*) ; 

__attribute__((used)) static int tty_reopen(struct tty_struct *tty)
{
	struct tty_driver *driver = tty->driver;
	struct tty_ldisc *ld;
	int retval = 0;

	if (driver->type == TTY_DRIVER_TYPE_PTY &&
	    driver->subtype == PTY_TYPE_MASTER)
		return -EIO;

	if (!tty->count)
		return -EAGAIN;

	if (test_bit(TTY_EXCLUSIVE, &tty->flags) && !capable(CAP_SYS_ADMIN))
		return -EBUSY;

	ld = tty_ldisc_ref_wait(tty);
	if (ld) {
		tty_ldisc_deref(ld);
	} else {
		retval = tty_ldisc_lock(tty, 5 * HZ);
		if (retval)
			return retval;

		if (!tty->ldisc)
			retval = tty_ldisc_reinit(tty, tty->termios.c_line);
		tty_ldisc_unlock(tty);
	}

	if (retval == 0)
		tty->count++;

	return retval;
}