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
struct TYPE_3__ {int /*<<< orphan*/  rx; } ;
struct uart_port {int /*<<< orphan*/  lock; TYPE_2__* state; TYPE_1__ icount; scalar_t__ membase; } ;
struct altera_jtaguart {struct uart_port port; } ;
struct TYPE_4__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 unsigned long ALTERA_JTAGUART_DATA_DATA_MSK ; 
 scalar_t__ ALTERA_JTAGUART_DATA_REG ; 
 unsigned long ALTERA_JTAGUART_DATA_RVALID_MSK ; 
 unsigned char TTY_NORMAL ; 
 unsigned long readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (int /*<<< orphan*/ *) ; 
 scalar_t__ uart_handle_sysrq_char (struct uart_port*,unsigned char) ; 
 int /*<<< orphan*/  uart_insert_char (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char,unsigned char) ; 

__attribute__((used)) static void altera_jtaguart_rx_chars(struct altera_jtaguart *pp)
{
	struct uart_port *port = &pp->port;
	unsigned char ch, flag;
	unsigned long status;

	while ((status = readl(port->membase + ALTERA_JTAGUART_DATA_REG)) &
	       ALTERA_JTAGUART_DATA_RVALID_MSK) {
		ch = status & ALTERA_JTAGUART_DATA_DATA_MSK;
		flag = TTY_NORMAL;
		port->icount.rx++;

		if (uart_handle_sysrq_char(port, ch))
			continue;
		uart_insert_char(port, 0, 0, ch, flag);
	}

	spin_unlock(&port->lock);
	tty_flip_buffer_push(&port->state->port);
	spin_lock(&port->lock);
}