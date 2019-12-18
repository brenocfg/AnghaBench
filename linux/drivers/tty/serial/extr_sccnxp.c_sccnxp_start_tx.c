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
struct uart_port {int /*<<< orphan*/  dev; } ;
struct sccnxp_port {int /*<<< orphan*/  lock; TYPE_1__* chip; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIR_OP ; 
 int /*<<< orphan*/  IMR_TXRDY ; 
 int SCCNXP_HAVE_IO ; 
 struct sccnxp_port* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sccnxp_enable_irq (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sccnxp_set_bit (struct uart_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void sccnxp_start_tx(struct uart_port *port)
{
	struct sccnxp_port *s = dev_get_drvdata(port->dev);
	unsigned long flags;

	spin_lock_irqsave(&s->lock, flags);

	/* Set direction to output */
	if (s->chip->flags & SCCNXP_HAVE_IO)
		sccnxp_set_bit(port, DIR_OP, 1);

	sccnxp_enable_irq(port, IMR_TXRDY);

	spin_unlock_irqrestore(&s->lock, flags);
}