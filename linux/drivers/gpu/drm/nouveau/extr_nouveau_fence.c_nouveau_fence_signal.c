#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nouveau_fence_chan {int /*<<< orphan*/  notify_ref; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
struct nouveau_fence {TYPE_1__ base; int /*<<< orphan*/  channel; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FENCE_FLAG_USER_BITS ; 
 int /*<<< orphan*/  dma_fence_put (TYPE_1__*) ; 
 int /*<<< orphan*/  dma_fence_signal_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct nouveau_fence_chan* nouveau_fctx (struct nouveau_fence*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nouveau_fence_signal(struct nouveau_fence *fence)
{
	int drop = 0;

	dma_fence_signal_locked(&fence->base);
	list_del(&fence->head);
	rcu_assign_pointer(fence->channel, NULL);

	if (test_bit(DMA_FENCE_FLAG_USER_BITS, &fence->base.flags)) {
		struct nouveau_fence_chan *fctx = nouveau_fctx(fence);

		if (!--fctx->notify_ref)
			drop = 1;
	}

	dma_fence_put(&fence->base);
	return drop;
}