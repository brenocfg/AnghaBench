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
struct uart_port {int /*<<< orphan*/  irq; scalar_t__ read_status_mask; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* cw_disable_ints ) (struct uart_port*) ;int /*<<< orphan*/  (* clock ) (struct uart_port*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_imr ) (struct uart_port*,scalar_t__) ;int /*<<< orphan*/  (* command ) (struct uart_port*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MPC52xx_PSC_RST_RX ; 
 int /*<<< orphan*/  MPC52xx_PSC_RST_TX ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct uart_port*) ; 
 TYPE_1__* psc_ops ; 
 int /*<<< orphan*/  stub1 (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct uart_port*,scalar_t__) ; 
 int /*<<< orphan*/  stub4 (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct uart_port*) ; 
 int /*<<< orphan*/  uart_console (struct uart_port*) ; 

__attribute__((used)) static void
mpc52xx_uart_shutdown(struct uart_port *port)
{
	/* Shut down the port.  Leave TX active if on a console port */
	psc_ops->command(port, MPC52xx_PSC_RST_RX);
	if (!uart_console(port))
		psc_ops->command(port, MPC52xx_PSC_RST_TX);

	port->read_status_mask = 0;
	psc_ops->set_imr(port, port->read_status_mask);

	if (psc_ops->clock)
		psc_ops->clock(port, 0);

	/* Disable interrupt */
	psc_ops->cw_disable_ints(port);

	/* Release interrupt */
	free_irq(port->irq, port);
}