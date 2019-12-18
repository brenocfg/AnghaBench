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
struct uart_port {int /*<<< orphan*/  lock; scalar_t__ membase; } ;
struct men_z135_port {TYPE_1__* mdev; int /*<<< orphan*/  stat_reg; struct uart_port port; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int IRQ_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int MEN_Z135_IRQ_ID_CTI ; 
 int MEN_Z135_IRQ_ID_MST ; 
 int MEN_Z135_IRQ_ID_RDA ; 
 int MEN_Z135_IRQ_ID_RLS ; 
 int MEN_Z135_IRQ_ID_TSA ; 
 scalar_t__ MEN_Z135_STAT_REG ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite8 (int,scalar_t__) ; 
 int /*<<< orphan*/  men_z135_handle_lsr (struct men_z135_port*) ; 
 int /*<<< orphan*/  men_z135_handle_modem_status (struct men_z135_port*) ; 
 int /*<<< orphan*/  men_z135_handle_rx (struct men_z135_port*) ; 
 int /*<<< orphan*/  men_z135_handle_tx (struct men_z135_port*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t men_z135_intr(int irq, void *data)
{
	struct men_z135_port *uart = (struct men_z135_port *)data;
	struct uart_port *port = &uart->port;
	bool handled = false;
	int irq_id;

	uart->stat_reg = ioread32(port->membase + MEN_Z135_STAT_REG);
	irq_id = IRQ_ID(uart->stat_reg);

	if (!irq_id)
		goto out;

	spin_lock(&port->lock);
	/* It's save to write to IIR[7:6] RXC[9:8] */
	iowrite8(irq_id, port->membase + MEN_Z135_STAT_REG);

	if (irq_id & MEN_Z135_IRQ_ID_RLS) {
		men_z135_handle_lsr(uart);
		handled = true;
	}

	if (irq_id & (MEN_Z135_IRQ_ID_RDA | MEN_Z135_IRQ_ID_CTI)) {
		if (irq_id & MEN_Z135_IRQ_ID_CTI)
			dev_dbg(&uart->mdev->dev, "Character Timeout Indication\n");
		men_z135_handle_rx(uart);
		handled = true;
	}

	if (irq_id & MEN_Z135_IRQ_ID_TSA) {
		men_z135_handle_tx(uart);
		handled = true;
	}

	if (irq_id & MEN_Z135_IRQ_ID_MST) {
		men_z135_handle_modem_status(uart);
		handled = true;
	}

	spin_unlock(&port->lock);
out:
	return IRQ_RETVAL(handled);
}