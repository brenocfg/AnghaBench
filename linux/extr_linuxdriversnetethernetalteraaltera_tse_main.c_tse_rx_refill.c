#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct altera_tse_private {unsigned int rx_ring_size; scalar_t__ rx_cons; unsigned int rx_prod; TYPE_2__* rx_ring; TYPE_1__* dmaops; int /*<<< orphan*/  rx_dma_buf_sz; } ;
struct TYPE_5__ {int /*<<< orphan*/ * skb; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* add_rx_desc ) (struct altera_tse_private*,TYPE_2__*) ;} ;

/* Variables and functions */
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct altera_tse_private*,TYPE_2__*) ; 
 int tse_init_rx_buffer (struct altera_tse_private*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void tse_rx_refill(struct altera_tse_private *priv)
{
	unsigned int rxsize = priv->rx_ring_size;
	unsigned int entry;
	int ret;

	for (; priv->rx_cons - priv->rx_prod > 0;
			priv->rx_prod++) {
		entry = priv->rx_prod % rxsize;
		if (likely(priv->rx_ring[entry].skb == NULL)) {
			ret = tse_init_rx_buffer(priv, &priv->rx_ring[entry],
				priv->rx_dma_buf_sz);
			if (unlikely(ret != 0))
				break;
			priv->dmaops->add_rx_desc(priv, &priv->rx_ring[entry]);
		}
	}
}