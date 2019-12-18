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
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct gdma_dmaengine_chan {TYPE_2__ vchan; int /*<<< orphan*/  id; int /*<<< orphan*/  desc; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct gdma_dma_dev {TYPE_1__ ddev; int /*<<< orphan*/  task; int /*<<< orphan*/  chan_issued; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct gdma_dma_dev* gdma_dma_chan_get_dev (struct gdma_dmaengine_chan*) ; 
 scalar_t__ gdma_next_desc (struct gdma_dmaengine_chan*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 struct gdma_dmaengine_chan* to_gdma_dma_chan (struct dma_chan*) ; 
 scalar_t__ vchan_issue_pending (TYPE_2__*) ; 

__attribute__((used)) static void gdma_dma_issue_pending(struct dma_chan *c)
{
	struct gdma_dmaengine_chan *chan = to_gdma_dma_chan(c);
	struct gdma_dma_dev *dma_dev = gdma_dma_chan_get_dev(chan);
	unsigned long flags;

	spin_lock_irqsave(&chan->vchan.lock, flags);
	if (vchan_issue_pending(&chan->vchan) && !chan->desc) {
		if (gdma_next_desc(chan)) {
			set_bit(chan->id, &dma_dev->chan_issued);
			tasklet_schedule(&dma_dev->task);
		} else {
			dev_dbg(dma_dev->ddev.dev, "chan %d no desc to issue\n",
				chan->id);
		}
	}
	spin_unlock_irqrestore(&chan->vchan.lock, flags);
}