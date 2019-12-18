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
struct net_device {int dummy; } ;
struct mlx5e_rep_indr_block_priv {TYPE_1__* rpriv; } ;
struct mlx5e_priv {int dummy; } ;
struct flow_cls_offload {int command; } ;
struct TYPE_2__ {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EGRESS ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ESW_OFFLOAD ; 
#define  FLOW_CLS_DESTROY 130 
#define  FLOW_CLS_REPLACE 129 
#define  FLOW_CLS_STATS 128 
 unsigned long MLX5_TC_FLAG (int /*<<< orphan*/ ) ; 
 int mlx5e_configure_flower (struct net_device*,struct mlx5e_priv*,struct flow_cls_offload*,unsigned long) ; 
 int mlx5e_delete_flower (struct net_device*,struct mlx5e_priv*,struct flow_cls_offload*,unsigned long) ; 
 int mlx5e_stats_flower (struct net_device*,struct mlx5e_priv*,struct flow_cls_offload*,unsigned long) ; 
 struct mlx5e_priv* netdev_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mlx5e_rep_indr_offload(struct net_device *netdev,
		       struct flow_cls_offload *flower,
		       struct mlx5e_rep_indr_block_priv *indr_priv)
{
	unsigned long flags = MLX5_TC_FLAG(EGRESS) | MLX5_TC_FLAG(ESW_OFFLOAD);
	struct mlx5e_priv *priv = netdev_priv(indr_priv->rpriv->netdev);
	int err = 0;

	switch (flower->command) {
	case FLOW_CLS_REPLACE:
		err = mlx5e_configure_flower(netdev, priv, flower, flags);
		break;
	case FLOW_CLS_DESTROY:
		err = mlx5e_delete_flower(netdev, priv, flower, flags);
		break;
	case FLOW_CLS_STATS:
		err = mlx5e_stats_flower(netdev, priv, flower, flags);
		break;
	default:
		err = -EOPNOTSUPP;
	}

	return err;
}