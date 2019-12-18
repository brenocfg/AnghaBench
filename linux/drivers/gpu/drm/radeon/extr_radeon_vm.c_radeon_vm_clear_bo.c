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
struct ttm_operation_ctx {int member_0; int member_1; } ;
struct radeon_ib {int length_dw; TYPE_1__* fence; } ;
struct radeon_device {int dummy; } ;
struct radeon_bo {int /*<<< orphan*/  placement; int /*<<< orphan*/  tbo; } ;
struct TYPE_2__ {int is_vm_update; } ;

/* Variables and functions */
 int /*<<< orphan*/  R600_RING_TYPE_DMA_INDEX ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  radeon_asic_vm_pad_ib (struct radeon_device*,struct radeon_ib*) ; 
 int /*<<< orphan*/  radeon_bo_fence (struct radeon_bo*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  radeon_bo_gpu_offset (struct radeon_bo*) ; 
 int radeon_bo_reserve (struct radeon_bo*,int) ; 
 int radeon_bo_size (struct radeon_bo*) ; 
 int /*<<< orphan*/  radeon_bo_unreserve (struct radeon_bo*) ; 
 int /*<<< orphan*/  radeon_ib_free (struct radeon_device*,struct radeon_ib*) ; 
 int radeon_ib_get (struct radeon_device*,int /*<<< orphan*/ ,struct radeon_ib*,int /*<<< orphan*/ *,int) ; 
 int radeon_ib_schedule (struct radeon_device*,struct radeon_ib*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  radeon_vm_set_pages (struct radeon_device*,struct radeon_ib*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ttm_bo_validate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ttm_operation_ctx*) ; 

__attribute__((used)) static int radeon_vm_clear_bo(struct radeon_device *rdev,
			      struct radeon_bo *bo)
{
	struct ttm_operation_ctx ctx = { true, false };
	struct radeon_ib ib;
	unsigned entries;
	uint64_t addr;
	int r;

	r = radeon_bo_reserve(bo, false);
	if (r)
		return r;

	r = ttm_bo_validate(&bo->tbo, &bo->placement, &ctx);
	if (r)
		goto error_unreserve;

	addr = radeon_bo_gpu_offset(bo);
	entries = radeon_bo_size(bo) / 8;

	r = radeon_ib_get(rdev, R600_RING_TYPE_DMA_INDEX, &ib, NULL, 256);
	if (r)
		goto error_unreserve;

	ib.length_dw = 0;

	radeon_vm_set_pages(rdev, &ib, addr, 0, entries, 0, 0);
	radeon_asic_vm_pad_ib(rdev, &ib);
	WARN_ON(ib.length_dw > 64);

	r = radeon_ib_schedule(rdev, &ib, NULL, false);
	if (r)
		goto error_free;

	ib.fence->is_vm_update = true;
	radeon_bo_fence(bo, ib.fence, false);

error_free:
	radeon_ib_free(rdev, &ib);

error_unreserve:
	radeon_bo_unreserve(bo);
	return r;
}