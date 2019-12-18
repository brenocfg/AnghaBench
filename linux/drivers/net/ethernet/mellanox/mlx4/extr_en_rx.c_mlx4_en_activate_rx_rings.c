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
struct mlx4_en_rx_ring {int stride; int buf; int buf_size; int size; scalar_t__ actual_size; scalar_t__ size_mask; scalar_t__ log_stride; int /*<<< orphan*/  cqn; scalar_t__ cons; scalar_t__ prod; } ;
struct mlx4_en_rx_desc {int dummy; } ;
struct mlx4_en_priv {int num_frags; int rx_ring_num; struct mlx4_en_rx_ring** rx_ring; TYPE_2__** rx_cq; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_3__ {int /*<<< orphan*/  cqn; } ;
struct TYPE_4__ {TYPE_1__ mcq; } ;

/* Variables and functions */
 int DS_SIZE ; 
 int STAMP_SHIFT ; 
 int TXBB_SIZE ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 scalar_t__ ffs (int) ; 
 int /*<<< orphan*/  memset (int,int /*<<< orphan*/ ,int) ; 
 int mlx4_en_fill_rx_buffers (struct mlx4_en_priv*) ; 
 int /*<<< orphan*/  mlx4_en_free_rx_buf (struct mlx4_en_priv*,struct mlx4_en_rx_ring*) ; 
 int /*<<< orphan*/  mlx4_en_init_rx_desc (struct mlx4_en_priv*,struct mlx4_en_rx_ring*,int) ; 
 int /*<<< orphan*/  mlx4_en_update_rx_prod_db (struct mlx4_en_rx_ring*) ; 
 int roundup_pow_of_two (int) ; 

int mlx4_en_activate_rx_rings(struct mlx4_en_priv *priv)
{
	struct mlx4_en_rx_ring *ring;
	int i;
	int ring_ind;
	int err;
	int stride = roundup_pow_of_two(sizeof(struct mlx4_en_rx_desc) +
					DS_SIZE * priv->num_frags);

	for (ring_ind = 0; ring_ind < priv->rx_ring_num; ring_ind++) {
		ring = priv->rx_ring[ring_ind];

		ring->prod = 0;
		ring->cons = 0;
		ring->actual_size = 0;
		ring->cqn = priv->rx_cq[ring_ind]->mcq.cqn;

		ring->stride = stride;
		if (ring->stride <= TXBB_SIZE) {
			/* Stamp first unused send wqe */
			__be32 *ptr = (__be32 *)ring->buf;
			__be32 stamp = cpu_to_be32(1 << STAMP_SHIFT);
			*ptr = stamp;
			/* Move pointer to start of rx section */
			ring->buf += TXBB_SIZE;
		}

		ring->log_stride = ffs(ring->stride) - 1;
		ring->buf_size = ring->size * ring->stride;

		memset(ring->buf, 0, ring->buf_size);
		mlx4_en_update_rx_prod_db(ring);

		/* Initialize all descriptors */
		for (i = 0; i < ring->size; i++)
			mlx4_en_init_rx_desc(priv, ring, i);
	}
	err = mlx4_en_fill_rx_buffers(priv);
	if (err)
		goto err_buffers;

	for (ring_ind = 0; ring_ind < priv->rx_ring_num; ring_ind++) {
		ring = priv->rx_ring[ring_ind];

		ring->size_mask = ring->actual_size - 1;
		mlx4_en_update_rx_prod_db(ring);
	}

	return 0;

err_buffers:
	for (ring_ind = 0; ring_ind < priv->rx_ring_num; ring_ind++)
		mlx4_en_free_rx_buf(priv, priv->rx_ring[ring_ind]);

	ring_ind = priv->rx_ring_num - 1;
	while (ring_ind >= 0) {
		if (priv->rx_ring[ring_ind]->stride <= TXBB_SIZE)
			priv->rx_ring[ring_ind]->buf -= TXBB_SIZE;
		ring_ind--;
	}
	return err;
}