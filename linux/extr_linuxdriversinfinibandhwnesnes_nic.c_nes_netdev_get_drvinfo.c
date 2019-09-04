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
struct net_device {int dummy; } ;
struct nes_vnic {TYPE_1__* nesdev; } ;
struct nes_adapter {int firmware_version; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  version; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  pcidev; struct nes_adapter* nesadapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int /*<<< orphan*/  DRV_VERSION ; 
 struct nes_vnic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void nes_netdev_get_drvinfo(struct net_device *netdev,
		struct ethtool_drvinfo *drvinfo)
{
	struct nes_vnic *nesvnic = netdev_priv(netdev);
	struct nes_adapter *nesadapter = nesvnic->nesdev->nesadapter;

	strlcpy(drvinfo->driver, DRV_NAME, sizeof(drvinfo->driver));
	strlcpy(drvinfo->bus_info, pci_name(nesvnic->nesdev->pcidev),
		sizeof(drvinfo->bus_info));
	snprintf(drvinfo->fw_version, sizeof(drvinfo->fw_version),
		 "%u.%u", nesadapter->firmware_version >> 16,
		 nesadapter->firmware_version & 0x000000ff);
	strlcpy(drvinfo->version, DRV_VERSION, sizeof(drvinfo->version));
}