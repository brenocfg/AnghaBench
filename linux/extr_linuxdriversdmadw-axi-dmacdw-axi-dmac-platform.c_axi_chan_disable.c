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
typedef  int u32 ;
struct axi_dma_chan {int /*<<< orphan*/  chip; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int DMAC_CHAN_EN_SHIFT ; 
 int DMAC_CHAN_EN_WE_SHIFT ; 
 int /*<<< orphan*/  DMAC_CHEN ; 
 int axi_dma_ioread32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  axi_dma_iowrite32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void axi_chan_disable(struct axi_dma_chan *chan)
{
	u32 val;

	val = axi_dma_ioread32(chan->chip, DMAC_CHEN);
	val &= ~(BIT(chan->id) << DMAC_CHAN_EN_SHIFT);
	val |=   BIT(chan->id) << DMAC_CHAN_EN_WE_SHIFT;
	axi_dma_iowrite32(chan->chip, DMAC_CHEN, val);
}