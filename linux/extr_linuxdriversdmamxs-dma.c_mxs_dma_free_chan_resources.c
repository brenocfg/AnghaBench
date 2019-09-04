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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct mxs_dma_engine {int /*<<< orphan*/  clk; TYPE_1__ dma_device; } ;
struct mxs_dma_chan {int /*<<< orphan*/  ccw_phys; int /*<<< orphan*/  ccw; int /*<<< orphan*/  chan_irq; struct mxs_dma_engine* mxs_dma; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCW_BLOCK_SIZE ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct mxs_dma_engine*) ; 
 int /*<<< orphan*/  mxs_dma_disable_chan (struct dma_chan*) ; 
 struct mxs_dma_chan* to_mxs_dma_chan (struct dma_chan*) ; 

__attribute__((used)) static void mxs_dma_free_chan_resources(struct dma_chan *chan)
{
	struct mxs_dma_chan *mxs_chan = to_mxs_dma_chan(chan);
	struct mxs_dma_engine *mxs_dma = mxs_chan->mxs_dma;

	mxs_dma_disable_chan(chan);

	free_irq(mxs_chan->chan_irq, mxs_dma);

	dma_free_coherent(mxs_dma->dma_device.dev, CCW_BLOCK_SIZE,
			mxs_chan->ccw, mxs_chan->ccw_phys);

	clk_disable_unprepare(mxs_dma->clk);
}