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
struct mxs_dma_engine {scalar_t__ base; } ;
struct TYPE_2__ {int chan_id; } ;
struct mxs_dma_chan {int /*<<< orphan*/  status; TYPE_1__ chan; struct mxs_dma_engine* mxs_dma; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_IN_PROGRESS ; 
 scalar_t__ HW_APBHX_CHANNEL_CTRL ; 
 scalar_t__ HW_APBHX_CTRL0 ; 
 scalar_t__ STMP_OFFSET_REG_CLR ; 
 scalar_t__ apbh_is_old (struct mxs_dma_engine*) ; 
 scalar_t__ dma_is_apbh (struct mxs_dma_engine*) ; 
 struct mxs_dma_chan* to_mxs_dma_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mxs_dma_resume_chan(struct dma_chan *chan)
{
	struct mxs_dma_chan *mxs_chan = to_mxs_dma_chan(chan);
	struct mxs_dma_engine *mxs_dma = mxs_chan->mxs_dma;
	int chan_id = mxs_chan->chan.chan_id;

	/* unfreeze the channel */
	if (dma_is_apbh(mxs_dma) && apbh_is_old(mxs_dma))
		writel(1 << chan_id,
			mxs_dma->base + HW_APBHX_CTRL0 + STMP_OFFSET_REG_CLR);
	else
		writel(1 << chan_id,
			mxs_dma->base + HW_APBHX_CHANNEL_CTRL + STMP_OFFSET_REG_CLR);

	mxs_chan->status = DMA_IN_PROGRESS;
	return 0;
}