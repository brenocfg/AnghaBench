#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct net_device {int dummy; } ;
struct TYPE_7__ {scalar_t__ cq_period_mode; } ;
struct TYPE_6__ {scalar_t__ cq_period_mode; } ;
struct TYPE_9__ {TYPE_2__ tx_cq_moderation; TYPE_1__ rx_cq_moderation; } ;
struct TYPE_8__ {TYPE_4__ params; } ;
struct mlx5e_priv {TYPE_3__ channels; int /*<<< orphan*/  state; struct mlx5_core_dev* mdev; } ;
struct mlx5e_channels {TYPE_4__ params; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  MLX5E_STATE_OPENED ; 
 int /*<<< orphan*/  MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CQ_PERIOD_MODE_START_FROM_CQE ; 
 scalar_t__ MLX5_CQ_PERIOD_MODE_START_FROM_EQE ; 
 int /*<<< orphan*/  cq_period_start_from_cqe ; 
 int mlx5e_safe_switch_channels (struct mlx5e_priv*,struct mlx5e_channels*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_set_rx_cq_mode_params (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  mlx5e_set_tx_cq_mode_params (TYPE_4__*,scalar_t__) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int set_pflag_cqe_based_moder(struct net_device *netdev, bool enable,
				     bool is_rx_cq)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);
	struct mlx5_core_dev *mdev = priv->mdev;
	struct mlx5e_channels new_channels = {};
	bool mode_changed;
	u8 cq_period_mode, current_cq_period_mode;

	cq_period_mode = enable ?
		MLX5_CQ_PERIOD_MODE_START_FROM_CQE :
		MLX5_CQ_PERIOD_MODE_START_FROM_EQE;
	current_cq_period_mode = is_rx_cq ?
		priv->channels.params.rx_cq_moderation.cq_period_mode :
		priv->channels.params.tx_cq_moderation.cq_period_mode;
	mode_changed = cq_period_mode != current_cq_period_mode;

	if (cq_period_mode == MLX5_CQ_PERIOD_MODE_START_FROM_CQE &&
	    !MLX5_CAP_GEN(mdev, cq_period_start_from_cqe))
		return -EOPNOTSUPP;

	if (!mode_changed)
		return 0;

	new_channels.params = priv->channels.params;
	if (is_rx_cq)
		mlx5e_set_rx_cq_mode_params(&new_channels.params, cq_period_mode);
	else
		mlx5e_set_tx_cq_mode_params(&new_channels.params, cq_period_mode);

	if (!test_bit(MLX5E_STATE_OPENED, &priv->state)) {
		priv->channels.params = new_channels.params;
		return 0;
	}

	return mlx5e_safe_switch_channels(priv, &new_channels, NULL);
}