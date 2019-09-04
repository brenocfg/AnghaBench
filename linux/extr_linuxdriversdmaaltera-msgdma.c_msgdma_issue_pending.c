#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct msgdma_device {int /*<<< orphan*/  lock; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  msgdma_start_transfer (struct msgdma_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct msgdma_device* to_mdev (struct dma_chan*) ; 

__attribute__((used)) static void msgdma_issue_pending(struct dma_chan *chan)
{
	struct msgdma_device *mdev = to_mdev(chan);
	unsigned long flags;

	spin_lock_irqsave(&mdev->lock, flags);
	msgdma_start_transfer(mdev);
	spin_unlock_irqrestore(&mdev->lock, flags);
}