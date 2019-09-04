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
struct dma_fence_cb {int dummy; } ;
struct dma_fence {int dummy; } ;
struct dma_buf_poll_cb_t {TYPE_1__* poll; scalar_t__ active; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_locked_poll (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static void dma_buf_poll_cb(struct dma_fence *fence, struct dma_fence_cb *cb)
{
	struct dma_buf_poll_cb_t *dcb = (struct dma_buf_poll_cb_t *)cb;
	unsigned long flags;

	spin_lock_irqsave(&dcb->poll->lock, flags);
	wake_up_locked_poll(dcb->poll, dcb->active);
	dcb->active = 0;
	spin_unlock_irqrestore(&dcb->poll->lock, flags);
}