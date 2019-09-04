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
struct mlx4_spec_list {int dummy; } ;
struct mlx4_en_priv {int dummy; } ;
struct list_head {int dummy; } ;
struct ethtool_rxnfc {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int mlx4_en_ethtool_add_mac_rule_by_ipv4(struct mlx4_en_priv *priv,
						struct ethtool_rxnfc *cmd,
						struct list_head *rule_list_h,
						struct mlx4_spec_list *spec_l2,
						__be32 ipv4_dst)
{
#ifdef CONFIG_INET
	unsigned char mac[ETH_ALEN];

	if (!ipv4_is_multicast(ipv4_dst)) {
		if (cmd->fs.flow_type & FLOW_MAC_EXT)
			memcpy(&mac, cmd->fs.h_ext.h_dest, ETH_ALEN);
		else
			memcpy(&mac, priv->dev->dev_addr, ETH_ALEN);
	} else {
		ip_eth_mc_map(ipv4_dst, mac);
	}

	return mlx4_en_ethtool_add_mac_rule(cmd, rule_list_h, spec_l2, &mac[0]);
#else
	return -EINVAL;
#endif
}