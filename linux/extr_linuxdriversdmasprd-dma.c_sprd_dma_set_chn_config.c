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
struct sprd_dma_chn_hw {int /*<<< orphan*/  req; int /*<<< orphan*/  des_blk_step; int /*<<< orphan*/  src_blk_step; int /*<<< orphan*/  frg_step; int /*<<< orphan*/  llist_ptr; int /*<<< orphan*/  wrap_to; int /*<<< orphan*/  wrap_ptr; int /*<<< orphan*/  trsf_step; int /*<<< orphan*/  trsc_len; int /*<<< orphan*/  blk_len; int /*<<< orphan*/  frg_len; int /*<<< orphan*/  des_addr; int /*<<< orphan*/  src_addr; int /*<<< orphan*/  intc; int /*<<< orphan*/  cfg; int /*<<< orphan*/  pause; } ;
struct sprd_dma_desc {struct sprd_dma_chn_hw chn_hw; } ;
struct sprd_dma_chn {scalar_t__ chn_base; } ;

/* Variables and functions */
 scalar_t__ SPRD_DMA_CHN_BLK_LEN ; 
 scalar_t__ SPRD_DMA_CHN_CFG ; 
 scalar_t__ SPRD_DMA_CHN_DES_ADDR ; 
 scalar_t__ SPRD_DMA_CHN_DES_BLK_STEP ; 
 scalar_t__ SPRD_DMA_CHN_FRAG_STEP ; 
 scalar_t__ SPRD_DMA_CHN_FRG_LEN ; 
 scalar_t__ SPRD_DMA_CHN_INTC ; 
 scalar_t__ SPRD_DMA_CHN_LLIST_PTR ; 
 scalar_t__ SPRD_DMA_CHN_PAUSE ; 
 scalar_t__ SPRD_DMA_CHN_REQ ; 
 scalar_t__ SPRD_DMA_CHN_SRC_ADDR ; 
 scalar_t__ SPRD_DMA_CHN_SRC_BLK_STEP ; 
 scalar_t__ SPRD_DMA_CHN_TRSC_LEN ; 
 scalar_t__ SPRD_DMA_CHN_TRSF_STEP ; 
 scalar_t__ SPRD_DMA_CHN_WARP_PTR ; 
 scalar_t__ SPRD_DMA_CHN_WARP_TO ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sprd_dma_set_chn_config(struct sprd_dma_chn *schan,
				    struct sprd_dma_desc *sdesc)
{
	struct sprd_dma_chn_hw *cfg = &sdesc->chn_hw;

	writel(cfg->pause, schan->chn_base + SPRD_DMA_CHN_PAUSE);
	writel(cfg->cfg, schan->chn_base + SPRD_DMA_CHN_CFG);
	writel(cfg->intc, schan->chn_base + SPRD_DMA_CHN_INTC);
	writel(cfg->src_addr, schan->chn_base + SPRD_DMA_CHN_SRC_ADDR);
	writel(cfg->des_addr, schan->chn_base + SPRD_DMA_CHN_DES_ADDR);
	writel(cfg->frg_len, schan->chn_base + SPRD_DMA_CHN_FRG_LEN);
	writel(cfg->blk_len, schan->chn_base + SPRD_DMA_CHN_BLK_LEN);
	writel(cfg->trsc_len, schan->chn_base + SPRD_DMA_CHN_TRSC_LEN);
	writel(cfg->trsf_step, schan->chn_base + SPRD_DMA_CHN_TRSF_STEP);
	writel(cfg->wrap_ptr, schan->chn_base + SPRD_DMA_CHN_WARP_PTR);
	writel(cfg->wrap_to, schan->chn_base + SPRD_DMA_CHN_WARP_TO);
	writel(cfg->llist_ptr, schan->chn_base + SPRD_DMA_CHN_LLIST_PTR);
	writel(cfg->frg_step, schan->chn_base + SPRD_DMA_CHN_FRAG_STEP);
	writel(cfg->src_blk_step, schan->chn_base + SPRD_DMA_CHN_SRC_BLK_STEP);
	writel(cfg->des_blk_step, schan->chn_base + SPRD_DMA_CHN_DES_BLK_STEP);
	writel(cfg->req, schan->chn_base + SPRD_DMA_CHN_REQ);
}