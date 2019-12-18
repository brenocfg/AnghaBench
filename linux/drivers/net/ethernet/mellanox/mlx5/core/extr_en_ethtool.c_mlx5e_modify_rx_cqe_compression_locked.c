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
struct TYPE_2__ {int /*<<< orphan*/  params; } ;
struct mlx5e_priv {TYPE_1__ channels; int /*<<< orphan*/  state; int /*<<< orphan*/  mdev; } ;
struct mlx5e_channels {int /*<<< orphan*/  params; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV ; 
 int EOPNOTSUPP ; 
 int MLX5E_GET_PFLAG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5E_PFLAG_RX_CQE_COMPRESS ; 
 int /*<<< orphan*/  MLX5E_SET_PFLAG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MLX5E_STATE_OPENED ; 
 int /*<<< orphan*/  MLX5_CAP_GEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cqe_compression ; 
 int /*<<< orphan*/  mlx5e_dbg (int /*<<< orphan*/ ,struct mlx5e_priv*,char*,char*) ; 
 int mlx5e_safe_switch_channels (struct mlx5e_priv*,struct mlx5e_channels*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int mlx5e_modify_rx_cqe_compression_locked(struct mlx5e_priv *priv, bool new_val)
{
	bool curr_val = MLX5E_GET_PFLAG(&priv->channels.params, MLX5E_PFLAG_RX_CQE_COMPRESS);
	struct mlx5e_channels new_channels = {};
	int err = 0;

	if (!MLX5_CAP_GEN(priv->mdev, cqe_compression))
		return new_val ? -EOPNOTSUPP : 0;

	if (curr_val == new_val)
		return 0;

	new_channels.params = priv->channels.params;
	MLX5E_SET_PFLAG(&new_channels.params, MLX5E_PFLAG_RX_CQE_COMPRESS, new_val);

	if (!test_bit(MLX5E_STATE_OPENED, &priv->state)) {
		priv->channels.params = new_channels.params;
		return 0;
	}

	err = mlx5e_safe_switch_channels(priv, &new_channels, NULL);
	if (err)
		return err;

	mlx5e_dbg(DRV, priv, "MLX5E: RxCqeCmprss was turned %s\n",
		  MLX5E_GET_PFLAG(&priv->channels.params,
				  MLX5E_PFLAG_RX_CQE_COMPRESS) ? "ON" : "OFF");

	return 0;
}