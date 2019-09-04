#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {TYPE_2__* driver; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* tiocmget ) (struct tty_struct*) ;int /*<<< orphan*/  (* tiocmset ) (struct tty_struct*,int,int) ;} ;

/* Variables and functions */
 int TIOCM_CTS ; 
 int TIOCM_RTS ; 
 int /*<<< orphan*/  msleep (int) ; 
 int stub1 (struct tty_struct*) ; 
 int stub2 (struct tty_struct*) ; 
 int /*<<< orphan*/  stub3 (struct tty_struct*,int,int) ; 
 int stub4 (struct tty_struct*) ; 
 int /*<<< orphan*/  stub5 (struct tty_struct*,int,int) ; 
 int stub6 (struct tty_struct*) ; 

__attribute__((used)) static int ath_wakeup_ar3k(struct tty_struct *tty)
{
	int status = tty->driver->ops->tiocmget(tty);

	if (status & TIOCM_CTS)
		return status;

	/* Clear RTS first */
	tty->driver->ops->tiocmget(tty);
	tty->driver->ops->tiocmset(tty, 0x00, TIOCM_RTS);
	msleep(20);

	/* Set RTS, wake up board */
	tty->driver->ops->tiocmget(tty);
	tty->driver->ops->tiocmset(tty, TIOCM_RTS, 0x00);
	msleep(20);

	status = tty->driver->ops->tiocmget(tty);
	return status;
}