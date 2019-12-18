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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  num_channels; } ;
struct TYPE_4__ {TYPE_1__ params; } ;
struct mlx5e_priv {TYPE_2__ channels; } ;
struct ethtool_rxnfc {scalar_t__ cmd; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 scalar_t__ ETHTOOL_GRXRINGS ; 
 int mlx5e_ethtool_get_rxnfc (struct net_device*,struct ethtool_rxnfc*,int /*<<< orphan*/ *) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlx5e_get_rxnfc(struct net_device *dev, struct ethtool_rxnfc *info, u32 *rule_locs)
{
	struct mlx5e_priv *priv = netdev_priv(dev);

	/* ETHTOOL_GRXRINGS is needed by ethtool -x which is not part
	 * of rxnfc. We keep this logic out of mlx5e_ethtool_get_rxnfc,
	 * to avoid breaking "ethtool -x" when mlx5e_ethtool_get_rxnfc
	 * is compiled out via CONFIG_MLX5_EN_RXNFC=n.
	 */
	if (info->cmd == ETHTOOL_GRXRINGS) {
		info->data = priv->channels.params.num_channels;
		return 0;
	}

	return mlx5e_ethtool_get_rxnfc(dev, info, rule_locs);
}