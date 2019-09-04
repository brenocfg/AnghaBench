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
struct mlx5e_priv {int /*<<< orphan*/  state_lock; int /*<<< orphan*/  channels; int /*<<< orphan*/  netdev; int /*<<< orphan*/  state; struct mlx5_core_dev* mdev; struct mlx5i_priv* ppriv; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_STATE_OPENED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_fs_remove_rx_underlay_qpn (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_close_channels (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_deactivate_priv_channels (struct mlx5e_priv*) ; 
 struct mlx5e_priv* mlx5i_epriv (struct net_device*) ; 
 int /*<<< orphan*/  mlx5i_uninit_underlay_qp (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx5i_close(struct net_device *netdev)
{
	struct mlx5e_priv *epriv = mlx5i_epriv(netdev);
	struct mlx5i_priv *ipriv = epriv->ppriv;
	struct mlx5_core_dev *mdev = epriv->mdev;

	/* May already be CLOSED in case a previous configuration operation
	 * (e.g RX/TX queue size change) that involves close&open failed.
	 */
	mutex_lock(&epriv->state_lock);

	if (!test_bit(MLX5E_STATE_OPENED, &epriv->state))
		goto unlock;

	clear_bit(MLX5E_STATE_OPENED, &epriv->state);

	netif_carrier_off(epriv->netdev);
	mlx5_fs_remove_rx_underlay_qpn(mdev, ipriv->qp.qpn);
	mlx5e_deactivate_priv_channels(epriv);
	mlx5e_close_channels(&epriv->channels);
	mlx5i_uninit_underlay_qp(epriv);
unlock:
	mutex_unlock(&epriv->state_lock);
	return 0;
}