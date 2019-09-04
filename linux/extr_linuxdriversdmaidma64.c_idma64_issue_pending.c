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
struct idma64_chan {TYPE_1__ vchan; int /*<<< orphan*/  desc; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  idma64_start_transfer (struct idma64_chan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct idma64_chan* to_idma64_chan (struct dma_chan*) ; 
 scalar_t__ vchan_issue_pending (TYPE_1__*) ; 

__attribute__((used)) static void idma64_issue_pending(struct dma_chan *chan)
{
	struct idma64_chan *idma64c = to_idma64_chan(chan);
	unsigned long flags;

	spin_lock_irqsave(&idma64c->vchan.lock, flags);
	if (vchan_issue_pending(&idma64c->vchan) && !idma64c->desc)
		idma64_start_transfer(idma64c);
	spin_unlock_irqrestore(&idma64c->vchan.lock, flags);
}