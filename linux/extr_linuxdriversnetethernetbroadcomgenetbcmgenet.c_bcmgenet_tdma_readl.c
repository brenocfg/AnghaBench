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
typedef  enum dma_reg { ____Placeholder_dma_reg } dma_reg ;

/* Variables and functions */
 scalar_t__ DMA_RINGS_SIZE ; 
 scalar_t__ GENET_TDMA_REG_OFF ; 
 scalar_t__* bcmgenet_dma_regs ; 
 int /*<<< orphan*/  bcmgenet_readl (scalar_t__) ; 

__attribute__((used)) static inline u32 bcmgenet_tdma_readl(struct bcmgenet_priv *priv,
				      enum dma_reg r)
{
	return bcmgenet_readl(priv->base + GENET_TDMA_REG_OFF +
			      DMA_RINGS_SIZE + bcmgenet_dma_regs[r]);
}