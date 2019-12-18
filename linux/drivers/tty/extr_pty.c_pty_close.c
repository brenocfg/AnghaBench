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
struct tty_struct {int count; TYPE_1__* link; TYPE_2__* driver; int /*<<< orphan*/  flags; int /*<<< orphan*/  ctrl_lock; scalar_t__ packet; int /*<<< orphan*/  write_wait; int /*<<< orphan*/  read_wait; } ;
struct file {int dummy; } ;
struct TYPE_4__ {scalar_t__ subtype; } ;
struct TYPE_3__ {scalar_t__ driver_data; int /*<<< orphan*/  write_wait; int /*<<< orphan*/  read_wait; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ PTY_TYPE_MASTER ; 
 int /*<<< orphan*/  TTY_IO_ERROR ; 
 int /*<<< orphan*/  TTY_OTHER_CLOSED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  devpts_mutex ; 
 int /*<<< orphan*/  devpts_pty_kill (scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__* ptm_driver ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ tty_io_error (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_vhangup (TYPE_1__*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pty_close(struct tty_struct *tty, struct file *filp)
{
	BUG_ON(!tty);
	if (tty->driver->subtype == PTY_TYPE_MASTER)
		WARN_ON(tty->count > 1);
	else {
		if (tty_io_error(tty))
			return;
		if (tty->count > 2)
			return;
	}
	set_bit(TTY_IO_ERROR, &tty->flags);
	wake_up_interruptible(&tty->read_wait);
	wake_up_interruptible(&tty->write_wait);
	spin_lock_irq(&tty->ctrl_lock);
	tty->packet = 0;
	spin_unlock_irq(&tty->ctrl_lock);
	/* Review - krefs on tty_link ?? */
	if (!tty->link)
		return;
	set_bit(TTY_OTHER_CLOSED, &tty->link->flags);
	wake_up_interruptible(&tty->link->read_wait);
	wake_up_interruptible(&tty->link->write_wait);
	if (tty->driver->subtype == PTY_TYPE_MASTER) {
		set_bit(TTY_OTHER_CLOSED, &tty->flags);
#ifdef CONFIG_UNIX98_PTYS
		if (tty->driver == ptm_driver) {
			mutex_lock(&devpts_mutex);
			if (tty->link->driver_data)
				devpts_pty_kill(tty->link->driver_data);
			mutex_unlock(&devpts_mutex);
		}
#endif
		tty_vhangup(tty->link);
	}
}