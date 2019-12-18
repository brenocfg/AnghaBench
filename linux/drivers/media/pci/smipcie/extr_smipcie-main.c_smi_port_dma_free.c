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
struct smi_port {int /*<<< orphan*/ ** cpu_addr; int /*<<< orphan*/ * dma_addr; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  pci_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMI_TS_DMA_BUF_SIZE ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smi_port_dma_free(struct smi_port *port)
{
	if (port->cpu_addr[0]) {
		pci_free_consistent(port->dev->pci_dev, SMI_TS_DMA_BUF_SIZE,
				    port->cpu_addr[0], port->dma_addr[0]);
		port->cpu_addr[0] = NULL;
	}
	if (port->cpu_addr[1]) {
		pci_free_consistent(port->dev->pci_dev, SMI_TS_DMA_BUF_SIZE,
				    port->cpu_addr[1], port->dma_addr[1]);
		port->cpu_addr[1] = NULL;
	}
}