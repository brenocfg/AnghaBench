#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_6__ {scalar_t__ lro_en; } ;
struct TYPE_5__ {TYPE_2__ params; } ;
struct mlx5e_priv {TYPE_1__ channels; int /*<<< orphan*/  state; struct mlx5_core_dev* mdev; } ;
struct mlx5e_channels {TYPE_2__ params; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  MLX5E_PFLAG_RX_STRIDING_RQ ; 
 int /*<<< orphan*/  MLX5E_SET_PFLAG (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MLX5E_STATE_OPENED ; 
 int /*<<< orphan*/  mlx5e_check_fragmented_striding_rq_cap (struct mlx5_core_dev*) ; 
 int mlx5e_safe_switch_channels (struct mlx5e_priv*,struct mlx5e_channels*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_set_rq_type (struct mlx5_core_dev*,TYPE_2__*) ; 
 int /*<<< orphan*/  mlx5e_striding_rq_possible (struct mlx5_core_dev*,TYPE_2__*) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int set_pflag_rx_striding_rq(struct net_device *netdev, bool enable)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);
	struct mlx5_core_dev *mdev = priv->mdev;
	struct mlx5e_channels new_channels = {};

	if (enable) {
		if (!mlx5e_check_fragmented_striding_rq_cap(mdev))
			return -EOPNOTSUPP;
		if (!mlx5e_striding_rq_possible(mdev, &priv->channels.params))
			return -EINVAL;
	} else if (priv->channels.params.lro_en) {
		netdev_warn(netdev, "Can't set legacy RQ with LRO, disable LRO first\n");
		return -EINVAL;
	}

	new_channels.params = priv->channels.params;

	MLX5E_SET_PFLAG(&new_channels.params, MLX5E_PFLAG_RX_STRIDING_RQ, enable);
	mlx5e_set_rq_type(mdev, &new_channels.params);

	if (!test_bit(MLX5E_STATE_OPENED, &priv->state)) {
		priv->channels.params = new_channels.params;
		return 0;
	}

	return mlx5e_safe_switch_channels(priv, &new_channels, NULL);
}