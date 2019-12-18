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
struct nouveau_fence_chan {int /*<<< orphan*/  notify; int /*<<< orphan*/  notify_ref; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct nouveau_fence {TYPE_1__ base; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FENCE_FLAG_USER_BITS ; 
 struct nouveau_fence* from_fence (struct dma_fence*) ; 
 struct nouveau_fence_chan* nouveau_fctx (struct nouveau_fence*) ; 
 int nouveau_fence_no_signaling (struct dma_fence*) ; 
 int /*<<< orphan*/  nvif_notify_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvif_notify_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool nouveau_fence_enable_signaling(struct dma_fence *f)
{
	struct nouveau_fence *fence = from_fence(f);
	struct nouveau_fence_chan *fctx = nouveau_fctx(fence);
	bool ret;

	if (!fctx->notify_ref++)
		nvif_notify_get(&fctx->notify);

	ret = nouveau_fence_no_signaling(f);
	if (ret)
		set_bit(DMA_FENCE_FLAG_USER_BITS, &fence->base.flags);
	else if (!--fctx->notify_ref)
		nvif_notify_put(&fctx->notify);

	return ret;
}