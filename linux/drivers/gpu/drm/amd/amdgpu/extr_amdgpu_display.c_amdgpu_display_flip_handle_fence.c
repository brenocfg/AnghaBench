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
struct dma_fence {int dummy; } ;
struct amdgpu_flip_work {int /*<<< orphan*/  cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_display_flip_callback ; 
 int /*<<< orphan*/  dma_fence_add_callback (struct dma_fence*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 

__attribute__((used)) static bool amdgpu_display_flip_handle_fence(struct amdgpu_flip_work *work,
					     struct dma_fence **f)
{
	struct dma_fence *fence= *f;

	if (fence == NULL)
		return false;

	*f = NULL;

	if (!dma_fence_add_callback(fence, &work->cb,
				    amdgpu_display_flip_callback))
		return true;

	dma_fence_put(fence);
	return false;
}