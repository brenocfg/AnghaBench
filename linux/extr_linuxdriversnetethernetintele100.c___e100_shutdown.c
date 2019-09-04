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
typedef  int u16 ;
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  phy_id; } ;
struct nic {int flags; scalar_t__ phy; TYPE_1__ mii; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int E100_82552_ANEG_NOW ; 
 int E100_82552_REV_ANEG ; 
 int /*<<< orphan*/  E100_82552_SMARTSPEED ; 
 int e100_asf (struct nic*) ; 
 int /*<<< orphan*/  e100_down (struct nic*) ; 
 int mdio_read (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdio_write (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  pci_clear_master (struct pci_dev*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 scalar_t__ phy_82552_v ; 
 int wol_magic ; 

__attribute__((used)) static void __e100_shutdown(struct pci_dev *pdev, bool *enable_wake)
{
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct nic *nic = netdev_priv(netdev);

	if (netif_running(netdev))
		e100_down(nic);
	netif_device_detach(netdev);

	pci_save_state(pdev);

	if ((nic->flags & wol_magic) | e100_asf(nic)) {
		/* enable reverse auto-negotiation */
		if (nic->phy == phy_82552_v) {
			u16 smartspeed = mdio_read(netdev, nic->mii.phy_id,
			                           E100_82552_SMARTSPEED);

			mdio_write(netdev, nic->mii.phy_id,
			           E100_82552_SMARTSPEED, smartspeed |
			           E100_82552_REV_ANEG | E100_82552_ANEG_NOW);
		}
		*enable_wake = true;
	} else {
		*enable_wake = false;
	}

	pci_clear_master(pdev);
}