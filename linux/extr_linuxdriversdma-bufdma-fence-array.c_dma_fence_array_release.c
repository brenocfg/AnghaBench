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
struct dma_fence_array {unsigned int num_fences; int /*<<< orphan*/ * fences; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_fence_free (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 struct dma_fence_array* to_dma_fence_array (struct dma_fence*) ; 

__attribute__((used)) static void dma_fence_array_release(struct dma_fence *fence)
{
	struct dma_fence_array *array = to_dma_fence_array(fence);
	unsigned i;

	for (i = 0; i < array->num_fences; ++i)
		dma_fence_put(array->fences[i]);

	kfree(array->fences);
	dma_fence_free(fence);
}