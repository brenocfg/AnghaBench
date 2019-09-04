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
typedef  int /*<<< orphan*/  u32 ;
struct bcmgenet_priv {scalar_t__ base; } ;
typedef  enum dma_ring_reg { ____Placeholder_dma_ring_reg } dma_ring_reg ;

/* Variables and functions */
 unsigned int DMA_RING_SIZE ; 
 scalar_t__ GENET_TDMA_REG_OFF ; 
 int /*<<< orphan*/  bcmgenet_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__* genet_dma_ring_regs ; 

__attribute__((used)) static inline void bcmgenet_tdma_ring_writel(struct bcmgenet_priv *priv,
					     unsigned int ring, u32 val,
					     enum dma_ring_reg r)
{
	bcmgenet_writel(val, priv->base + GENET_TDMA_REG_OFF +
			(DMA_RING_SIZE * ring) +
			genet_dma_ring_regs[r]);
}