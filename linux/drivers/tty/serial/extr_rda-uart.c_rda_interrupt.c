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
typedef  int u32 ;
struct uart_port {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  RDA_UART_IRQ_CAUSE ; 
 int /*<<< orphan*/  RDA_UART_IRQ_MASK ; 
 int RDA_UART_RX_DATA_AVAILABLE ; 
 int RDA_UART_RX_TIMEOUT ; 
 int RDA_UART_TX_DATA_NEEDED ; 
 int rda_uart_read (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rda_uart_receive_chars (struct uart_port*) ; 
 int /*<<< orphan*/  rda_uart_send_chars (struct uart_port*) ; 
 int /*<<< orphan*/  rda_uart_write (struct uart_port*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t rda_interrupt(int irq, void *dev_id)
{
	struct uart_port *port = dev_id;
	unsigned long flags;
	u32 val, irq_mask;

	spin_lock_irqsave(&port->lock, flags);

	/* Clear IRQ cause */
	val = rda_uart_read(port, RDA_UART_IRQ_CAUSE);
	rda_uart_write(port, val, RDA_UART_IRQ_CAUSE);

	if (val & (RDA_UART_RX_DATA_AVAILABLE | RDA_UART_RX_TIMEOUT))
		rda_uart_receive_chars(port);

	if (val & (RDA_UART_TX_DATA_NEEDED)) {
		irq_mask = rda_uart_read(port, RDA_UART_IRQ_MASK);
		irq_mask &= ~RDA_UART_TX_DATA_NEEDED;
		rda_uart_write(port, irq_mask, RDA_UART_IRQ_MASK);

		rda_uart_send_chars(port);
	}

	spin_unlock_irqrestore(&port->lock, flags);

	return IRQ_HANDLED;
}