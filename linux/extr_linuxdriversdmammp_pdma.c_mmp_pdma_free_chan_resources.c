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
struct mmp_pdma_chan {int idle; scalar_t__ dev_addr; int /*<<< orphan*/ * desc_pool; int /*<<< orphan*/  desc_lock; int /*<<< orphan*/  chain_running; int /*<<< orphan*/  chain_pending; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmp_pdma_free_desc_list (struct mmp_pdma_chan*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmp_pdma_free_phy (struct mmp_pdma_chan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct mmp_pdma_chan* to_mmp_pdma_chan (struct dma_chan*) ; 

__attribute__((used)) static void mmp_pdma_free_chan_resources(struct dma_chan *dchan)
{
	struct mmp_pdma_chan *chan = to_mmp_pdma_chan(dchan);
	unsigned long flags;

	spin_lock_irqsave(&chan->desc_lock, flags);
	mmp_pdma_free_desc_list(chan, &chan->chain_pending);
	mmp_pdma_free_desc_list(chan, &chan->chain_running);
	spin_unlock_irqrestore(&chan->desc_lock, flags);

	dma_pool_destroy(chan->desc_pool);
	chan->desc_pool = NULL;
	chan->idle = true;
	chan->dev_addr = 0;
	mmp_pdma_free_phy(chan);
	return;
}