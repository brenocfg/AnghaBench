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
struct TYPE_4__ {int /*<<< orphan*/  dscp2prio; int /*<<< orphan*/  trust_state; } ;
struct TYPE_3__ {int /*<<< orphan*/  params; } ;
struct mlx5e_priv {TYPE_2__ dcbx_dp; struct mlx5_core_dev* mdev; TYPE_1__ channels; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_DSCP_SUPPORTED (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  MLX5_QPTS_TRUST_PCP ; 
 int mlx5_query_dscp2prio (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int mlx5_query_trust_state (struct mlx5_core_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_trust_update_tx_min_inline_mode (struct mlx5e_priv*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx5e_trust_initialize(struct mlx5e_priv *priv)
{
	struct mlx5_core_dev *mdev = priv->mdev;
	int err;

	priv->dcbx_dp.trust_state = MLX5_QPTS_TRUST_PCP;

	if (!MLX5_DSCP_SUPPORTED(mdev))
		return 0;

	err = mlx5_query_trust_state(priv->mdev, &priv->dcbx_dp.trust_state);
	if (err)
		return err;

	mlx5e_trust_update_tx_min_inline_mode(priv, &priv->channels.params);

	err = mlx5_query_dscp2prio(priv->mdev, priv->dcbx_dp.dscp2prio);
	if (err)
		return err;

	return 0;
}