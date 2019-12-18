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
struct mlx4_en_rx_ring {int dummy; } ;
struct mlx4_en_priv {int rx_ring_num; int /*<<< orphan*/ * prof; int /*<<< orphan*/  num_tx_rings_p_up; int /*<<< orphan*/ * tx_cq; int /*<<< orphan*/ * tx_ring; int /*<<< orphan*/ * tx_ring_num; int /*<<< orphan*/  hwtstamp_config; int /*<<< orphan*/ * rx_cq; int /*<<< orphan*/ * rx_ring; } ;
struct mlx4_en_port_profile {int dummy; } ;
struct mlx4_en_cq {int dummy; } ;

/* Variables and functions */
 int MLX4_EN_NUM_TX_TYPES ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void mlx4_en_update_priv(struct mlx4_en_priv *dst,
				struct mlx4_en_priv *src)
{
	int t;
	memcpy(dst->rx_ring, src->rx_ring,
	       sizeof(struct mlx4_en_rx_ring *) * src->rx_ring_num);
	memcpy(dst->rx_cq, src->rx_cq,
	       sizeof(struct mlx4_en_cq *) * src->rx_ring_num);
	memcpy(&dst->hwtstamp_config, &src->hwtstamp_config,
	       sizeof(dst->hwtstamp_config));
	for (t = 0; t < MLX4_EN_NUM_TX_TYPES; t++) {
		dst->tx_ring_num[t] = src->tx_ring_num[t];
		dst->tx_ring[t] = src->tx_ring[t];
		dst->tx_cq[t] = src->tx_cq[t];
	}
	dst->num_tx_rings_p_up = src->num_tx_rings_p_up;
	dst->rx_ring_num = src->rx_ring_num;
	memcpy(dst->prof, src->prof, sizeof(struct mlx4_en_port_profile));
}