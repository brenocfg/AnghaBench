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
typedef  int u8 ;
struct TYPE_3__ {int /*<<< orphan*/  overrun; int /*<<< orphan*/  frame; int /*<<< orphan*/  parity; int /*<<< orphan*/  rx; } ;
struct uart_port {int read_status_mask; int ignore_status_mask; TYPE_2__* state; int /*<<< orphan*/  lock; TYPE_1__ icount; scalar_t__ membase; } ;
struct TYPE_4__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 unsigned int TTY_FRAME ; 
 unsigned int TTY_NORMAL ; 
 unsigned int TTY_OVERRUN ; 
 unsigned int TTY_PARITY ; 
 scalar_t__ UA_EMI_REC ; 
 scalar_t__ UA_STATUS ; 
 int UA_STATUS_FRAME_ERR ; 
 int UA_STATUS_OVERRUN_ERR ; 
 int UA_STATUS_PARITY_ERR ; 
 scalar_t__ digicolor_uart_rx_empty (struct uart_port*) ; 
 int readb_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uart_insert_char (struct uart_port*,int,int,int,unsigned int) ; 

__attribute__((used)) static void digicolor_uart_rx(struct uart_port *port)
{
	unsigned long flags;

	spin_lock_irqsave(&port->lock, flags);

	while (1) {
		u8 status, ch;
		unsigned int ch_flag;

		if (digicolor_uart_rx_empty(port))
			break;

		ch = readb_relaxed(port->membase + UA_EMI_REC);
		status = readb_relaxed(port->membase + UA_STATUS);

		port->icount.rx++;
		ch_flag = TTY_NORMAL;

		if (status) {
			if (status & UA_STATUS_PARITY_ERR)
				port->icount.parity++;
			else if (status & UA_STATUS_FRAME_ERR)
				port->icount.frame++;
			else if (status & UA_STATUS_OVERRUN_ERR)
				port->icount.overrun++;

			status &= port->read_status_mask;

			if (status & UA_STATUS_PARITY_ERR)
				ch_flag = TTY_PARITY;
			else if (status & UA_STATUS_FRAME_ERR)
				ch_flag = TTY_FRAME;
			else if (status & UA_STATUS_OVERRUN_ERR)
				ch_flag = TTY_OVERRUN;
		}

		if (status & port->ignore_status_mask)
			continue;

		uart_insert_char(port, status, UA_STATUS_OVERRUN_ERR, ch,
				 ch_flag);
	}

	spin_unlock_irqrestore(&port->lock, flags);

	tty_flip_buffer_push(&port->state->port);
}