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
struct mtk_tx_ring {scalar_t__ dma; } ;
struct mtk_tx_dma {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int txd_to_idx(struct mtk_tx_ring *ring, struct mtk_tx_dma *dma)
{
	return ((void *)dma - (void *)ring->dma) / sizeof(*dma);
}