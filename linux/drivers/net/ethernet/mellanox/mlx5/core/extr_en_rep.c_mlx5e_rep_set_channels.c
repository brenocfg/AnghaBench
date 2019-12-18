#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct net_device {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  t; } ;
struct TYPE_10__ {TYPE_3__ ft; } ;
struct TYPE_11__ {TYPE_4__ ttc; } ;
struct TYPE_7__ {int num_channels; } ;
struct TYPE_8__ {TYPE_1__ params; } ;
struct mlx5e_priv {int /*<<< orphan*/  netdev; TYPE_6__* direct_tir; TYPE_5__ fs; TYPE_2__ channels; } ;
struct mlx5_flow_destination {int /*<<< orphan*/  tir_num; int /*<<< orphan*/  type; int /*<<< orphan*/  ft; } ;
struct ethtool_channels {int combined_count; } ;
struct TYPE_12__ {int /*<<< orphan*/  tirn; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE ; 
 int /*<<< orphan*/  MLX5_FLOW_DESTINATION_TYPE_TIR ; 
 int mlx5e_ethtool_set_channels (struct mlx5e_priv*,struct ethtool_channels*) ; 
 int mlx5e_replace_rep_vport_rx_rule (struct mlx5e_priv*,struct mlx5_flow_destination*) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static int mlx5e_rep_set_channels(struct net_device *dev,
				  struct ethtool_channels *ch)
{
	struct mlx5e_priv *priv = netdev_priv(dev);
	u16 curr_channels_amount = priv->channels.params.num_channels;
	u32 new_channels_amount = ch->combined_count;
	struct mlx5_flow_destination new_dest;
	int err = 0;

	err = mlx5e_ethtool_set_channels(priv, ch);
	if (err)
		return err;

	if (curr_channels_amount == 1 && new_channels_amount > 1) {
		new_dest.type = MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE;
		new_dest.ft = priv->fs.ttc.ft.t;
	} else if (new_channels_amount == 1 && curr_channels_amount > 1) {
		new_dest.type = MLX5_FLOW_DESTINATION_TYPE_TIR;
		new_dest.tir_num = priv->direct_tir[0].tirn;
	} else {
		return 0;
	}

	err = mlx5e_replace_rep_vport_rx_rule(priv, &new_dest);
	if (err) {
		netdev_warn(priv->netdev, "Failed to update vport rx rule, when going from (%d) channels to (%d) channels\n",
			    curr_channels_amount, new_channels_amount);
		return err;
	}

	return 0;
}