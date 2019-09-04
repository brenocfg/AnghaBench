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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct mlx5e_priv {int /*<<< orphan*/  state_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_PFLAG_RX_CQE_BASED_MODER ; 
 int /*<<< orphan*/  MLX5E_PFLAG_RX_CQE_COMPRESS ; 
 int /*<<< orphan*/  MLX5E_PFLAG_RX_STRIDING_RQ ; 
 int /*<<< orphan*/  MLX5E_PFLAG_TX_CQE_BASED_MODER ; 
 int mlx5e_handle_pflag (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_update_features (struct net_device*) ; 
 int /*<<< orphan*/  set_pflag_rx_cqe_based_moder ; 
 int /*<<< orphan*/  set_pflag_rx_cqe_compress ; 
 int /*<<< orphan*/  set_pflag_rx_striding_rq ; 
 int /*<<< orphan*/  set_pflag_tx_cqe_based_moder ; 

__attribute__((used)) static int mlx5e_set_priv_flags(struct net_device *netdev, u32 pflags)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);
	int err;

	mutex_lock(&priv->state_lock);
	err = mlx5e_handle_pflag(netdev, pflags,
				 MLX5E_PFLAG_RX_CQE_BASED_MODER,
				 set_pflag_rx_cqe_based_moder);
	if (err)
		goto out;

	err = mlx5e_handle_pflag(netdev, pflags,
				 MLX5E_PFLAG_TX_CQE_BASED_MODER,
				 set_pflag_tx_cqe_based_moder);
	if (err)
		goto out;

	err = mlx5e_handle_pflag(netdev, pflags,
				 MLX5E_PFLAG_RX_CQE_COMPRESS,
				 set_pflag_rx_cqe_compress);
	if (err)
		goto out;

	err = mlx5e_handle_pflag(netdev, pflags,
				 MLX5E_PFLAG_RX_STRIDING_RQ,
				 set_pflag_rx_striding_rq);

out:
	mutex_unlock(&priv->state_lock);

	/* Need to fix some features.. */
	netdev_update_features(netdev);

	return err;
}