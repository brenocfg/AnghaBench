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
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct vmw_fence_obj {TYPE_1__ base; } ;
struct vmw_fence_manager {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FENCE_FLAG_SIGNALED_BIT ; 
 int dma_fence_is_signaled (TYPE_1__*) ; 
 struct vmw_fence_manager* fman_from_fence (struct vmw_fence_obj*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_fences_update (struct vmw_fence_manager*) ; 

bool vmw_fence_obj_signaled(struct vmw_fence_obj *fence)
{
	struct vmw_fence_manager *fman = fman_from_fence(fence);

	if (test_bit(DMA_FENCE_FLAG_SIGNALED_BIT, &fence->base.flags))
		return 1;

	vmw_fences_update(fman);

	return dma_fence_is_signaled(&fence->base);
}