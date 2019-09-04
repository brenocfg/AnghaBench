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
struct gfar_private {TYPE_1__ rx_list; int /*<<< orphan*/  num_rx_queues; } ;
struct ethtool_rxnfc {int cmd; int /*<<< orphan*/  rule_cnt; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int EINVAL ; 
#define  ETHTOOL_GRXCLSRLALL 131 
#define  ETHTOOL_GRXCLSRLCNT 130 
#define  ETHTOOL_GRXCLSRULE 129 
#define  ETHTOOL_GRXRINGS 128 
 int gfar_get_cls (struct gfar_private*,struct ethtool_rxnfc*) ; 
 int gfar_get_cls_all (struct gfar_private*,struct ethtool_rxnfc*,int /*<<< orphan*/ *) ; 
 struct gfar_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int gfar_get_nfc(struct net_device *dev, struct ethtool_rxnfc *cmd,
			u32 *rule_locs)
{
	struct gfar_private *priv = netdev_priv(dev);
	int ret = 0;

	switch (cmd->cmd) {
	case ETHTOOL_GRXRINGS:
		cmd->data = priv->num_rx_queues;
		break;
	case ETHTOOL_GRXCLSRLCNT:
		cmd->rule_cnt = priv->rx_list.count;
		break;
	case ETHTOOL_GRXCLSRULE:
		ret = gfar_get_cls(priv, cmd);
		break;
	case ETHTOOL_GRXCLSRLALL:
		ret = gfar_get_cls_all(priv, cmd, rule_locs);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}