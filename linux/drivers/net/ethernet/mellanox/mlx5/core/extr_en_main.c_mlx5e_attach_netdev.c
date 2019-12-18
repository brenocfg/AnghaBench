#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mlx5e_profile {int (* init_tx ) (struct mlx5e_priv*) ;int (* init_rx ) (struct mlx5e_priv*) ;int /*<<< orphan*/  (* cleanup_tx ) (struct mlx5e_priv*) ;int /*<<< orphan*/  (* enable ) (struct mlx5e_priv*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  indirection_rqt; } ;
struct TYPE_4__ {int num_channels; } ;
struct TYPE_5__ {TYPE_1__ params; } ;
struct mlx5e_priv {TYPE_3__ rss_params; TYPE_2__ channels; int /*<<< orphan*/  mdev; int /*<<< orphan*/  state; struct mlx5e_profile* profile; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_INDIR_RQT_SIZE ; 
 int /*<<< orphan*/  MLX5E_STATE_DESTROYING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_core_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mlx5e_build_default_indir_rqt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mlx5e_get_max_num_channels (int /*<<< orphan*/ ) ; 
 int stub1 (struct mlx5e_priv*) ; 
 int stub2 (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  stub3 (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  stub4 (struct mlx5e_priv*) ; 

int mlx5e_attach_netdev(struct mlx5e_priv *priv)
{
	const struct mlx5e_profile *profile;
	int max_nch;
	int err;

	profile = priv->profile;
	clear_bit(MLX5E_STATE_DESTROYING, &priv->state);

	/* max number of channels may have changed */
	max_nch = mlx5e_get_max_num_channels(priv->mdev);
	if (priv->channels.params.num_channels > max_nch) {
		mlx5_core_warn(priv->mdev, "MLX5E: Reducing number of channels to %d\n", max_nch);
		priv->channels.params.num_channels = max_nch;
		mlx5e_build_default_indir_rqt(priv->rss_params.indirection_rqt,
					      MLX5E_INDIR_RQT_SIZE, max_nch);
	}

	err = profile->init_tx(priv);
	if (err)
		goto out;

	err = profile->init_rx(priv);
	if (err)
		goto err_cleanup_tx;

	if (profile->enable)
		profile->enable(priv);

	return 0;

err_cleanup_tx:
	profile->cleanup_tx(priv);

out:
	return err;
}