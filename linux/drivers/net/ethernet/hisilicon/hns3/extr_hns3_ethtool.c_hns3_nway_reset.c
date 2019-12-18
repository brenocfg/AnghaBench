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
struct phy_device {int dummy; } ;
struct net_device {struct phy_device* phydev; } ;
struct hnae3_handle {TYPE_1__* pdev; TYPE_2__* ae_algo; } ;
struct hnae3_ae_ops {int (* get_autoneg ) (struct hnae3_handle*) ;int (* restart_autoneg ) (struct hnae3_handle*) ;} ;
struct TYPE_4__ {struct hnae3_ae_ops* ops; } ;
struct TYPE_3__ {int revision; } ;

/* Variables and functions */
 int AUTONEG_ENABLE ; 
 int EBUSY ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  drv ; 
 int genphy_restart_aneg (struct phy_device*) ; 
 struct hnae3_handle* hns3_get_handle (struct net_device*) ; 
 scalar_t__ hns3_nic_resetting (struct net_device*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_dbg (struct hnae3_handle*,int /*<<< orphan*/ ,struct net_device*,char*,char*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int stub1 (struct hnae3_handle*) ; 
 int stub2 (struct hnae3_handle*) ; 

__attribute__((used)) static int hns3_nway_reset(struct net_device *netdev)
{
	struct hnae3_handle *handle = hns3_get_handle(netdev);
	const struct hnae3_ae_ops *ops = handle->ae_algo->ops;
	struct phy_device *phy = netdev->phydev;
	int autoneg;

	if (!netif_running(netdev))
		return 0;

	if (hns3_nic_resetting(netdev)) {
		netdev_err(netdev, "dev resetting!");
		return -EBUSY;
	}

	if (!ops->get_autoneg || !ops->restart_autoneg)
		return -EOPNOTSUPP;

	autoneg = ops->get_autoneg(handle);
	if (autoneg != AUTONEG_ENABLE) {
		netdev_err(netdev,
			   "Autoneg is off, don't support to restart it\n");
		return -EINVAL;
	}

	netif_dbg(handle, drv, netdev,
		  "nway reset (using %s)\n", phy ? "phy" : "mac");

	if (phy)
		return genphy_restart_aneg(phy);

	if (handle->pdev->revision == 0x20)
		return -EOPNOTSUPP;

	return ops->restart_autoneg(handle);
}