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
typedef  scalar_t__ u8 ;
struct net_device {int mtu; } ;
struct TYPE_3__ {int refcnt; } ;
struct mlx5e_params {int sw_mtu; scalar_t__ rq_wq_type; scalar_t__ xdp_prog; int /*<<< orphan*/  lro_en; } ;
struct TYPE_4__ {struct mlx5e_params params; } ;
struct mlx5e_priv {int /*<<< orphan*/  state_lock; TYPE_1__ xsk; int /*<<< orphan*/  mdev; TYPE_2__ channels; int /*<<< orphan*/  state; } ;
struct mlx5e_channels {struct mlx5e_params params; } ;
typedef  int /*<<< orphan*/  (* change_hw_mtu_cb ) (struct mlx5e_priv*) ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MLX5E_STATE_OPENED ; 
 scalar_t__ MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ ; 
 scalar_t__ mlx5e_mpwqe_log_pkts_per_wqe (struct mlx5e_params*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_rx_is_linear_skb (struct mlx5e_params*,int /*<<< orphan*/ *) ; 
 int mlx5e_rx_mpwqe_is_linear_skb (int /*<<< orphan*/ ,struct mlx5e_params*,int /*<<< orphan*/ *) ; 
 int mlx5e_safe_switch_channels (struct mlx5e_priv*,struct mlx5e_channels*,int /*<<< orphan*/  (*) (struct mlx5e_priv*)) ; 
 int /*<<< orphan*/  mlx5e_xdp_max_mtu (struct mlx5e_params*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_xsk_validate_mtu (struct net_device*,TYPE_2__*,struct mlx5e_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int,int /*<<< orphan*/ ) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int mlx5e_change_mtu(struct net_device *netdev, int new_mtu,
		     change_hw_mtu_cb set_mtu_cb)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);
	struct mlx5e_channels new_channels = {};
	struct mlx5e_params *params;
	int err = 0;
	bool reset;

	mutex_lock(&priv->state_lock);

	params = &priv->channels.params;

	reset = !params->lro_en;
	reset = reset && test_bit(MLX5E_STATE_OPENED, &priv->state);

	new_channels.params = *params;
	new_channels.params.sw_mtu = new_mtu;

	if (params->xdp_prog &&
	    !mlx5e_rx_is_linear_skb(&new_channels.params, NULL)) {
		netdev_err(netdev, "MTU(%d) > %d is not allowed while XDP enabled\n",
			   new_mtu, mlx5e_xdp_max_mtu(params, NULL));
		err = -EINVAL;
		goto out;
	}

	if (priv->xsk.refcnt &&
	    !mlx5e_xsk_validate_mtu(netdev, &priv->channels,
				    &new_channels.params, priv->mdev)) {
		err = -EINVAL;
		goto out;
	}

	if (params->rq_wq_type == MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ) {
		bool is_linear = mlx5e_rx_mpwqe_is_linear_skb(priv->mdev,
							      &new_channels.params,
							      NULL);
		u8 ppw_old = mlx5e_mpwqe_log_pkts_per_wqe(params, NULL);
		u8 ppw_new = mlx5e_mpwqe_log_pkts_per_wqe(&new_channels.params, NULL);

		/* If XSK is active, XSK RQs are linear. */
		is_linear |= priv->xsk.refcnt;

		/* Always reset in linear mode - hw_mtu is used in data path. */
		reset = reset && (is_linear || (ppw_old != ppw_new));
	}

	if (!reset) {
		params->sw_mtu = new_mtu;
		if (set_mtu_cb)
			set_mtu_cb(priv);
		netdev->mtu = params->sw_mtu;
		goto out;
	}

	err = mlx5e_safe_switch_channels(priv, &new_channels, set_mtu_cb);
	if (err)
		goto out;

	netdev->mtu = new_channels.params.sw_mtu;

out:
	mutex_unlock(&priv->state_lock);
	return err;
}