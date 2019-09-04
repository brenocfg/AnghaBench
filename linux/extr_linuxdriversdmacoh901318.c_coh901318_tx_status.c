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
struct dma_tx_state {int dummy; } ;
struct dma_chan {int dummy; } ;
struct coh901318_chan {scalar_t__ stopped; } ;
typedef  enum dma_status { ____Placeholder_dma_status } dma_status ;
typedef  int /*<<< orphan*/  dma_cookie_t ;

/* Variables and functions */
 int DMA_COMPLETE ; 
 int DMA_IN_PROGRESS ; 
 int DMA_PAUSED ; 
 int /*<<< orphan*/  coh901318_get_bytes_left (struct dma_chan*) ; 
 int dma_cookie_status (struct dma_chan*,int /*<<< orphan*/ ,struct dma_tx_state*) ; 
 int /*<<< orphan*/  dma_set_residue (struct dma_tx_state*,int /*<<< orphan*/ ) ; 
 struct coh901318_chan* to_coh901318_chan (struct dma_chan*) ; 

__attribute__((used)) static enum dma_status
coh901318_tx_status(struct dma_chan *chan, dma_cookie_t cookie,
		 struct dma_tx_state *txstate)
{
	struct coh901318_chan *cohc = to_coh901318_chan(chan);
	enum dma_status ret;

	ret = dma_cookie_status(chan, cookie, txstate);
	if (ret == DMA_COMPLETE || !txstate)
		return ret;

	dma_set_residue(txstate, coh901318_get_bytes_left(chan));

	if (ret == DMA_IN_PROGRESS && cohc->stopped)
		ret = DMA_PAUSED;

	return ret;
}