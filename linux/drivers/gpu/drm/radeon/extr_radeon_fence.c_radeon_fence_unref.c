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
struct radeon_fence {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_fence_put (int /*<<< orphan*/ *) ; 

void radeon_fence_unref(struct radeon_fence **fence)
{
	struct radeon_fence *tmp = *fence;

	*fence = NULL;
	if (tmp) {
		dma_fence_put(&tmp->base);
	}
}