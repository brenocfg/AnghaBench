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
struct mdc_chan {TYPE_1__ vc; int /*<<< orphan*/  desc; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdc_issue_desc (struct mdc_chan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct mdc_chan* to_mdc_chan (struct dma_chan*) ; 
 scalar_t__ vchan_issue_pending (TYPE_1__*) ; 

__attribute__((used)) static void mdc_issue_pending(struct dma_chan *chan)
{
	struct mdc_chan *mchan = to_mdc_chan(chan);
	unsigned long flags;

	spin_lock_irqsave(&mchan->vc.lock, flags);
	if (vchan_issue_pending(&mchan->vc) && !mchan->desc)
		mdc_issue_desc(mchan);
	spin_unlock_irqrestore(&mchan->vc.lock, flags);
}