#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hidma_chan {int /*<<< orphan*/  lock; TYPE_2__* running; scalar_t__ paused; int /*<<< orphan*/  last_success; } ;
struct dma_tx_state {int dummy; } ;
struct dma_chan {int /*<<< orphan*/  cookie; } ;
typedef  enum dma_status { ____Placeholder_dma_status } dma_status ;
typedef  int /*<<< orphan*/  dma_cookie_t ;
struct TYPE_3__ {int /*<<< orphan*/  cookie; } ;
struct TYPE_4__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int DMA_COMPLETE ; 
 int DMA_ERROR ; 
 int DMA_IN_PROGRESS ; 
 int DMA_PAUSED ; 
 int /*<<< orphan*/  EINVAL ; 
 int dma_cookie_status (struct dma_chan*,int /*<<< orphan*/ ,struct dma_tx_state*) ; 
 int hidma_txn_is_success (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct hidma_chan* to_hidma_chan (struct dma_chan*) ; 

__attribute__((used)) static enum dma_status hidma_tx_status(struct dma_chan *dmach,
				       dma_cookie_t cookie,
				       struct dma_tx_state *txstate)
{
	struct hidma_chan *mchan = to_hidma_chan(dmach);
	enum dma_status ret;

	ret = dma_cookie_status(dmach, cookie, txstate);
	if (ret == DMA_COMPLETE) {
		bool is_success;

		is_success = hidma_txn_is_success(cookie, mchan->last_success,
						  dmach->cookie);
		return is_success ? ret : DMA_ERROR;
	}

	if (mchan->paused && (ret == DMA_IN_PROGRESS)) {
		unsigned long flags;
		dma_cookie_t runcookie;

		spin_lock_irqsave(&mchan->lock, flags);
		if (mchan->running)
			runcookie = mchan->running->desc.cookie;
		else
			runcookie = -EINVAL;

		if (runcookie == cookie)
			ret = DMA_PAUSED;

		spin_unlock_irqrestore(&mchan->lock, flags);
	}

	return ret;
}