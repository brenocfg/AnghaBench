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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct iavf_adapter {int /*<<< orphan*/  num_active_queues; } ;
struct ethtool_rxnfc {int cmd; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETHTOOL_GRXFH 129 
#define  ETHTOOL_GRXRINGS 128 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 struct iavf_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int iavf_get_rxnfc(struct net_device *netdev, struct ethtool_rxnfc *cmd,
			  u32 *rule_locs)
{
	struct iavf_adapter *adapter = netdev_priv(netdev);
	int ret = -EOPNOTSUPP;

	switch (cmd->cmd) {
	case ETHTOOL_GRXRINGS:
		cmd->data = adapter->num_active_queues;
		ret = 0;
		break;
	case ETHTOOL_GRXFH:
		netdev_info(netdev,
			    "RSS hash info is not available to vf, use pf.\n");
		break;
	default:
		break;
	}

	return ret;
}