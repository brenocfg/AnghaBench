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
struct mtk_tx_ring {int dma_pdma; int dma; } ;
struct mtk_tx_dma {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct mtk_tx_dma *qdma_to_pdma(struct mtk_tx_ring *ring,
				       struct mtk_tx_dma *dma)
{
	return ring->dma_pdma - ring->dma + dma;
}