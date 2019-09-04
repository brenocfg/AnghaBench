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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {scalar_t__ buffer_funcs; } ;
struct amdgpu_device {TYPE_1__ mman; } ;
struct amdgpu_bo_param {unsigned int size; unsigned int domain; int /*<<< orphan*/ * resv; int /*<<< orphan*/  type; scalar_t__ flags; int /*<<< orphan*/  byte_align; } ;
struct amdgpu_bo {int /*<<< orphan*/  tbo; } ;
typedef  int /*<<< orphan*/  bp ;

/* Variables and functions */
 int AMDGPU_BENCHMARK_ITERATIONS ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int amdgpu_benchmark_do_move (struct amdgpu_device*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  amdgpu_benchmark_log_results (int,unsigned int,int,unsigned int,unsigned int,char*) ; 
 int amdgpu_bo_create (struct amdgpu_device*,struct amdgpu_bo_param*,struct amdgpu_bo**) ; 
 int /*<<< orphan*/  amdgpu_bo_gpu_offset (struct amdgpu_bo*) ; 
 int amdgpu_bo_pin (struct amdgpu_bo*,unsigned int) ; 
 int amdgpu_bo_reserve (struct amdgpu_bo*,int) ; 
 int /*<<< orphan*/  amdgpu_bo_unpin (struct amdgpu_bo*) ; 
 int /*<<< orphan*/  amdgpu_bo_unref (struct amdgpu_bo**) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (struct amdgpu_bo*) ; 
 int amdgpu_ttm_alloc_gart (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memset (struct amdgpu_bo_param*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ttm_bo_type_kernel ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void amdgpu_benchmark_move(struct amdgpu_device *adev, unsigned size,
				  unsigned sdomain, unsigned ddomain)
{
	struct amdgpu_bo *dobj = NULL;
	struct amdgpu_bo *sobj = NULL;
	struct amdgpu_bo_param bp;
	uint64_t saddr, daddr;
	int r, n;
	int time;

	memset(&bp, 0, sizeof(bp));
	bp.size = size;
	bp.byte_align = PAGE_SIZE;
	bp.domain = sdomain;
	bp.flags = 0;
	bp.type = ttm_bo_type_kernel;
	bp.resv = NULL;
	n = AMDGPU_BENCHMARK_ITERATIONS;
	r = amdgpu_bo_create(adev, &bp, &sobj);
	if (r) {
		goto out_cleanup;
	}
	r = amdgpu_bo_reserve(sobj, false);
	if (unlikely(r != 0))
		goto out_cleanup;
	r = amdgpu_bo_pin(sobj, sdomain);
	if (r) {
		amdgpu_bo_unreserve(sobj);
		goto out_cleanup;
	}
	r = amdgpu_ttm_alloc_gart(&sobj->tbo);
	amdgpu_bo_unreserve(sobj);
	if (r) {
		goto out_cleanup;
	}
	saddr = amdgpu_bo_gpu_offset(sobj);
	bp.domain = ddomain;
	r = amdgpu_bo_create(adev, &bp, &dobj);
	if (r) {
		goto out_cleanup;
	}
	r = amdgpu_bo_reserve(dobj, false);
	if (unlikely(r != 0))
		goto out_cleanup;
	r = amdgpu_bo_pin(dobj, ddomain);
	if (r) {
		amdgpu_bo_unreserve(sobj);
		goto out_cleanup;
	}
	r = amdgpu_ttm_alloc_gart(&dobj->tbo);
	amdgpu_bo_unreserve(dobj);
	if (r) {
		goto out_cleanup;
	}
	daddr = amdgpu_bo_gpu_offset(dobj);

	if (adev->mman.buffer_funcs) {
		time = amdgpu_benchmark_do_move(adev, size, saddr, daddr, n);
		if (time < 0)
			goto out_cleanup;
		if (time > 0)
			amdgpu_benchmark_log_results(n, size, time,
						     sdomain, ddomain, "dma");
	}

out_cleanup:
	/* Check error value now. The value can be overwritten when clean up.*/
	if (r) {
		DRM_ERROR("Error while benchmarking BO move.\n");
	}

	if (sobj) {
		r = amdgpu_bo_reserve(sobj, true);
		if (likely(r == 0)) {
			amdgpu_bo_unpin(sobj);
			amdgpu_bo_unreserve(sobj);
		}
		amdgpu_bo_unref(&sobj);
	}
	if (dobj) {
		r = amdgpu_bo_reserve(dobj, true);
		if (likely(r == 0)) {
			amdgpu_bo_unpin(dobj);
			amdgpu_bo_unreserve(dobj);
		}
		amdgpu_bo_unref(&dobj);
	}
}