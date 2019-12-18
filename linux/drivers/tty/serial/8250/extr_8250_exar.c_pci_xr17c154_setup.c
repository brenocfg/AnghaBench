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
struct TYPE_2__ {unsigned int uartclk; } ;
struct uart_8250_port {TYPE_1__ port; } ;
struct pci_dev {int dummy; } ;
struct exar8250 {int dummy; } ;

/* Variables and functions */
 int default_setup (struct exar8250*,struct pci_dev*,int,unsigned int,struct uart_8250_port*) ; 

__attribute__((used)) static int
pci_xr17c154_setup(struct exar8250 *priv, struct pci_dev *pcidev,
		   struct uart_8250_port *port, int idx)
{
	unsigned int offset = idx * 0x200;
	unsigned int baud = 921600;

	port->port.uartclk = baud * 16;
	return default_setup(priv, pcidev, idx, offset, port);
}