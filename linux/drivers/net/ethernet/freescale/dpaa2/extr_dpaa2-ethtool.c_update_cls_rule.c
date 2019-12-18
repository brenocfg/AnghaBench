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
struct ethtool_rx_flow_spec {int dummy; } ;
struct dpaa2_eth_priv {scalar_t__ rx_cls_fields; struct dpaa2_eth_cls_rule* cls_rules; int /*<<< orphan*/  rx_cls_enabled; } ;
struct dpaa2_eth_cls_rule {int in_use; struct ethtool_rx_flow_spec fs; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int do_cls_rule (struct net_device*,struct ethtool_rx_flow_spec*,int) ; 
 int dpaa2_eth_fs_count (struct dpaa2_eth_priv*) ; 
 int /*<<< orphan*/  dpaa2_eth_fs_mask_enabled (struct dpaa2_eth_priv*) ; 
 struct dpaa2_eth_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  num_rules (struct dpaa2_eth_priv*) ; 

__attribute__((used)) static int update_cls_rule(struct net_device *net_dev,
			   struct ethtool_rx_flow_spec *new_fs,
			   int location)
{
	struct dpaa2_eth_priv *priv = netdev_priv(net_dev);
	struct dpaa2_eth_cls_rule *rule;
	int err = -EINVAL;

	if (!priv->rx_cls_enabled)
		return -EOPNOTSUPP;

	if (location >= dpaa2_eth_fs_count(priv))
		return -EINVAL;

	rule = &priv->cls_rules[location];

	/* If a rule is present at the specified location, delete it. */
	if (rule->in_use) {
		err = do_cls_rule(net_dev, &rule->fs, false);
		if (err)
			return err;

		rule->in_use = 0;

		if (!dpaa2_eth_fs_mask_enabled(priv) && !num_rules(priv))
			priv->rx_cls_fields = 0;
	}

	/* If no new entry to add, return here */
	if (!new_fs)
		return err;

	err = do_cls_rule(net_dev, new_fs, true);
	if (err)
		return err;

	rule->in_use = 1;
	rule->fs = *new_fs;

	return 0;
}