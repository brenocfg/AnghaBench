#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* tty; } ;
struct slgt_info {int signals; TYPE_3__ port; int /*<<< orphan*/  lock; int /*<<< orphan*/  gpio_wait_q; int /*<<< orphan*/ * tx_buf; int /*<<< orphan*/  rx_timer; int /*<<< orphan*/  tx_timer; int /*<<< orphan*/  event_wait_q; int /*<<< orphan*/  status_event_wait_q; int /*<<< orphan*/  device_name; } ;
struct TYPE_5__ {int c_cflag; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; TYPE_1__ termios; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGINFO (char*) ; 
 int HUPCL ; 
 int IRQ_ALL ; 
 int IRQ_MASTER ; 
 int SerialSignal_DTR ; 
 int SerialSignal_RTS ; 
 int /*<<< orphan*/  TTY_IO_ERROR ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_cond_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rx_stop (struct slgt_info*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_signals (struct slgt_info*) ; 
 int /*<<< orphan*/  slgt_irq_off (struct slgt_info*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_port_initialized (TYPE_3__*) ; 
 int /*<<< orphan*/  tty_port_set_initialized (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tx_stop (struct slgt_info*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void shutdown(struct slgt_info *info)
{
	unsigned long flags;

	if (!tty_port_initialized(&info->port))
		return;

	DBGINFO(("%s shutdown\n", info->device_name));

	/* clear status wait queue because status changes */
	/* can't happen after shutting down the hardware */
	wake_up_interruptible(&info->status_event_wait_q);
	wake_up_interruptible(&info->event_wait_q);

	del_timer_sync(&info->tx_timer);
	del_timer_sync(&info->rx_timer);

	kfree(info->tx_buf);
	info->tx_buf = NULL;

	spin_lock_irqsave(&info->lock,flags);

	tx_stop(info);
	rx_stop(info);

	slgt_irq_off(info, IRQ_ALL | IRQ_MASTER);

 	if (!info->port.tty || info->port.tty->termios.c_cflag & HUPCL) {
		info->signals &= ~(SerialSignal_RTS | SerialSignal_DTR);
		set_signals(info);
	}

	flush_cond_wait(&info->gpio_wait_q);

	spin_unlock_irqrestore(&info->lock,flags);

	if (info->port.tty)
		set_bit(TTY_IO_ERROR, &info->port.tty->flags);

	tty_port_set_initialized(&info->port, 0);
}