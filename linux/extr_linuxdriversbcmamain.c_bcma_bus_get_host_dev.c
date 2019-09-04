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
struct device {int dummy; } ;
struct bcma_bus {int hosttype; TYPE_3__* host_sdio; TYPE_2__* host_pdev; TYPE_1__* host_pci; } ;
struct TYPE_6__ {struct device dev; } ;
struct TYPE_5__ {struct device dev; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
#define  BCMA_HOSTTYPE_PCI 130 
#define  BCMA_HOSTTYPE_SDIO 129 
#define  BCMA_HOSTTYPE_SOC 128 

struct device *bcma_bus_get_host_dev(struct bcma_bus *bus)
{
	switch (bus->hosttype) {
	case BCMA_HOSTTYPE_PCI:
		if (bus->host_pci)
			return &bus->host_pci->dev;
		else
			return NULL;
	case BCMA_HOSTTYPE_SOC:
		if (bus->host_pdev)
			return &bus->host_pdev->dev;
		else
			return NULL;
	case BCMA_HOSTTYPE_SDIO:
		if (bus->host_sdio)
			return &bus->host_sdio->dev;
		else
			return NULL;
	}
	return NULL;
}