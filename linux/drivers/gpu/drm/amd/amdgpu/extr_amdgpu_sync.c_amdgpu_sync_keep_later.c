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

/* Variables and functions */
 struct dma_fence* dma_fence_get (struct dma_fence*) ; 
 scalar_t__ dma_fence_is_later (struct dma_fence*,struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 

__attribute__((used)) static void amdgpu_sync_keep_later(struct dma_fence **keep,
				   struct dma_fence *fence)
{
	if (*keep && dma_fence_is_later(*keep, fence))
		return;

	dma_fence_put(*keep);
	*keep = dma_fence_get(fence);
}