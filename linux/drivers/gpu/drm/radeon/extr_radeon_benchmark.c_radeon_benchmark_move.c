#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct radeon_device {TYPE_2__* asic; } ;
struct TYPE_7__ {int /*<<< orphan*/  resv; } ;
struct TYPE_8__ {TYPE_3__ base; } ;
struct radeon_bo {TYPE_4__ tbo; } ;
struct TYPE_5__ {scalar_t__ blit; scalar_t__ dma; } ;
struct TYPE_6__ {TYPE_1__ copy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  RADEON_BENCHMARK_COPY_BLIT ; 
 int /*<<< orphan*/  RADEON_BENCHMARK_COPY_DMA ; 
 int RADEON_BENCHMARK_ITERATIONS ; 
 scalar_t__ likely (int) ; 
 int radeon_benchmark_do_move (struct radeon_device*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_benchmark_log_results (int,unsigned int,int,unsigned int,unsigned int,char*) ; 
 int radeon_bo_create (struct radeon_device*,unsigned int,int /*<<< orphan*/ ,int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct radeon_bo**) ; 
 int radeon_bo_pin (struct radeon_bo*,unsigned int,int /*<<< orphan*/ *) ; 
 int radeon_bo_reserve (struct radeon_bo*,int) ; 
 int /*<<< orphan*/  radeon_bo_unpin (struct radeon_bo*) ; 
 int /*<<< orphan*/  radeon_bo_unref (struct radeon_bo**) ; 
 int /*<<< orphan*/  radeon_bo_unreserve (struct radeon_bo*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void radeon_benchmark_move(struct radeon_device *rdev, unsigned size,
				  unsigned sdomain, unsigned ddomain)
{
	struct radeon_bo *dobj = NULL;
	struct radeon_bo *sobj = NULL;
	uint64_t saddr, daddr;
	int r, n;
	int time;

	n = RADEON_BENCHMARK_ITERATIONS;
	r = radeon_bo_create(rdev, size, PAGE_SIZE, true, sdomain, 0, NULL, NULL, &sobj);
	if (r) {
		goto out_cleanup;
	}
	r = radeon_bo_reserve(sobj, false);
	if (unlikely(r != 0))
		goto out_cleanup;
	r = radeon_bo_pin(sobj, sdomain, &saddr);
	radeon_bo_unreserve(sobj);
	if (r) {
		goto out_cleanup;
	}
	r = radeon_bo_create(rdev, size, PAGE_SIZE, true, ddomain, 0, NULL, NULL, &dobj);
	if (r) {
		goto out_cleanup;
	}
	r = radeon_bo_reserve(dobj, false);
	if (unlikely(r != 0))
		goto out_cleanup;
	r = radeon_bo_pin(dobj, ddomain, &daddr);
	radeon_bo_unreserve(dobj);
	if (r) {
		goto out_cleanup;
	}

	if (rdev->asic->copy.dma) {
		time = radeon_benchmark_do_move(rdev, size, saddr, daddr,
						RADEON_BENCHMARK_COPY_DMA, n,
						dobj->tbo.base.resv);
		if (time < 0)
			goto out_cleanup;
		if (time > 0)
			radeon_benchmark_log_results(n, size, time,
						     sdomain, ddomain, "dma");
	}

	if (rdev->asic->copy.blit) {
		time = radeon_benchmark_do_move(rdev, size, saddr, daddr,
						RADEON_BENCHMARK_COPY_BLIT, n,
						dobj->tbo.base.resv);
		if (time < 0)
			goto out_cleanup;
		if (time > 0)
			radeon_benchmark_log_results(n, size, time,
						     sdomain, ddomain, "blit");
	}

out_cleanup:
	if (sobj) {
		r = radeon_bo_reserve(sobj, false);
		if (likely(r == 0)) {
			radeon_bo_unpin(sobj);
			radeon_bo_unreserve(sobj);
		}
		radeon_bo_unref(&sobj);
	}
	if (dobj) {
		r = radeon_bo_reserve(dobj, false);
		if (likely(r == 0)) {
			radeon_bo_unpin(dobj);
			radeon_bo_unreserve(dobj);
		}
		radeon_bo_unref(&dobj);
	}

	if (r) {
		DRM_ERROR("Error while benchmarking BO move.\n");
	}
}