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
struct vmw_fence_manager {int dummy; } ;
struct dma_fence_array {int num_fences; struct dma_fence** fences; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_fence_is_array (struct dma_fence*) ; 
 scalar_t__ dma_fence_is_signaled (struct dma_fence*) ; 
 int dma_fence_wait (struct dma_fence*,int) ; 
 struct dma_fence_array* to_dma_fence_array (struct dma_fence*) ; 

int vmw_wait_dma_fence(struct vmw_fence_manager *fman,
		       struct dma_fence *fence)
{
	struct dma_fence_array *fence_array;
	int ret = 0;
	int i;


	if (dma_fence_is_signaled(fence))
		return 0;

	if (!dma_fence_is_array(fence))
		return dma_fence_wait(fence, true);

	/* From i915: Note that if the fence-array was created in
	 * signal-on-any mode, we should *not* decompose it into its individual
	 * fences. However, we don't currently store which mode the fence-array
	 * is operating in. Fortunately, the only user of signal-on-any is
	 * private to amdgpu and we should not see any incoming fence-array
	 * from sync-file being in signal-on-any mode.
	 */

	fence_array = to_dma_fence_array(fence);
	for (i = 0; i < fence_array->num_fences; i++) {
		struct dma_fence *child = fence_array->fences[i];

		ret = dma_fence_wait(child, true);

		if (ret < 0)
			return ret;
	}

	return 0;
}