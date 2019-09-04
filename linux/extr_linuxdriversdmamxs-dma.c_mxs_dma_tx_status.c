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
typedef  scalar_t__ u32 ;
struct mxs_dma_engine {scalar_t__ base; } ;
struct mxs_dma_chan {scalar_t__ status; int flags; int desc_count; struct mxs_dma_ccw* ccw; struct mxs_dma_engine* mxs_dma; } ;
struct mxs_dma_ccw {scalar_t__ bufaddr; scalar_t__ xfer_bytes; } ;
struct dma_tx_state {int dummy; } ;
struct dma_chan {int /*<<< orphan*/  cookie; int /*<<< orphan*/  completed_cookie; int /*<<< orphan*/  chan_id; } ;
typedef  enum dma_status { ____Placeholder_dma_status } dma_status ;
typedef  int /*<<< orphan*/  dma_cookie_t ;

/* Variables and functions */
 scalar_t__ DMA_IN_PROGRESS ; 
 scalar_t__ HW_APBHX_CHn_BAR (struct mxs_dma_engine*,int /*<<< orphan*/ ) ; 
 int MXS_DMA_SG_LOOP ; 
 int /*<<< orphan*/  dma_set_tx_state (struct dma_tx_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ readl (scalar_t__) ; 
 struct mxs_dma_chan* to_mxs_dma_chan (struct dma_chan*) ; 

__attribute__((used)) static enum dma_status mxs_dma_tx_status(struct dma_chan *chan,
			dma_cookie_t cookie, struct dma_tx_state *txstate)
{
	struct mxs_dma_chan *mxs_chan = to_mxs_dma_chan(chan);
	struct mxs_dma_engine *mxs_dma = mxs_chan->mxs_dma;
	u32 residue = 0;

	if (mxs_chan->status == DMA_IN_PROGRESS &&
			mxs_chan->flags & MXS_DMA_SG_LOOP) {
		struct mxs_dma_ccw *last_ccw;
		u32 bar;

		last_ccw = &mxs_chan->ccw[mxs_chan->desc_count - 1];
		residue = last_ccw->xfer_bytes + last_ccw->bufaddr;

		bar = readl(mxs_dma->base +
				HW_APBHX_CHn_BAR(mxs_dma, chan->chan_id));
		residue -= bar;
	}

	dma_set_tx_state(txstate, chan->completed_cookie, chan->cookie,
			residue);

	return mxs_chan->status;
}