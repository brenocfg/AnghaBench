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
struct TYPE_2__ {int /*<<< orphan*/  phy_id; } ;
struct nic {TYPE_1__ mii; } ;
struct net_device {int dummy; } ;
struct ethtool_link_ksettings {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMCR_RESET ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  e100_configure ; 
 int /*<<< orphan*/  e100_exec_cb (struct nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdio_write (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mii_ethtool_set_link_ksettings (TYPE_1__*,struct ethtool_link_ksettings const*) ; 
 struct nic* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int e100_set_link_ksettings(struct net_device *netdev,
				   const struct ethtool_link_ksettings *cmd)
{
	struct nic *nic = netdev_priv(netdev);
	int err;

	mdio_write(netdev, nic->mii.phy_id, MII_BMCR, BMCR_RESET);
	err = mii_ethtool_set_link_ksettings(&nic->mii, cmd);
	e100_exec_cb(nic, NULL, e100_configure);

	return err;
}