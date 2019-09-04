#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  coherent_dma_mask; int /*<<< orphan*/ * dma_mask; scalar_t__ parent; int /*<<< orphan*/ * bus; int /*<<< orphan*/  release; } ;
struct bcma_device {TYPE_3__ dev; TYPE_3__* dma_dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  core_index; } ;
struct bcma_bus {int hosttype; TYPE_2__* host_pdev; TYPE_1__* host_pci; int /*<<< orphan*/  num; } ;
struct TYPE_5__ {TYPE_3__ dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; TYPE_3__ dev; } ;

/* Variables and functions */
#define  BCMA_HOSTTYPE_PCI 130 
#define  BCMA_HOSTTYPE_SDIO 129 
#define  BCMA_HOSTTYPE_SOC 128 
 int /*<<< orphan*/  CONFIG_OF ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ bcma_bus_get_host_dev (struct bcma_bus*) ; 
 int /*<<< orphan*/  bcma_bus_type ; 
 int /*<<< orphan*/  bcma_of_fill_device (scalar_t__,struct bcma_device*) ; 
 int /*<<< orphan*/  bcma_release_core_dev ; 
 int /*<<< orphan*/  dev_set_name (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bcma_prepare_core(struct bcma_bus *bus, struct bcma_device *core)
{
	core->dev.release = bcma_release_core_dev;
	core->dev.bus = &bcma_bus_type;
	dev_set_name(&core->dev, "bcma%d:%d", bus->num, core->core_index);
	core->dev.parent = bcma_bus_get_host_dev(bus);
	if (core->dev.parent)
		bcma_of_fill_device(core->dev.parent, core);

	switch (bus->hosttype) {
	case BCMA_HOSTTYPE_PCI:
		core->dma_dev = &bus->host_pci->dev;
		core->irq = bus->host_pci->irq;
		break;
	case BCMA_HOSTTYPE_SOC:
		if (IS_ENABLED(CONFIG_OF) && bus->host_pdev) {
			core->dma_dev = &bus->host_pdev->dev;
		} else {
			core->dev.dma_mask = &core->dev.coherent_dma_mask;
			core->dma_dev = &core->dev;
		}
		break;
	case BCMA_HOSTTYPE_SDIO:
		break;
	}
}