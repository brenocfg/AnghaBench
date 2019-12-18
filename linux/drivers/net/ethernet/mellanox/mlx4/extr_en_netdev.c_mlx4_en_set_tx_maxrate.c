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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct mlx4_update_qp_params {int rate_val; scalar_t__ rate_unit; } ;
struct mlx4_en_tx_ring {int /*<<< orphan*/  qpn; } ;
struct mlx4_en_priv {TYPE_2__* mdev; struct mlx4_en_tx_ring*** tx_ring; } ;
struct TYPE_4__ {int flags2; } ;
struct TYPE_6__ {TYPE_1__ caps; } ;
struct TYPE_5__ {TYPE_3__* dev; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int MLX4_DEV_CAP_FLAG2_QP_RATE_LIMIT ; 
 scalar_t__ MLX4_QP_RATE_LIMIT_GBS ; 
 scalar_t__ MLX4_QP_RATE_LIMIT_MBS ; 
 int /*<<< orphan*/  MLX4_UPDATE_QP_RATE_LIMIT ; 
 size_t TX ; 
 int mlx4_update_qp (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mlx4_update_qp_params*) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlx4_en_set_tx_maxrate(struct net_device *dev, int queue_index, u32 maxrate)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);
	struct mlx4_en_tx_ring *tx_ring = priv->tx_ring[TX][queue_index];
	struct mlx4_update_qp_params params;
	int err;

	if (!(priv->mdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_QP_RATE_LIMIT))
		return -EOPNOTSUPP;

	/* rate provided to us in Mbs, check if it fits into 12 bits, if not use Gbs */
	if (maxrate >> 12) {
		params.rate_unit = MLX4_QP_RATE_LIMIT_GBS;
		params.rate_val  = maxrate / 1000;
	} else if (maxrate) {
		params.rate_unit = MLX4_QP_RATE_LIMIT_MBS;
		params.rate_val  = maxrate;
	} else { /* zero serves to revoke the QP rate-limitation */
		params.rate_unit = 0;
		params.rate_val  = 0;
	}

	err = mlx4_update_qp(priv->mdev->dev, tx_ring->qpn, MLX4_UPDATE_QP_RATE_LIMIT,
			     &params);
	return err;
}