#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_8__ {int phys; } ;
struct TYPE_9__ {TYPE_3__ tx; } ;
struct axi_dma_desc {TYPE_4__ vd; } ;
struct axi_dma_chan {size_t id; TYPE_5__* chip; } ;
struct TYPE_10__ {TYPE_2__* dw; } ;
struct TYPE_7__ {TYPE_1__* hdata; } ;
struct TYPE_6__ {int* priority; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH_CFG_H ; 
 int CH_CFG_H_HS_SEL_DST_POS ; 
 int CH_CFG_H_HS_SEL_SRC_POS ; 
 int CH_CFG_H_PRIORITY_POS ; 
 int CH_CFG_H_TT_FC_POS ; 
 int /*<<< orphan*/  CH_CFG_L ; 
 int CH_CFG_L_DST_MULTBLK_TYPE_POS ; 
 int CH_CFG_L_SRC_MULTBLK_TYPE_POS ; 
 int DWAXIDMAC_HS_SEL_HW ; 
 int DWAXIDMAC_IRQ_ALL_ERR ; 
 int DWAXIDMAC_IRQ_DMA_TRF ; 
 int DWAXIDMAC_IRQ_SUSPENDED ; 
 int DWAXIDMAC_MBLK_TYPE_LL ; 
 int DWAXIDMAC_TT_FC_MEM_TO_MEM_DMAC ; 
 int /*<<< orphan*/  axi_chan_enable (struct axi_dma_chan*) ; 
 int /*<<< orphan*/  axi_chan_iowrite32 (struct axi_dma_chan*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  axi_chan_irq_set (struct axi_dma_chan*,int) ; 
 int /*<<< orphan*/  axi_chan_irq_sig_set (struct axi_dma_chan*,int) ; 
 int /*<<< orphan*/  axi_chan_is_hw_enable (struct axi_dma_chan*) ; 
 int /*<<< orphan*/  axi_chan_name (struct axi_dma_chan*) ; 
 int /*<<< orphan*/  axi_dma_enable (TYPE_5__*) ; 
 int /*<<< orphan*/  chan2dev (struct axi_dma_chan*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_chan_llp (struct axi_dma_chan*,int) ; 

__attribute__((used)) static void axi_chan_block_xfer_start(struct axi_dma_chan *chan,
				      struct axi_dma_desc *first)
{
	u32 priority = chan->chip->dw->hdata->priority[chan->id];
	u32 reg, irq_mask;
	u8 lms = 0; /* Select AXI0 master for LLI fetching */

	if (unlikely(axi_chan_is_hw_enable(chan))) {
		dev_err(chan2dev(chan), "%s is non-idle!\n",
			axi_chan_name(chan));

		return;
	}

	axi_dma_enable(chan->chip);

	reg = (DWAXIDMAC_MBLK_TYPE_LL << CH_CFG_L_DST_MULTBLK_TYPE_POS |
	       DWAXIDMAC_MBLK_TYPE_LL << CH_CFG_L_SRC_MULTBLK_TYPE_POS);
	axi_chan_iowrite32(chan, CH_CFG_L, reg);

	reg = (DWAXIDMAC_TT_FC_MEM_TO_MEM_DMAC << CH_CFG_H_TT_FC_POS |
	       priority << CH_CFG_H_PRIORITY_POS |
	       DWAXIDMAC_HS_SEL_HW << CH_CFG_H_HS_SEL_DST_POS |
	       DWAXIDMAC_HS_SEL_HW << CH_CFG_H_HS_SEL_SRC_POS);
	axi_chan_iowrite32(chan, CH_CFG_H, reg);

	write_chan_llp(chan, first->vd.tx.phys | lms);

	irq_mask = DWAXIDMAC_IRQ_DMA_TRF | DWAXIDMAC_IRQ_ALL_ERR;
	axi_chan_irq_sig_set(chan, irq_mask);

	/* Generate 'suspend' status but don't generate interrupt */
	irq_mask |= DWAXIDMAC_IRQ_SUSPENDED;
	axi_chan_irq_set(chan, irq_mask);

	axi_chan_enable(chan);
}