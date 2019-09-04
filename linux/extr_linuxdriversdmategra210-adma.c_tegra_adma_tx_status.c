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
struct virt_dma_desc {int /*<<< orphan*/  tx; } ;
struct TYPE_6__ {unsigned int tc; } ;
struct tegra_adma_desc {TYPE_1__ ch_regs; } ;
struct TYPE_10__ {int /*<<< orphan*/  lock; } ;
struct tegra_adma_chan {TYPE_5__ vc; TYPE_4__* desc; } ;
struct dma_tx_state {int dummy; } ;
struct dma_chan {int dummy; } ;
typedef  enum dma_status { ____Placeholder_dma_status } dma_status ;
typedef  scalar_t__ dma_cookie_t ;
struct TYPE_7__ {scalar_t__ cookie; } ;
struct TYPE_8__ {TYPE_2__ tx; } ;
struct TYPE_9__ {TYPE_3__ vd; } ;

/* Variables and functions */
 int DMA_COMPLETE ; 
 int dma_cookie_status (struct dma_chan*,scalar_t__,struct dma_tx_state*) ; 
 int /*<<< orphan*/  dma_set_residue (struct dma_tx_state*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned int tegra_adma_get_residue (struct tegra_adma_chan*) ; 
 struct tegra_adma_chan* to_tegra_adma_chan (struct dma_chan*) ; 
 struct tegra_adma_desc* to_tegra_adma_desc (int /*<<< orphan*/ *) ; 
 struct virt_dma_desc* vchan_find_desc (TYPE_5__*,scalar_t__) ; 

__attribute__((used)) static enum dma_status tegra_adma_tx_status(struct dma_chan *dc,
					    dma_cookie_t cookie,
					    struct dma_tx_state *txstate)
{
	struct tegra_adma_chan *tdc = to_tegra_adma_chan(dc);
	struct tegra_adma_desc *desc;
	struct virt_dma_desc *vd;
	enum dma_status ret;
	unsigned long flags;
	unsigned int residual;

	ret = dma_cookie_status(dc, cookie, txstate);
	if (ret == DMA_COMPLETE || !txstate)
		return ret;

	spin_lock_irqsave(&tdc->vc.lock, flags);

	vd = vchan_find_desc(&tdc->vc, cookie);
	if (vd) {
		desc = to_tegra_adma_desc(&vd->tx);
		residual = desc->ch_regs.tc;
	} else if (tdc->desc && tdc->desc->vd.tx.cookie == cookie) {
		residual = tegra_adma_get_residue(tdc);
	} else {
		residual = 0;
	}

	spin_unlock_irqrestore(&tdc->vc.lock, flags);

	dma_set_residue(txstate, residual);

	return ret;
}