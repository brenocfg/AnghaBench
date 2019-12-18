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
struct TYPE_2__ {int /*<<< orphan*/  uartclk; int /*<<< orphan*/  iobase; } ;
struct uart_8250_port {TYPE_1__ port; } ;
struct serial_private {int /*<<< orphan*/  dev; } ;
struct pciserial_board {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FL_GET_BASE (int /*<<< orphan*/ ) ; 
 int pci_default_setup (struct serial_private*,struct pciserial_board const*,struct uart_8250_port*,int) ; 
 int /*<<< orphan*/  pci_quatech_clock (struct uart_8250_port*) ; 
 scalar_t__ pci_quatech_rs422 (struct uart_8250_port*) ; 
 int /*<<< orphan*/  pci_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static int pci_quatech_setup(struct serial_private *priv,
		  const struct pciserial_board *board,
		  struct uart_8250_port *port, int idx)
{
	/* Needed by pci_quatech calls below */
	port->port.iobase = pci_resource_start(priv->dev, FL_GET_BASE(board->flags));
	/* Set up the clocking */
	port->port.uartclk = pci_quatech_clock(port);
	/* For now just warn about RS422 */
	if (pci_quatech_rs422(port))
		pr_warn("quatech: software control of RS422 features not currently supported.\n");
	return pci_default_setup(priv, board, port, idx);
}