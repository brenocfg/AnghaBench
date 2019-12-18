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
struct TYPE_2__ {int regshift; int /*<<< orphan*/ * membase; void* mapbase; void* iobase; int /*<<< orphan*/  iotype; } ;
struct uart_8250_port {TYPE_1__ port; } ;
struct serial_private {struct pci_dev* dev; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int IORESOURCE_MEM ; 
 int PCI_NUM_BAR_RESOURCES ; 
 int /*<<< orphan*/  UPIO_MEM ; 
 int /*<<< orphan*/  UPIO_PORT ; 
 int pci_resource_flags (struct pci_dev*,int) ; 
 void* pci_resource_start (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pcim_iomap (struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** pcim_iomap_table (struct pci_dev*) ; 

__attribute__((used)) static int
setup_port(struct serial_private *priv, struct uart_8250_port *port,
	   int bar, int offset, int regshift)
{
	struct pci_dev *dev = priv->dev;

	if (bar >= PCI_NUM_BAR_RESOURCES)
		return -EINVAL;

	if (pci_resource_flags(dev, bar) & IORESOURCE_MEM) {
		if (!pcim_iomap(dev, bar, 0) && !pcim_iomap_table(dev))
			return -ENOMEM;

		port->port.iotype = UPIO_MEM;
		port->port.iobase = 0;
		port->port.mapbase = pci_resource_start(dev, bar) + offset;
		port->port.membase = pcim_iomap_table(dev)[bar] + offset;
		port->port.regshift = regshift;
	} else {
		port->port.iotype = UPIO_PORT;
		port->port.iobase = pci_resource_start(dev, bar) + offset;
		port->port.mapbase = 0;
		port->port.membase = NULL;
		port->port.regshift = 0;
	}
	return 0;
}