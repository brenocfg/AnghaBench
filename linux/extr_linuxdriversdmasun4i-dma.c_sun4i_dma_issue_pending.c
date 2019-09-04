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
struct sun4i_dma_vchan {TYPE_1__ vc; } ;
struct sun4i_dma_dev {int dummy; } ;
struct dma_chan {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  __execute_vchan_pending (struct sun4i_dma_dev*,struct sun4i_dma_vchan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct sun4i_dma_dev* to_sun4i_dma_dev (int /*<<< orphan*/ ) ; 
 struct sun4i_dma_vchan* to_sun4i_dma_vchan (struct dma_chan*) ; 
 scalar_t__ vchan_issue_pending (TYPE_1__*) ; 

__attribute__((used)) static void sun4i_dma_issue_pending(struct dma_chan *chan)
{
	struct sun4i_dma_dev *priv = to_sun4i_dma_dev(chan->device);
	struct sun4i_dma_vchan *vchan = to_sun4i_dma_vchan(chan);
	unsigned long flags;

	spin_lock_irqsave(&vchan->vc.lock, flags);

	/*
	 * If there are pending transactions for this vchan, push one of
	 * them into the engine to get the ball rolling.
	 */
	if (vchan_issue_pending(&vchan->vc))
		__execute_vchan_pending(priv, vchan);

	spin_unlock_irqrestore(&vchan->vc.lock, flags);
}