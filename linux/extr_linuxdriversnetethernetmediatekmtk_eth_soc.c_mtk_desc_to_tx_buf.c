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
struct mtk_tx_ring {struct mtk_tx_buf* buf; struct mtk_tx_dma* dma; } ;
struct mtk_tx_dma {int dummy; } ;
struct mtk_tx_buf {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct mtk_tx_buf *mtk_desc_to_tx_buf(struct mtk_tx_ring *ring,
						    struct mtk_tx_dma *txd)
{
	int idx = txd - ring->dma;

	return &ring->buf[idx];
}