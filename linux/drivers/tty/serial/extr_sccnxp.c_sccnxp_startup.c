#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct uart_port {size_t line; int /*<<< orphan*/  dev; } ;
struct sccnxp_port {int* opened; int /*<<< orphan*/  lock; TYPE_1__* chip; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int CR_CMD_BREAK_RESET ; 
 int CR_CMD_RX_RESET ; 
 int CR_CMD_STATUS_RESET ; 
 int CR_CMD_TX_RESET ; 
 int CR_RX_ENABLE ; 
 int CR_TX_ENABLE ; 
 int /*<<< orphan*/  IMR_RXRDY ; 
 int /*<<< orphan*/  SCCNXP_CR_REG ; 
 int SCCNXP_HAVE_IO ; 
 int /*<<< orphan*/  SCCNXP_OPCR_REG ; 
 struct sccnxp_port* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sccnxp_enable_irq (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sccnxp_port_write (struct uart_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sccnxp_write (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int sccnxp_startup(struct uart_port *port)
{
	struct sccnxp_port *s = dev_get_drvdata(port->dev);
	unsigned long flags;

	spin_lock_irqsave(&s->lock, flags);

	if (s->chip->flags & SCCNXP_HAVE_IO) {
		/* Outputs are controlled manually */
		sccnxp_write(port, SCCNXP_OPCR_REG, 0);
	}

	/* Reset break condition, status and FIFOs */
	sccnxp_port_write(port, SCCNXP_CR_REG, CR_CMD_RX_RESET);
	sccnxp_port_write(port, SCCNXP_CR_REG, CR_CMD_TX_RESET);
	sccnxp_port_write(port, SCCNXP_CR_REG, CR_CMD_STATUS_RESET);
	sccnxp_port_write(port, SCCNXP_CR_REG, CR_CMD_BREAK_RESET);

	/* Enable RX & TX */
	sccnxp_port_write(port, SCCNXP_CR_REG, CR_RX_ENABLE | CR_TX_ENABLE);

	/* Enable RX interrupt */
	sccnxp_enable_irq(port, IMR_RXRDY);

	s->opened[port->line] = 1;

	spin_unlock_irqrestore(&s->lock, flags);

	return 0;
}