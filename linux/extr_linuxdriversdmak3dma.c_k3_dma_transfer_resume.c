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
struct k3_dma_phy {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct k3_dma_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/  chan_pending; TYPE_1__ slave; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  desc_issued; } ;
struct k3_dma_chan {scalar_t__ status; TYPE_2__ vc; int /*<<< orphan*/  node; struct k3_dma_phy* phy; } ;
struct dma_chan {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 scalar_t__ DMA_IN_PROGRESS ; 
 scalar_t__ DMA_PAUSED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  k3_dma_pause_dma (struct k3_dma_phy*,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct k3_dma_chan* to_k3_chan (struct dma_chan*) ; 
 struct k3_dma_dev* to_k3_dma (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int k3_dma_transfer_resume(struct dma_chan *chan)
{
	struct k3_dma_chan *c = to_k3_chan(chan);
	struct k3_dma_dev *d = to_k3_dma(chan->device);
	struct k3_dma_phy *p = c->phy;
	unsigned long flags;

	dev_dbg(d->slave.dev, "vchan %p: resume\n", &c->vc);
	spin_lock_irqsave(&c->vc.lock, flags);
	if (c->status == DMA_PAUSED) {
		c->status = DMA_IN_PROGRESS;
		if (p) {
			k3_dma_pause_dma(p, true);
		} else if (!list_empty(&c->vc.desc_issued)) {
			spin_lock(&d->lock);
			list_add_tail(&c->node, &d->chan_pending);
			spin_unlock(&d->lock);
		}
	}
	spin_unlock_irqrestore(&c->vc.lock, flags);

	return 0;
}