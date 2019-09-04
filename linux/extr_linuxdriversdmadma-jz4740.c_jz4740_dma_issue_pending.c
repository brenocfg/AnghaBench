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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct jz4740_dmaengine_chan {TYPE_1__ vchan; int /*<<< orphan*/  desc; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  jz4740_dma_start_transfer (struct jz4740_dmaengine_chan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct jz4740_dmaengine_chan* to_jz4740_dma_chan (struct dma_chan*) ; 
 scalar_t__ vchan_issue_pending (TYPE_1__*) ; 

__attribute__((used)) static void jz4740_dma_issue_pending(struct dma_chan *c)
{
	struct jz4740_dmaengine_chan *chan = to_jz4740_dma_chan(c);
	unsigned long flags;

	spin_lock_irqsave(&chan->vchan.lock, flags);
	if (vchan_issue_pending(&chan->vchan) && !chan->desc)
		jz4740_dma_start_transfer(chan);
	spin_unlock_irqrestore(&chan->vchan.lock, flags);
}