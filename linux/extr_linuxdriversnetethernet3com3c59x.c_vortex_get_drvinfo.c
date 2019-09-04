#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vortex_private {int /*<<< orphan*/  gendev; } ;
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  base_addr; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 scalar_t__ VORTEX_EISA (struct vortex_private*) ; 
 scalar_t__ VORTEX_PCI (struct vortex_private*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 struct vortex_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_name (scalar_t__) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vortex_get_drvinfo(struct net_device *dev,
					struct ethtool_drvinfo *info)
{
	struct vortex_private *vp = netdev_priv(dev);

	strlcpy(info->driver, DRV_NAME, sizeof(info->driver));
	if (VORTEX_PCI(vp)) {
		strlcpy(info->bus_info, pci_name(VORTEX_PCI(vp)),
			sizeof(info->bus_info));
	} else {
		if (VORTEX_EISA(vp))
			strlcpy(info->bus_info, dev_name(vp->gendev),
				sizeof(info->bus_info));
		else
			snprintf(info->bus_info, sizeof(info->bus_info),
				"EISA 0x%lx %d", dev->base_addr, dev->irq);
	}
}