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
struct dim_cq_moder {int /*<<< orphan*/  pkts; int /*<<< orphan*/  usec; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_dim_enabled; struct dim_cq_moder tx_cq_moderation; int /*<<< orphan*/  rx_dim_enabled; struct dim_cq_moder rx_cq_moderation; } ;
struct TYPE_4__ {TYPE_1__ params; } ;
struct mlx5e_priv {TYPE_2__ channels; int /*<<< orphan*/  mdev; } ;
struct ethtool_coalesce {int /*<<< orphan*/  use_adaptive_tx_coalesce; int /*<<< orphan*/  tx_max_coalesced_frames; int /*<<< orphan*/  tx_coalesce_usecs; int /*<<< orphan*/  use_adaptive_rx_coalesce; int /*<<< orphan*/  rx_max_coalesced_frames; int /*<<< orphan*/  rx_coalesce_usecs; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  MLX5_CAP_GEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cq_moderation ; 

int mlx5e_ethtool_get_coalesce(struct mlx5e_priv *priv,
			       struct ethtool_coalesce *coal)
{
	struct dim_cq_moder *rx_moder, *tx_moder;

	if (!MLX5_CAP_GEN(priv->mdev, cq_moderation))
		return -EOPNOTSUPP;

	rx_moder = &priv->channels.params.rx_cq_moderation;
	coal->rx_coalesce_usecs		= rx_moder->usec;
	coal->rx_max_coalesced_frames	= rx_moder->pkts;
	coal->use_adaptive_rx_coalesce	= priv->channels.params.rx_dim_enabled;

	tx_moder = &priv->channels.params.tx_cq_moderation;
	coal->tx_coalesce_usecs		= tx_moder->usec;
	coal->tx_max_coalesced_frames	= tx_moder->pkts;
	coal->use_adaptive_tx_coalesce	= priv->channels.params.tx_dim_enabled;

	return 0;
}