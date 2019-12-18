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
struct mdio_ops {int /*<<< orphan*/  write; int /*<<< orphan*/  read; int /*<<< orphan*/  mode_support; } ;
struct cphy_ops {int /*<<< orphan*/  mmds; } ;
struct TYPE_2__ {int prtad; struct net_device* dev; int /*<<< orphan*/  mdio_write; int /*<<< orphan*/  mdio_read; int /*<<< orphan*/  mode_support; int /*<<< orphan*/  mmds; } ;
struct cphy {TYPE_1__ mdio; struct cphy_ops const* ops; struct adapter* adapter; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 struct adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static inline void cphy_init(struct cphy *phy, struct net_device *dev,
			     int phy_addr, const struct cphy_ops *phy_ops,
			     const struct mdio_ops *mdio_ops)
{
	struct adapter *adapter = netdev_priv(dev);
	phy->adapter = adapter;
	phy->ops     = phy_ops;
	if (mdio_ops) {
		phy->mdio.prtad = phy_addr;
		phy->mdio.mmds = phy_ops->mmds;
		phy->mdio.mode_support = mdio_ops->mode_support;
		phy->mdio.mdio_read = mdio_ops->read;
		phy->mdio.mdio_write = mdio_ops->write;
	}
	phy->mdio.dev = dev;
}