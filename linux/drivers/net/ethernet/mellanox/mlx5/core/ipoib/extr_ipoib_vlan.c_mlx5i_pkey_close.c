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
struct TYPE_2__ {int /*<<< orphan*/  qpn; } ;
struct mlx5i_priv {TYPE_1__ qp; } ;
struct mlx5e_priv {int /*<<< orphan*/  state_lock; int /*<<< orphan*/ ** tisn; int /*<<< orphan*/  channels; int /*<<< orphan*/  netdev; int /*<<< orphan*/  state; struct mlx5_core_dev* mdev; struct mlx5i_priv* ppriv; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_STATE_OPENED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_fs_remove_rx_underlay_qpn (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_close_channels (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_deactivate_priv_channels (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_destroy_tis (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 struct mlx5e_priv* mlx5i_epriv (struct net_device*) ; 
 int /*<<< orphan*/  mlx5i_uninit_underlay_qp (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx5i_pkey_close(struct net_device *netdev)
{
	struct mlx5e_priv *priv = mlx5i_epriv(netdev);
	struct mlx5i_priv *ipriv = priv->ppriv;
	struct mlx5_core_dev *mdev = priv->mdev;

	mutex_lock(&priv->state_lock);

	if (!test_bit(MLX5E_STATE_OPENED, &priv->state))
		goto unlock;

	clear_bit(MLX5E_STATE_OPENED, &priv->state);

	netif_carrier_off(priv->netdev);
	mlx5_fs_remove_rx_underlay_qpn(mdev, ipriv->qp.qpn);
	mlx5i_uninit_underlay_qp(priv);
	mlx5e_deactivate_priv_channels(priv);
	mlx5e_close_channels(&priv->channels);
	mlx5e_destroy_tis(mdev, priv->tisn[0][0]);
unlock:
	mutex_unlock(&priv->state_lock);
	return 0;
}