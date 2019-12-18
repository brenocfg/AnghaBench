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
struct ef4_nic {int /*<<< orphan*/  net_dev; TYPE_1__* pci_dev; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  dev_attr_phy_type ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ef4_dev_registered (struct ef4_nic*) ; 
 struct ef4_nic* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_name (TYPE_1__*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ef4_unregister_netdev(struct ef4_nic *efx)
{
	if (!efx->net_dev)
		return;

	BUG_ON(netdev_priv(efx->net_dev) != efx);

	if (ef4_dev_registered(efx)) {
		strlcpy(efx->name, pci_name(efx->pci_dev), sizeof(efx->name));
		device_remove_file(&efx->pci_dev->dev, &dev_attr_phy_type);
		unregister_netdev(efx->net_dev);
	}
}