#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int /*<<< orphan*/  flags; } ;
struct TYPE_8__ {int serial_signals; int /*<<< orphan*/  port; int /*<<< orphan*/  lock; int /*<<< orphan*/ * tx_buf; int /*<<< orphan*/  tx_timer; int /*<<< orphan*/  event_wait_q; int /*<<< orphan*/  status_event_wait_q; int /*<<< orphan*/  device_name; } ;
typedef  TYPE_1__ MGSLPC_INFO ;

/* Variables and functions */
 scalar_t__ C_HUPCL (struct tty_struct*) ; 
 scalar_t__ DEBUG_LEVEL_INFO ; 
 int SerialSignal_DTR ; 
 int SerialSignal_RTS ; 
 int /*<<< orphan*/  TTY_IO_ERROR ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_resources (TYPE_1__*) ; 
 int /*<<< orphan*/  reset_device (TYPE_1__*) ; 
 int /*<<< orphan*/  rx_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_signals (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_port_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_port_set_initialized (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tx_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void shutdown(MGSLPC_INFO * info, struct tty_struct *tty)
{
	unsigned long flags;

	if (!tty_port_initialized(&info->port))
		return;

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):mgslpc_shutdown(%s)\n",
			 __FILE__, __LINE__, info->device_name);

	/* clear status wait queue because status changes */
	/* can't happen after shutting down the hardware */
	wake_up_interruptible(&info->status_event_wait_q);
	wake_up_interruptible(&info->event_wait_q);

	del_timer_sync(&info->tx_timer);

	if (info->tx_buf) {
		free_page((unsigned long) info->tx_buf);
		info->tx_buf = NULL;
	}

	spin_lock_irqsave(&info->lock, flags);

	rx_stop(info);
	tx_stop(info);

	/* TODO:disable interrupts instead of reset to preserve signal states */
	reset_device(info);

	if (!tty || C_HUPCL(tty)) {
		info->serial_signals &= ~(SerialSignal_RTS | SerialSignal_DTR);
		set_signals(info);
	}

	spin_unlock_irqrestore(&info->lock, flags);

	release_resources(info);

	if (tty)
		set_bit(TTY_IO_ERROR, &tty->flags);

	tty_port_set_initialized(&info->port, 0);
}