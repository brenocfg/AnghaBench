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
struct tty_struct {TYPE_1__* ops; TYPE_2__* driver; } ;
struct TYPE_4__ {int flags; } ;
struct TYPE_3__ {int (* break_ctl ) (struct tty_struct*,int) ;} ;

/* Variables and functions */
 int EINTR ; 
 int TTY_DRIVER_HARDWARE_BREAK ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  msleep_interruptible (unsigned int) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int stub1 (struct tty_struct*,unsigned int) ; 
 int stub2 (struct tty_struct*,int) ; 
 int stub3 (struct tty_struct*,int) ; 
 scalar_t__ tty_write_lock (struct tty_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_write_unlock (struct tty_struct*) ; 

__attribute__((used)) static int send_break(struct tty_struct *tty, unsigned int duration)
{
	int retval;

	if (tty->ops->break_ctl == NULL)
		return 0;

	if (tty->driver->flags & TTY_DRIVER_HARDWARE_BREAK)
		retval = tty->ops->break_ctl(tty, duration);
	else {
		/* Do the work ourselves */
		if (tty_write_lock(tty, 0) < 0)
			return -EINTR;
		retval = tty->ops->break_ctl(tty, -1);
		if (retval)
			goto out;
		if (!signal_pending(current))
			msleep_interruptible(duration);
		retval = tty->ops->break_ctl(tty, 0);
out:
		tty_write_unlock(tty);
		if (signal_pending(current))
			retval = -EINTR;
	}
	return retval;
}