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
typedef  unsigned int u32 ;
struct mlx4_en_tx_ring {unsigned int size; struct mlx4_en_tx_desc* buf; scalar_t__ bounce_buf; } ;
struct mlx4_en_tx_desc {int dummy; } ;
struct mlx4_en_priv {int dummy; } ;

/* Variables and functions */
 unsigned int LOG_TXBB_SIZE ; 
 int TXBB_SIZE ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static struct mlx4_en_tx_desc *mlx4_en_bounce_to_desc(struct mlx4_en_priv *priv,
						      struct mlx4_en_tx_ring *ring,
						      u32 index,
						      unsigned int desc_size)
{
	u32 copy = (ring->size - index) << LOG_TXBB_SIZE;
	int i;

	for (i = desc_size - copy - 4; i >= 0; i -= 4) {
		if ((i & (TXBB_SIZE - 1)) == 0)
			wmb();

		*((u32 *) (ring->buf + i)) =
			*((u32 *) (ring->bounce_buf + copy + i));
	}

	for (i = copy - 4; i >= 4 ; i -= 4) {
		if ((i & (TXBB_SIZE - 1)) == 0)
			wmb();

		*((u32 *)(ring->buf + (index << LOG_TXBB_SIZE) + i)) =
			*((u32 *) (ring->bounce_buf + i));
	}

	/* Return real descriptor location */
	return ring->buf + (index << LOG_TXBB_SIZE);
}