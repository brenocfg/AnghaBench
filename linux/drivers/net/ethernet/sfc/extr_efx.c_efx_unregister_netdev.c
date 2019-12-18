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
struct efx_nic {int /*<<< orphan*/  net_dev; TYPE_1__* pci_dev; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  dev_attr_mcdi_logging ; 
 int /*<<< orphan*/  dev_attr_phy_type ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ efx_dev_registered (struct efx_nic*) ; 
 struct efx_nic* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_name (TYPE_1__*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void efx_unregister_netdev(struct efx_nic *efx)
{
	if (!efx->net_dev)
		return;

	BUG_ON(netdev_priv(efx->net_dev) != efx);

	if (efx_dev_registered(efx)) {
		strlcpy(efx->name, pci_name(efx->pci_dev), sizeof(efx->name));
#ifdef CONFIG_SFC_MCDI_LOGGING
		device_remove_file(&efx->pci_dev->dev, &dev_attr_mcdi_logging);
#endif
		device_remove_file(&efx->pci_dev->dev, &dev_attr_phy_type);
		unregister_netdev(efx->net_dev);
	}
}