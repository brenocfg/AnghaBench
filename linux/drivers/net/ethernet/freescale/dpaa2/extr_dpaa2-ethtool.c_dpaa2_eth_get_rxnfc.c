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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int location; } ;
struct ethtool_rxnfc {int cmd; int data; int rule_cnt; TYPE_1__ fs; } ;
struct dpaa2_eth_priv {int rx_hash_fields; TYPE_2__* cls_rules; } ;
struct TYPE_4__ {int /*<<< orphan*/  in_use; TYPE_1__ fs; } ;

/* Variables and functions */
 int EINVAL ; 
 int EMSGSIZE ; 
 int EOPNOTSUPP ; 
#define  ETHTOOL_GRXCLSRLALL 132 
#define  ETHTOOL_GRXCLSRLCNT 131 
#define  ETHTOOL_GRXCLSRULE 130 
#define  ETHTOOL_GRXFH 129 
#define  ETHTOOL_GRXRINGS 128 
 int array_index_nospec (int,int) ; 
 int dpaa2_eth_fs_count (struct dpaa2_eth_priv*) ; 
 int dpaa2_eth_queue_count (struct dpaa2_eth_priv*) ; 
 struct dpaa2_eth_priv* netdev_priv (struct net_device*) ; 
 int num_rules (struct dpaa2_eth_priv*) ; 

__attribute__((used)) static int dpaa2_eth_get_rxnfc(struct net_device *net_dev,
			       struct ethtool_rxnfc *rxnfc, u32 *rule_locs)
{
	struct dpaa2_eth_priv *priv = netdev_priv(net_dev);
	int max_rules = dpaa2_eth_fs_count(priv);
	int i, j = 0;

	switch (rxnfc->cmd) {
	case ETHTOOL_GRXFH:
		/* we purposely ignore cmd->flow_type for now, because the
		 * classifier only supports a single set of fields for all
		 * protocols
		 */
		rxnfc->data = priv->rx_hash_fields;
		break;
	case ETHTOOL_GRXRINGS:
		rxnfc->data = dpaa2_eth_queue_count(priv);
		break;
	case ETHTOOL_GRXCLSRLCNT:
		rxnfc->rule_cnt = 0;
		rxnfc->rule_cnt = num_rules(priv);
		rxnfc->data = max_rules;
		break;
	case ETHTOOL_GRXCLSRULE:
		if (rxnfc->fs.location >= max_rules)
			return -EINVAL;
		rxnfc->fs.location = array_index_nospec(rxnfc->fs.location,
							max_rules);
		if (!priv->cls_rules[rxnfc->fs.location].in_use)
			return -EINVAL;
		rxnfc->fs = priv->cls_rules[rxnfc->fs.location].fs;
		break;
	case ETHTOOL_GRXCLSRLALL:
		for (i = 0; i < max_rules; i++) {
			if (!priv->cls_rules[i].in_use)
				continue;
			if (j == rxnfc->rule_cnt)
				return -EMSGSIZE;
			rule_locs[j++] = i;
		}
		rxnfc->rule_cnt = j;
		rxnfc->data = max_rules;
		break;
	default:
		return -EOPNOTSUPP;
	}

	return 0;
}