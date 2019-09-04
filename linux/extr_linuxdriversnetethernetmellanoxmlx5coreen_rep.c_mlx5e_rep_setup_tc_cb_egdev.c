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
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  MLX5E_TC_EGRESS ; 
#define  TC_SETUP_CLSFLOWER 128 
 int mlx5e_rep_setup_tc_cls_flower (struct mlx5e_priv*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tc_cls_can_offload_and_chain0 (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int mlx5e_rep_setup_tc_cb_egdev(enum tc_setup_type type, void *type_data,
				       void *cb_priv)
{
	struct mlx5e_priv *priv = cb_priv;

	if (!tc_cls_can_offload_and_chain0(priv->netdev, type_data))
		return -EOPNOTSUPP;

	switch (type) {
	case TC_SETUP_CLSFLOWER:
		return mlx5e_rep_setup_tc_cls_flower(priv, type_data, MLX5E_TC_EGRESS);
	default:
		return -EOPNOTSUPP;
	}
}