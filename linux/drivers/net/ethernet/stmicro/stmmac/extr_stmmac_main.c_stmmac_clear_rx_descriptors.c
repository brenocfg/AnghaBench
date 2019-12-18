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
typedef  size_t u32 ;
struct stmmac_rx_queue {int /*<<< orphan*/ * dma_rx; TYPE_1__* dma_erx; } ;
struct stmmac_priv {int /*<<< orphan*/  dma_buf_sz; int /*<<< orphan*/  mode; int /*<<< orphan*/  use_riwt; scalar_t__ extend_desc; struct stmmac_rx_queue* rx_queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  basic; } ;

/* Variables and functions */
 int DMA_RX_SIZE ; 
 int /*<<< orphan*/  stmmac_init_rx_desc (struct stmmac_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stmmac_clear_rx_descriptors(struct stmmac_priv *priv, u32 queue)
{
	struct stmmac_rx_queue *rx_q = &priv->rx_queue[queue];
	int i;

	/* Clear the RX descriptors */
	for (i = 0; i < DMA_RX_SIZE; i++)
		if (priv->extend_desc)
			stmmac_init_rx_desc(priv, &rx_q->dma_erx[i].basic,
					priv->use_riwt, priv->mode,
					(i == DMA_RX_SIZE - 1),
					priv->dma_buf_sz);
		else
			stmmac_init_rx_desc(priv, &rx_q->dma_rx[i],
					priv->use_riwt, priv->mode,
					(i == DMA_RX_SIZE - 1),
					priv->dma_buf_sz);
}