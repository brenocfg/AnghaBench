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
typedef  int /*<<< orphan*/  uint64_t ;
struct radeon_fence {int dummy; } ;
struct radeon_device {int dummy; } ;
struct dma_resv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct radeon_fence*) ; 
 int PTR_ERR (struct radeon_fence*) ; 
#define  RADEON_BENCHMARK_COPY_BLIT 129 
#define  RADEON_BENCHMARK_COPY_DMA 128 
 unsigned int RADEON_GPU_PAGE_SIZE ; 
 unsigned long jiffies ; 
 int jiffies_to_msecs (unsigned long) ; 
 struct radeon_fence* radeon_copy_blit (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,struct dma_resv*) ; 
 struct radeon_fence* radeon_copy_dma (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,struct dma_resv*) ; 
 int /*<<< orphan*/  radeon_fence_unref (struct radeon_fence**) ; 
 int radeon_fence_wait (struct radeon_fence*,int) ; 

__attribute__((used)) static int radeon_benchmark_do_move(struct radeon_device *rdev, unsigned size,
				    uint64_t saddr, uint64_t daddr,
				    int flag, int n,
				    struct dma_resv *resv)
{
	unsigned long start_jiffies;
	unsigned long end_jiffies;
	struct radeon_fence *fence = NULL;
	int i, r;

	start_jiffies = jiffies;
	for (i = 0; i < n; i++) {
		switch (flag) {
		case RADEON_BENCHMARK_COPY_DMA:
			fence = radeon_copy_dma(rdev, saddr, daddr,
						size / RADEON_GPU_PAGE_SIZE,
						resv);
			break;
		case RADEON_BENCHMARK_COPY_BLIT:
			fence = radeon_copy_blit(rdev, saddr, daddr,
						 size / RADEON_GPU_PAGE_SIZE,
						 resv);
			break;
		default:
			DRM_ERROR("Unknown copy method\n");
			return -EINVAL;
		}
		if (IS_ERR(fence))
			return PTR_ERR(fence);

		r = radeon_fence_wait(fence, false);
		radeon_fence_unref(&fence);
		if (r)
			return r;
	}
	end_jiffies = jiffies;
	return jiffies_to_msecs(end_jiffies - start_jiffies);
}