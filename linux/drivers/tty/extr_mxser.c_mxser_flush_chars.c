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
struct tty_struct {scalar_t__ hw_stopped; scalar_t__ stopped; struct mxser_port* driver_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  xmit_buf; } ;
struct mxser_port {scalar_t__ xmit_cnt; scalar_t__ type; int IER; int /*<<< orphan*/  slock; scalar_t__ ioaddr; TYPE_2__* board; TYPE_1__ port; } ;
struct TYPE_4__ {int /*<<< orphan*/  chip_flag; } ;

/* Variables and functions */
 scalar_t__ PORT_16550A ; 
 scalar_t__ UART_IER ; 
 int UART_IER_THRI ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void mxser_flush_chars(struct tty_struct *tty)
{
	struct mxser_port *info = tty->driver_data;
	unsigned long flags;

	if (info->xmit_cnt <= 0 || tty->stopped || !info->port.xmit_buf ||
			(tty->hw_stopped && info->type != PORT_16550A &&
			 !info->board->chip_flag))
		return;

	spin_lock_irqsave(&info->slock, flags);

	outb(info->IER & ~UART_IER_THRI, info->ioaddr + UART_IER);
	info->IER |= UART_IER_THRI;
	outb(info->IER, info->ioaddr + UART_IER);

	spin_unlock_irqrestore(&info->slock, flags);
}