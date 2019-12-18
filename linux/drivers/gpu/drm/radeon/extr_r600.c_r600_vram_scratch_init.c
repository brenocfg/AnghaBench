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
struct TYPE_2__ {int /*<<< orphan*/ * robj; int /*<<< orphan*/  ptr; int /*<<< orphan*/  gpu_addr; } ;
struct radeon_device {TYPE_1__ vram_scratch; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  RADEON_GEM_DOMAIN_VRAM ; 
 int /*<<< orphan*/  RADEON_GPU_PAGE_SIZE ; 
 int radeon_bo_create (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int radeon_bo_kmap (int /*<<< orphan*/ *,void**) ; 
 int radeon_bo_pin (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int radeon_bo_reserve (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  radeon_bo_unpin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_bo_unreserve (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int r600_vram_scratch_init(struct radeon_device *rdev)
{
	int r;

	if (rdev->vram_scratch.robj == NULL) {
		r = radeon_bo_create(rdev, RADEON_GPU_PAGE_SIZE,
				     PAGE_SIZE, true, RADEON_GEM_DOMAIN_VRAM,
				     0, NULL, NULL, &rdev->vram_scratch.robj);
		if (r) {
			return r;
		}
	}

	r = radeon_bo_reserve(rdev->vram_scratch.robj, false);
	if (unlikely(r != 0))
		return r;
	r = radeon_bo_pin(rdev->vram_scratch.robj,
			  RADEON_GEM_DOMAIN_VRAM, &rdev->vram_scratch.gpu_addr);
	if (r) {
		radeon_bo_unreserve(rdev->vram_scratch.robj);
		return r;
	}
	r = radeon_bo_kmap(rdev->vram_scratch.robj,
				(void **)&rdev->vram_scratch.ptr);
	if (r)
		radeon_bo_unpin(rdev->vram_scratch.robj);
	radeon_bo_unreserve(rdev->vram_scratch.robj);

	return r;
}