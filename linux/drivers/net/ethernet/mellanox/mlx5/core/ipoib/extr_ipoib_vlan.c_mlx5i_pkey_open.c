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
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  qpn; } ;
struct mlx5i_priv {TYPE_2__ qp; } ;
struct mlx5e_priv {int /*<<< orphan*/  state_lock; int /*<<< orphan*/  state; int /*<<< orphan*/ ** tisn; TYPE_1__* profile; int /*<<< orphan*/  channels; struct mlx5_core_dev* mdev; struct mlx5i_priv* ppriv; } ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* update_rx ) (struct mlx5e_priv*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_STATE_OPENED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,int) ; 
 int mlx5_fs_add_rx_underlay_qpn (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_fs_remove_rx_underlay_qpn (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_activate_priv_channels (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_destroy_tis (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int mlx5e_open_channels (struct mlx5e_priv*,int /*<<< orphan*/ *) ; 
 int mlx5i_create_tis (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mlx5e_priv* mlx5i_epriv (struct net_device*) ; 
 int mlx5i_init_underlay_qp (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5i_uninit_underlay_qp (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mlx5e_priv*) ; 

__attribute__((used)) static int mlx5i_pkey_open(struct net_device *netdev)
{
	struct mlx5e_priv *epriv = mlx5i_epriv(netdev);
	struct mlx5i_priv *ipriv = epriv->ppriv;
	struct mlx5_core_dev *mdev = epriv->mdev;
	int err;

	mutex_lock(&epriv->state_lock);

	set_bit(MLX5E_STATE_OPENED, &epriv->state);

	err = mlx5i_init_underlay_qp(epriv);
	if (err) {
		mlx5_core_warn(mdev, "prepare child underlay qp state failed, %d\n", err);
		goto err_release_lock;
	}

	err = mlx5_fs_add_rx_underlay_qpn(mdev, ipriv->qp.qpn);
	if (err) {
		mlx5_core_warn(mdev, "attach child underlay qp to ft failed, %d\n", err);
		goto err_unint_underlay_qp;
	}

	err = mlx5i_create_tis(mdev, ipriv->qp.qpn, &epriv->tisn[0][0]);
	if (err) {
		mlx5_core_warn(mdev, "create child tis failed, %d\n", err);
		goto err_remove_rx_uderlay_qp;
	}

	err = mlx5e_open_channels(epriv, &epriv->channels);
	if (err) {
		mlx5_core_warn(mdev, "opening child channels failed, %d\n", err);
		goto err_clear_state_opened_flag;
	}
	epriv->profile->update_rx(epriv);
	mlx5e_activate_priv_channels(epriv);
	mutex_unlock(&epriv->state_lock);

	return 0;

err_clear_state_opened_flag:
	mlx5e_destroy_tis(mdev, epriv->tisn[0][0]);
err_remove_rx_uderlay_qp:
	mlx5_fs_remove_rx_underlay_qpn(mdev, ipriv->qp.qpn);
err_unint_underlay_qp:
	mlx5i_uninit_underlay_qp(epriv);
err_release_lock:
	clear_bit(MLX5E_STATE_OPENED, &epriv->state);
	mutex_unlock(&epriv->state_lock);
	return err;
}