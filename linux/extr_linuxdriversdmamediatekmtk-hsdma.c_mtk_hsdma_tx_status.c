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
struct virt_dma_desc {int dummy; } ;
struct mtk_hsdma_vdesc {size_t residue; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct mtk_hsdma_vchan {TYPE_1__ vc; } ;
struct dma_tx_state {int dummy; } ;
struct dma_chan {int dummy; } ;
typedef  enum dma_status { ____Placeholder_dma_status } dma_status ;
typedef  int /*<<< orphan*/  dma_cookie_t ;

/* Variables and functions */
 int DMA_COMPLETE ; 
 int dma_cookie_status (struct dma_chan*,int /*<<< orphan*/ ,struct dma_tx_state*) ; 
 int /*<<< orphan*/  dma_set_residue (struct dma_tx_state*,size_t) ; 
 struct virt_dma_desc* mtk_hsdma_find_active_desc (struct dma_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct mtk_hsdma_vchan* to_hsdma_vchan (struct dma_chan*) ; 
 struct mtk_hsdma_vdesc* to_hsdma_vdesc (struct virt_dma_desc*) ; 

__attribute__((used)) static enum dma_status mtk_hsdma_tx_status(struct dma_chan *c,
					   dma_cookie_t cookie,
					   struct dma_tx_state *txstate)
{
	struct mtk_hsdma_vchan *hvc = to_hsdma_vchan(c);
	struct mtk_hsdma_vdesc *hvd;
	struct virt_dma_desc *vd;
	enum dma_status ret;
	unsigned long flags;
	size_t bytes = 0;

	ret = dma_cookie_status(c, cookie, txstate);
	if (ret == DMA_COMPLETE || !txstate)
		return ret;

	spin_lock_irqsave(&hvc->vc.lock, flags);
	vd = mtk_hsdma_find_active_desc(c, cookie);
	spin_unlock_irqrestore(&hvc->vc.lock, flags);

	if (vd) {
		hvd = to_hsdma_vdesc(vd);
		bytes = hvd->residue;
	}

	dma_set_residue(txstate, bytes);

	return ret;
}