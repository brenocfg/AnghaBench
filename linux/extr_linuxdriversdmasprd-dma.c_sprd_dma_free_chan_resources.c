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
struct sprd_dma_chn {TYPE_2__ vc; } ;
struct dma_chan {TYPE_1__* device; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sprd_dma_stop (struct sprd_dma_chn*) ; 
 struct sprd_dma_chn* to_sprd_dma_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  vchan_free_chan_resources (TYPE_2__*) ; 

__attribute__((used)) static void sprd_dma_free_chan_resources(struct dma_chan *chan)
{
	struct sprd_dma_chn *schan = to_sprd_dma_chan(chan);
	unsigned long flags;

	spin_lock_irqsave(&schan->vc.lock, flags);
	sprd_dma_stop(schan);
	spin_unlock_irqrestore(&schan->vc.lock, flags);

	vchan_free_chan_resources(&schan->vc);
	pm_runtime_put(chan->device->dev);
}