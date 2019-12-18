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
struct TYPE_2__ {int /*<<< orphan*/  private_data; } ;
struct uart_8250_port {TYPE_1__ port; } ;
struct pci_dev {scalar_t__ vendor; } ;

/* Variables and functions */
 scalar_t__ PCI_VENDOR_ID_EXAR ; 
 int /*<<< orphan*/  __xr17v35x_register_gpio (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exar_gpio_properties ; 

__attribute__((used)) static int xr17v35x_register_gpio(struct pci_dev *pcidev,
				  struct uart_8250_port *port)
{
	if (pcidev->vendor == PCI_VENDOR_ID_EXAR)
		port->port.private_data =
			__xr17v35x_register_gpio(pcidev, exar_gpio_properties);

	return 0;
}