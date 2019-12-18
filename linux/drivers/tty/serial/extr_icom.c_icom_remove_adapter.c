#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct icom_port {scalar_t__ status; TYPE_1__* dram; int /*<<< orphan*/  uart_port; } ;
struct icom_adapter {int numb_ports; TYPE_2__* pci_dev; int /*<<< orphan*/  base_addr; struct icom_port* port_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  osr; } ;

/* Variables and functions */
 scalar_t__ ICOM_PORT_ACTIVE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  free_port_memory (struct icom_port*) ; 
 int /*<<< orphan*/  icom_free_adapter (struct icom_adapter*) ; 
 int /*<<< orphan*/  icom_uart_driver ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pci_release_regions (TYPE_2__*) ; 
 int /*<<< orphan*/  stop_processor (struct icom_port*) ; 
 int /*<<< orphan*/  uart_remove_one_port (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void icom_remove_adapter(struct icom_adapter *icom_adapter)
{
	struct icom_port *icom_port;
	int index;

	for (index = 0; index < icom_adapter->numb_ports; index++) {
		icom_port = &icom_adapter->port_info[index];

		if (icom_port->status == ICOM_PORT_ACTIVE) {
			dev_info(&icom_adapter->pci_dev->dev,
				 "Device removed\n");

			uart_remove_one_port(&icom_uart_driver,
					     &icom_port->uart_port);

			/* be sure that DTR and RTS are dropped */
			writeb(0x00, &icom_port->dram->osr);

			/* Wait 0.1 Sec for simple Init to complete */
			msleep(100);

			/* Stop proccessor */
			stop_processor(icom_port);

			free_port_memory(icom_port);
		}
	}

	free_irq(icom_adapter->pci_dev->irq, (void *) icom_adapter);
	iounmap(icom_adapter->base_addr);
	pci_release_regions(icom_adapter->pci_dev);
	icom_free_adapter(icom_adapter);
}