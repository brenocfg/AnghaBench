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
struct s3c24xx_dma_chan {scalar_t__ state; TYPE_1__ vc; int /*<<< orphan*/  phy; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 scalar_t__ S3C24XX_DMA_CHAN_WAITING ; 
 int /*<<< orphan*/  s3c24xx_dma_phy_alloc_and_start (struct s3c24xx_dma_chan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct s3c24xx_dma_chan* to_s3c24xx_dma_chan (struct dma_chan*) ; 
 scalar_t__ vchan_issue_pending (TYPE_1__*) ; 

__attribute__((used)) static void s3c24xx_dma_issue_pending(struct dma_chan *chan)
{
	struct s3c24xx_dma_chan *s3cchan = to_s3c24xx_dma_chan(chan);
	unsigned long flags;

	spin_lock_irqsave(&s3cchan->vc.lock, flags);
	if (vchan_issue_pending(&s3cchan->vc)) {
		if (!s3cchan->phy && s3cchan->state != S3C24XX_DMA_CHAN_WAITING)
			s3c24xx_dma_phy_alloc_and_start(s3cchan);
	}
	spin_unlock_irqrestore(&s3cchan->vc.lock, flags);
}