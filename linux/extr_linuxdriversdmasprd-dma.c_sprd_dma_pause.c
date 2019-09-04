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
struct sprd_dma_chn {TYPE_1__ vc; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sprd_dma_pause_resume (struct sprd_dma_chn*,int) ; 
 struct sprd_dma_chn* to_sprd_dma_chan (struct dma_chan*) ; 

__attribute__((used)) static int sprd_dma_pause(struct dma_chan *chan)
{
	struct sprd_dma_chn *schan = to_sprd_dma_chan(chan);
	unsigned long flags;

	spin_lock_irqsave(&schan->vc.lock, flags);
	sprd_dma_pause_resume(schan, true);
	spin_unlock_irqrestore(&schan->vc.lock, flags);

	return 0;
}