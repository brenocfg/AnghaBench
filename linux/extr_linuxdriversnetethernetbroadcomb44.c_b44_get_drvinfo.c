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
struct ssb_bus {int bustype; int /*<<< orphan*/  host_pci; } ;
struct net_device {int dummy; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;
struct b44 {TYPE_1__* sdev; } ;
struct TYPE_2__ {struct ssb_bus* bus; } ;

/* Variables and functions */
 char* DRV_MODULE_NAME ; 
 char* DRV_MODULE_VERSION ; 
#define  SSB_BUSTYPE_PCI 131 
#define  SSB_BUSTYPE_PCMCIA 130 
#define  SSB_BUSTYPE_SDIO 129 
#define  SSB_BUSTYPE_SSB 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct b44* netdev_priv (struct net_device*) ; 
 char* pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void b44_get_drvinfo (struct net_device *dev, struct ethtool_drvinfo *info)
{
	struct b44 *bp = netdev_priv(dev);
	struct ssb_bus *bus = bp->sdev->bus;

	strlcpy(info->driver, DRV_MODULE_NAME, sizeof(info->driver));
	strlcpy(info->version, DRV_MODULE_VERSION, sizeof(info->version));
	switch (bus->bustype) {
	case SSB_BUSTYPE_PCI:
		strlcpy(info->bus_info, pci_name(bus->host_pci), sizeof(info->bus_info));
		break;
	case SSB_BUSTYPE_SSB:
		strlcpy(info->bus_info, "SSB", sizeof(info->bus_info));
		break;
	case SSB_BUSTYPE_PCMCIA:
	case SSB_BUSTYPE_SDIO:
		WARN_ON(1); /* A device with this bus does not exist. */
		break;
	}
}