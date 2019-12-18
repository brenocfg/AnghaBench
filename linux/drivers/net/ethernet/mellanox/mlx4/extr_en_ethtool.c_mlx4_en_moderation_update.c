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
struct mlx4_en_priv {int* tx_ring_num; int rx_ring_num; TYPE_1__** rx_cq; scalar_t__ port_up; int /*<<< orphan*/ * last_moder_time; int /*<<< orphan*/  rx_usecs; int /*<<< orphan*/  rx_frames; scalar_t__ adaptive_rx_coal; TYPE_1__*** tx_cq; int /*<<< orphan*/  tx_usecs; int /*<<< orphan*/  tx_frames; } ;
struct TYPE_2__ {int /*<<< orphan*/  moder_time; int /*<<< orphan*/  moder_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_EN_AUTO_CONF ; 
 int MLX4_EN_NUM_TX_TYPES ; 
 int mlx4_en_set_cq_moder (struct mlx4_en_priv*,TYPE_1__*) ; 

__attribute__((used)) static int mlx4_en_moderation_update(struct mlx4_en_priv *priv)
{
	int i, t;
	int err = 0;

	for (t = 0 ; t < MLX4_EN_NUM_TX_TYPES; t++) {
		for (i = 0; i < priv->tx_ring_num[t]; i++) {
			priv->tx_cq[t][i]->moder_cnt = priv->tx_frames;
			priv->tx_cq[t][i]->moder_time = priv->tx_usecs;
			if (priv->port_up) {
				err = mlx4_en_set_cq_moder(priv,
							   priv->tx_cq[t][i]);
				if (err)
					return err;
			}
		}
	}

	if (priv->adaptive_rx_coal)
		return 0;

	for (i = 0; i < priv->rx_ring_num; i++) {
		priv->rx_cq[i]->moder_cnt = priv->rx_frames;
		priv->rx_cq[i]->moder_time = priv->rx_usecs;
		priv->last_moder_time[i] = MLX4_EN_AUTO_CONF;
		if (priv->port_up) {
			err = mlx4_en_set_cq_moder(priv, priv->rx_cq[i]);
			if (err)
				return err;
		}
	}

	return err;
}