#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dma_fence {int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {TYPE_1__* gem_context; } ;
struct TYPE_3__ {scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FENCE_FLAG_SIGNALED_BIT ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* to_request (struct dma_fence*) ; 

__attribute__((used)) static const char *i915_fence_get_timeline_name(struct dma_fence *fence)
{
	/*
	 * The timeline struct (as part of the ppgtt underneath a context)
	 * may be freed when the request is no longer in use by the GPU.
	 * We could extend the life of a context to beyond that of all
	 * fences, possibly keeping the hw resource around indefinitely,
	 * or we just give them a false name. Since
	 * dma_fence_ops.get_timeline_name is a debug feature, the occasional
	 * lie seems justifiable.
	 */
	if (test_bit(DMA_FENCE_FLAG_SIGNALED_BIT, &fence->flags))
		return "signaled";

	return to_request(fence)->gem_context->name ?: "[i915]";
}