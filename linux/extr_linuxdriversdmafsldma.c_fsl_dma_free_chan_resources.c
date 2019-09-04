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
struct fsldma_chan {int /*<<< orphan*/ * desc_pool; int /*<<< orphan*/  desc_lock; int /*<<< orphan*/  ld_completed; int /*<<< orphan*/  ld_running; int /*<<< orphan*/  ld_pending; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  chan_dbg (struct fsldma_chan*,char*) ; 
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsldma_cleanup_descriptors (struct fsldma_chan*) ; 
 int /*<<< orphan*/  fsldma_free_desc_list (struct fsldma_chan*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct fsldma_chan* to_fsl_chan (struct dma_chan*) ; 

__attribute__((used)) static void fsl_dma_free_chan_resources(struct dma_chan *dchan)
{
	struct fsldma_chan *chan = to_fsl_chan(dchan);

	chan_dbg(chan, "free all channel resources\n");
	spin_lock_bh(&chan->desc_lock);
	fsldma_cleanup_descriptors(chan);
	fsldma_free_desc_list(chan, &chan->ld_pending);
	fsldma_free_desc_list(chan, &chan->ld_running);
	fsldma_free_desc_list(chan, &chan->ld_completed);
	spin_unlock_bh(&chan->desc_lock);

	dma_pool_destroy(chan->desc_pool);
	chan->desc_pool = NULL;
}