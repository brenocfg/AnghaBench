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
struct net_device {int dummy; } ;
struct ethtool_rxnfc {int cmd; } ;
struct ena_adapter {int /*<<< orphan*/  ena_dev; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETHTOOL_SRXCLSRLDEL 130 
#define  ETHTOOL_SRXCLSRLINS 129 
#define  ETHTOOL_SRXFH 128 
 int /*<<< orphan*/  drv ; 
 int ena_set_rss_hash (int /*<<< orphan*/ ,struct ethtool_rxnfc*) ; 
 struct ena_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct ena_adapter*,int /*<<< orphan*/ ,struct net_device*,char*,int) ; 

__attribute__((used)) static int ena_set_rxnfc(struct net_device *netdev, struct ethtool_rxnfc *info)
{
	struct ena_adapter *adapter = netdev_priv(netdev);
	int rc = 0;

	switch (info->cmd) {
	case ETHTOOL_SRXFH:
		rc = ena_set_rss_hash(adapter->ena_dev, info);
		break;
	case ETHTOOL_SRXCLSRLDEL:
	case ETHTOOL_SRXCLSRLINS:
	default:
		netif_err(adapter, drv, netdev,
			  "Command parameter %d is not supported\n", info->cmd);
		rc = -EOPNOTSUPP;
	}

	return rc;
}