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
struct dwc2_hsotg {int /*<<< orphan*/  lock; int /*<<< orphan*/ * frame_list; int /*<<< orphan*/  frame_list_sz; int /*<<< orphan*/  frame_list_dma; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void dwc2_frame_list_free(struct dwc2_hsotg *hsotg)
{
	unsigned long flags;

	spin_lock_irqsave(&hsotg->lock, flags);

	if (!hsotg->frame_list) {
		spin_unlock_irqrestore(&hsotg->lock, flags);
		return;
	}

	dma_unmap_single(hsotg->dev, hsotg->frame_list_dma,
			 hsotg->frame_list_sz, DMA_FROM_DEVICE);

	kfree(hsotg->frame_list);
	hsotg->frame_list = NULL;

	spin_unlock_irqrestore(&hsotg->lock, flags);
}