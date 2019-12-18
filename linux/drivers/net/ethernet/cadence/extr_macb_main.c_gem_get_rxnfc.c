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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  count; } ;
struct macb {TYPE_1__ rx_fs_list; int /*<<< orphan*/  num_queues; } ;
struct ethtool_rxnfc {int cmd; int /*<<< orphan*/  rule_cnt; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETHTOOL_GRXCLSRLALL 131 
#define  ETHTOOL_GRXCLSRLCNT 130 
#define  ETHTOOL_GRXCLSRULE 129 
#define  ETHTOOL_GRXRINGS 128 
 int gem_get_all_flow_entries (struct net_device*,struct ethtool_rxnfc*,int /*<<< orphan*/ *) ; 
 int gem_get_flow_entry (struct net_device*,struct ethtool_rxnfc*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 struct macb* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int gem_get_rxnfc(struct net_device *netdev, struct ethtool_rxnfc *cmd,
		u32 *rule_locs)
{
	struct macb *bp = netdev_priv(netdev);
	int ret = 0;

	switch (cmd->cmd) {
	case ETHTOOL_GRXRINGS:
		cmd->data = bp->num_queues;
		break;
	case ETHTOOL_GRXCLSRLCNT:
		cmd->rule_cnt = bp->rx_fs_list.count;
		break;
	case ETHTOOL_GRXCLSRULE:
		ret = gem_get_flow_entry(netdev, cmd);
		break;
	case ETHTOOL_GRXCLSRLALL:
		ret = gem_get_all_flow_entries(netdev, cmd, rule_locs);
		break;
	default:
		netdev_err(netdev,
			  "Command parameter %d is not supported\n", cmd->cmd);
		ret = -EOPNOTSUPP;
	}

	return ret;
}