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
struct mlx4_en_priv {int* tx_ring_num; int rx_ring_num; scalar_t__* rx_cq; int /*<<< orphan*/  stride; TYPE_2__* prof; scalar_t__* rx_ring; scalar_t__** tx_cq; scalar_t__** tx_ring; TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_ring_size; } ;
struct TYPE_3__ {int /*<<< orphan*/ * rx_cpu_rmap; } ;

/* Variables and functions */
 int MLX4_EN_NUM_TX_TYPES ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 int /*<<< orphan*/  mlx4_en_destroy_cq (struct mlx4_en_priv*,scalar_t__*) ; 
 int /*<<< orphan*/  mlx4_en_destroy_rx_ring (struct mlx4_en_priv*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_en_destroy_tx_ring (struct mlx4_en_priv*,scalar_t__*) ; 

__attribute__((used)) static void mlx4_en_free_resources(struct mlx4_en_priv *priv)
{
	int i, t;

#ifdef CONFIG_RFS_ACCEL
	priv->dev->rx_cpu_rmap = NULL;
#endif

	for (t = 0; t < MLX4_EN_NUM_TX_TYPES; t++) {
		for (i = 0; i < priv->tx_ring_num[t]; i++) {
			if (priv->tx_ring[t] && priv->tx_ring[t][i])
				mlx4_en_destroy_tx_ring(priv,
							&priv->tx_ring[t][i]);
			if (priv->tx_cq[t] && priv->tx_cq[t][i])
				mlx4_en_destroy_cq(priv, &priv->tx_cq[t][i]);
		}
		kfree(priv->tx_ring[t]);
		kfree(priv->tx_cq[t]);
	}

	for (i = 0; i < priv->rx_ring_num; i++) {
		if (priv->rx_ring[i])
			mlx4_en_destroy_rx_ring(priv, &priv->rx_ring[i],
				priv->prof->rx_ring_size, priv->stride);
		if (priv->rx_cq[i])
			mlx4_en_destroy_cq(priv, &priv->rx_cq[i]);
	}

}