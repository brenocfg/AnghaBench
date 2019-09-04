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
struct txx9dmac_chan {int /*<<< orphan*/  lock; } ;
struct dma_tx_state {int dummy; } ;
struct dma_chan {int dummy; } ;
typedef  enum dma_status { ____Placeholder_dma_status } dma_status ;
typedef  int /*<<< orphan*/  dma_cookie_t ;

/* Variables and functions */
 int DMA_COMPLETE ; 
 int dma_cookie_status (struct dma_chan*,int /*<<< orphan*/ ,struct dma_tx_state*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct txx9dmac_chan* to_txx9dmac_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  txx9dmac_scan_descriptors (struct txx9dmac_chan*) ; 

__attribute__((used)) static enum dma_status
txx9dmac_tx_status(struct dma_chan *chan, dma_cookie_t cookie,
		   struct dma_tx_state *txstate)
{
	struct txx9dmac_chan *dc = to_txx9dmac_chan(chan);
	enum dma_status ret;

	ret = dma_cookie_status(chan, cookie, txstate);
	if (ret == DMA_COMPLETE)
		return DMA_COMPLETE;

	spin_lock_bh(&dc->lock);
	txx9dmac_scan_descriptors(dc);
	spin_unlock_bh(&dc->lock);

	return dma_cookie_status(chan, cookie, txstate);
}