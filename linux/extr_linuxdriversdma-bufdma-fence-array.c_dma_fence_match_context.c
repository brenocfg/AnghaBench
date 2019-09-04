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
typedef  scalar_t__ u64 ;
struct dma_fence_array {unsigned int num_fences; TYPE_1__** fences; } ;
struct dma_fence {scalar_t__ context; } ;
struct TYPE_2__ {scalar_t__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_fence_is_array (struct dma_fence*) ; 
 struct dma_fence_array* to_dma_fence_array (struct dma_fence*) ; 

bool dma_fence_match_context(struct dma_fence *fence, u64 context)
{
	struct dma_fence_array *array = to_dma_fence_array(fence);
	unsigned i;

	if (!dma_fence_is_array(fence))
		return fence->context == context;

	for (i = 0; i < array->num_fences; i++) {
		if (array->fences[i]->context != context)
			return false;
	}

	return true;
}