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
struct radeon_fence {int /*<<< orphan*/  base; int /*<<< orphan*/  ring; int /*<<< orphan*/  seq; int /*<<< orphan*/  rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FENCE_TRACE (int /*<<< orphan*/ *,char*) ; 
 int dma_fence_signal (int /*<<< orphan*/ *) ; 
 scalar_t__ radeon_fence_seq_signaled (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool radeon_fence_signaled(struct radeon_fence *fence)
{
	if (!fence)
		return true;

	if (radeon_fence_seq_signaled(fence->rdev, fence->seq, fence->ring)) {
		int ret;

		ret = dma_fence_signal(&fence->base);
		if (!ret)
			DMA_FENCE_TRACE(&fence->base, "signaled from radeon_fence_signaled\n");
		return true;
	}
	return false;
}