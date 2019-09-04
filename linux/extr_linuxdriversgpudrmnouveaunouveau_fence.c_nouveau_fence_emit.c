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
struct nouveau_fence_priv {scalar_t__ uevent; } ;
struct nouveau_fence_chan {int (* emit ) (struct nouveau_fence*) ;int /*<<< orphan*/  lock; int /*<<< orphan*/  pending; int /*<<< orphan*/  notify; int /*<<< orphan*/  fence_ref; int /*<<< orphan*/  sequence; int /*<<< orphan*/  context; } ;
struct nouveau_fence {int /*<<< orphan*/  head; int /*<<< orphan*/  base; scalar_t__ timeout; struct nouveau_channel* channel; } ;
struct nouveau_channel {TYPE_1__* drm; struct nouveau_fence_chan* fence; } ;
struct TYPE_2__ {scalar_t__ fence; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  dma_fence_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_fence_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_fence_ops_legacy ; 
 int /*<<< orphan*/  nouveau_fence_ops_uevent ; 
 scalar_t__ nouveau_fence_update (struct nouveau_channel*,struct nouveau_fence_chan*) ; 
 int /*<<< orphan*/  nvif_notify_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int stub1 (struct nouveau_fence*) ; 
 int /*<<< orphan*/  trace_dma_fence_emit (int /*<<< orphan*/ *) ; 

int
nouveau_fence_emit(struct nouveau_fence *fence, struct nouveau_channel *chan)
{
	struct nouveau_fence_chan *fctx = chan->fence;
	struct nouveau_fence_priv *priv = (void*)chan->drm->fence;
	int ret;

	fence->channel  = chan;
	fence->timeout  = jiffies + (15 * HZ);

	if (priv->uevent)
		dma_fence_init(&fence->base, &nouveau_fence_ops_uevent,
			       &fctx->lock, fctx->context, ++fctx->sequence);
	else
		dma_fence_init(&fence->base, &nouveau_fence_ops_legacy,
			       &fctx->lock, fctx->context, ++fctx->sequence);
	kref_get(&fctx->fence_ref);

	trace_dma_fence_emit(&fence->base);
	ret = fctx->emit(fence);
	if (!ret) {
		dma_fence_get(&fence->base);
		spin_lock_irq(&fctx->lock);

		if (nouveau_fence_update(chan, fctx))
			nvif_notify_put(&fctx->notify);

		list_add_tail(&fence->head, &fctx->pending);
		spin_unlock_irq(&fctx->lock);
	}

	return ret;
}