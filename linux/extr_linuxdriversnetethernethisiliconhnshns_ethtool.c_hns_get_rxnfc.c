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
struct hns_nic_priv {TYPE_1__* ae_handle; } ;
struct ethtool_rxnfc {int cmd; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int /*<<< orphan*/  q_num; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETHTOOL_GRXRINGS 128 
 struct hns_nic_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int hns_get_rxnfc(struct net_device *netdev,
			 struct ethtool_rxnfc *cmd,
			 u32 *rule_locs)
{
	struct hns_nic_priv *priv = netdev_priv(netdev);

	switch (cmd->cmd) {
	case ETHTOOL_GRXRINGS:
		cmd->data = priv->ae_handle->q_num;
		break;
	default:
		return -EOPNOTSUPP;
	}

	return 0;
}