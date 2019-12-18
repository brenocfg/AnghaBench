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
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  read_reg; } ;
struct TYPE_5__ {int /*<<< orphan*/  mdio; TYPE_1__ ops; } ;
struct TYPE_6__ {TYPE_2__ phy; } ;
struct ixgbe_adapter {TYPE_3__ hw; } ;
struct ifreq {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  SIOCGHWTSTAMP 130 
#define  SIOCGMIIPHY 129 
#define  SIOCSHWTSTAMP 128 
 int /*<<< orphan*/  if_mii (struct ifreq*) ; 
 int ixgbe_ptp_get_ts_config (struct ixgbe_adapter*,struct ifreq*) ; 
 int ixgbe_ptp_set_ts_config (struct ixgbe_adapter*,struct ifreq*) ; 
 int mdio_mii_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ixgbe_ioctl(struct net_device *netdev, struct ifreq *req, int cmd)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);

	switch (cmd) {
	case SIOCSHWTSTAMP:
		return ixgbe_ptp_set_ts_config(adapter, req);
	case SIOCGHWTSTAMP:
		return ixgbe_ptp_get_ts_config(adapter, req);
	case SIOCGMIIPHY:
		if (!adapter->hw.phy.ops.read_reg)
			return -EOPNOTSUPP;
		/* fall through */
	default:
		return mdio_mii_ioctl(&adapter->hw.phy.mdio, if_mii(req), cmd);
	}
}