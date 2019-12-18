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
struct mlx5e_priv {int /*<<< orphan*/  netdev; } ;
struct flow_cls_offload {int command; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  FLOW_CLS_DESTROY 130 
#define  FLOW_CLS_REPLACE 129 
#define  FLOW_CLS_STATS 128 
 int mlx5e_configure_flower (int /*<<< orphan*/ ,struct mlx5e_priv*,struct flow_cls_offload*,int) ; 
 int mlx5e_delete_flower (int /*<<< orphan*/ ,struct mlx5e_priv*,struct flow_cls_offload*,int) ; 
 int mlx5e_stats_flower (int /*<<< orphan*/ ,struct mlx5e_priv*,struct flow_cls_offload*,int) ; 

__attribute__((used)) static int
mlx5e_rep_setup_tc_cls_flower(struct mlx5e_priv *priv,
			      struct flow_cls_offload *cls_flower, int flags)
{
	switch (cls_flower->command) {
	case FLOW_CLS_REPLACE:
		return mlx5e_configure_flower(priv->netdev, priv, cls_flower,
					      flags);
	case FLOW_CLS_DESTROY:
		return mlx5e_delete_flower(priv->netdev, priv, cls_flower,
					   flags);
	case FLOW_CLS_STATS:
		return mlx5e_stats_flower(priv->netdev, priv, cls_flower,
					  flags);
	default:
		return -EOPNOTSUPP;
	}
}