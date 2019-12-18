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
struct nouveau_fence_chan {int /*<<< orphan*/  lock; int /*<<< orphan*/  notify; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/ * ops; } ;
struct nouveau_fence {TYPE_1__ base; int /*<<< orphan*/  channel; } ;
struct nouveau_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FENCE_FLAG_SIGNALED_BIT ; 
 int dma_fence_is_signaled (TYPE_1__*) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 struct nouveau_fence_chan* nouveau_fctx (struct nouveau_fence*) ; 
 int /*<<< orphan*/  nouveau_fence_ops_legacy ; 
 int /*<<< orphan*/  nouveau_fence_ops_uevent ; 
 scalar_t__ nouveau_fence_update (struct nouveau_channel*,struct nouveau_fence_chan*) ; 
 int /*<<< orphan*/  nvif_notify_put (int /*<<< orphan*/ *) ; 
 struct nouveau_channel* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool
nouveau_fence_done(struct nouveau_fence *fence)
{
	if (fence->base.ops == &nouveau_fence_ops_legacy ||
	    fence->base.ops == &nouveau_fence_ops_uevent) {
		struct nouveau_fence_chan *fctx = nouveau_fctx(fence);
		struct nouveau_channel *chan;
		unsigned long flags;

		if (test_bit(DMA_FENCE_FLAG_SIGNALED_BIT, &fence->base.flags))
			return true;

		spin_lock_irqsave(&fctx->lock, flags);
		chan = rcu_dereference_protected(fence->channel, lockdep_is_held(&fctx->lock));
		if (chan && nouveau_fence_update(chan, fctx))
			nvif_notify_put(&fctx->notify);
		spin_unlock_irqrestore(&fctx->lock, flags);
	}
	return dma_fence_is_signaled(&fence->base);
}