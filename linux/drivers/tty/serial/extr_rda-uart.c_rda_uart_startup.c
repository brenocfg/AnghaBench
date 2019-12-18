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
struct uart_port {int /*<<< orphan*/  lock; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_NO_SUSPEND ; 
 int /*<<< orphan*/  RDA_UART_CTRL ; 
 int RDA_UART_ENABLE ; 
 int /*<<< orphan*/  RDA_UART_IRQ_MASK ; 
 int RDA_UART_RX_DATA_AVAILABLE ; 
 int RDA_UART_RX_TIMEOUT ; 
 int /*<<< orphan*/  rda_interrupt ; 
 int rda_uart_read (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rda_uart_write (struct uart_port*,int,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct uart_port*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int rda_uart_startup(struct uart_port *port)
{
	unsigned long flags;
	int ret;
	u32 val;

	spin_lock_irqsave(&port->lock, flags);
	rda_uart_write(port, 0, RDA_UART_IRQ_MASK);
	spin_unlock_irqrestore(&port->lock, flags);

	ret = request_irq(port->irq, rda_interrupt, IRQF_NO_SUSPEND,
			  "rda-uart", port);
	if (ret)
		return ret;

	spin_lock_irqsave(&port->lock, flags);

	val = rda_uart_read(port, RDA_UART_CTRL);
	val |= RDA_UART_ENABLE;
	rda_uart_write(port, val, RDA_UART_CTRL);

	/* enable rx interrupt */
	val = rda_uart_read(port, RDA_UART_IRQ_MASK);
	val |= (RDA_UART_RX_DATA_AVAILABLE | RDA_UART_RX_TIMEOUT);
	rda_uart_write(port, val, RDA_UART_IRQ_MASK);

	spin_unlock_irqrestore(&port->lock, flags);

	return 0;
}