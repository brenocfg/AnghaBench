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
struct TYPE_2__ {int /*<<< orphan*/  shutdown; int /*<<< orphan*/  pm; int /*<<< orphan*/  type; int /*<<< orphan*/  set_divisor; int /*<<< orphan*/  get_divisor; scalar_t__ membase; int /*<<< orphan*/  regshift; scalar_t__ mapbase; int /*<<< orphan*/  iotype; } ;
struct uart_8250_port {TYPE_1__ port; } ;
struct pci_dev {int dummy; } ;
struct exar8250_board {int /*<<< orphan*/  reg_shift; } ;
struct exar8250 {scalar_t__ virt; struct exar8250_board* board; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_XR17D15X ; 
 int /*<<< orphan*/  PORT_XR17V35X ; 
 scalar_t__ UART_EXAR_DVID ; 
 int /*<<< orphan*/  UPIO_MEM ; 
 int /*<<< orphan*/  exar_pm ; 
 int /*<<< orphan*/  exar_shutdown ; 
 scalar_t__ pci_resource_start (struct pci_dev*,unsigned int) ; 
 unsigned char readb (scalar_t__) ; 
 int /*<<< orphan*/  xr17v35x_get_divisor ; 
 int /*<<< orphan*/  xr17v35x_set_divisor ; 

__attribute__((used)) static int default_setup(struct exar8250 *priv, struct pci_dev *pcidev,
			 int idx, unsigned int offset,
			 struct uart_8250_port *port)
{
	const struct exar8250_board *board = priv->board;
	unsigned int bar = 0;
	unsigned char status;

	port->port.iotype = UPIO_MEM;
	port->port.mapbase = pci_resource_start(pcidev, bar) + offset;
	port->port.membase = priv->virt + offset;
	port->port.regshift = board->reg_shift;

	/*
	 * XR17V35x UARTs have an extra divisor register, DLD that gets enabled
	 * with when DLAB is set which will cause the device to incorrectly match
	 * and assign port type to PORT_16650. The EFR for this UART is found
	 * at offset 0x09. Instead check the Deice ID (DVID) register
	 * for a 2, 4 or 8 port UART.
	 */
	status = readb(port->port.membase + UART_EXAR_DVID);
	if (status == 0x82 || status == 0x84 || status == 0x88) {
		port->port.type = PORT_XR17V35X;

		port->port.get_divisor = xr17v35x_get_divisor;
		port->port.set_divisor = xr17v35x_set_divisor;
	} else {
		port->port.type = PORT_XR17D15X;
	}

	port->port.pm = exar_pm;
	port->port.shutdown = exar_shutdown;

	return 0;
}