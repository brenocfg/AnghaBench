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
struct TYPE_2__ {int num_gpu_pages; int /*<<< orphan*/ * pages_entry; int /*<<< orphan*/  table_addr; int /*<<< orphan*/  robj; int /*<<< orphan*/  ptr; } ;
struct radeon_device {TYPE_1__ gart; } ;

/* Variables and functions */
 int /*<<< orphan*/  RADEON_GEM_DOMAIN_VRAM ; 
 int /*<<< orphan*/  mb () ; 
 int radeon_bo_kmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int radeon_bo_pin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int radeon_bo_reserve (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radeon_bo_unpin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_bo_unreserve (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_gart_set_page (struct radeon_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_gart_tlb_flush (struct radeon_device*) ; 
 scalar_t__ unlikely (int) ; 

int radeon_gart_table_vram_pin(struct radeon_device *rdev)
{
	uint64_t gpu_addr;
	int r;

	r = radeon_bo_reserve(rdev->gart.robj, false);
	if (unlikely(r != 0))
		return r;
	r = radeon_bo_pin(rdev->gart.robj,
				RADEON_GEM_DOMAIN_VRAM, &gpu_addr);
	if (r) {
		radeon_bo_unreserve(rdev->gart.robj);
		return r;
	}
	r = radeon_bo_kmap(rdev->gart.robj, &rdev->gart.ptr);
	if (r)
		radeon_bo_unpin(rdev->gart.robj);
	radeon_bo_unreserve(rdev->gart.robj);
	rdev->gart.table_addr = gpu_addr;

	if (!r) {
		int i;

		/* We might have dropped some GART table updates while it wasn't
		 * mapped, restore all entries
		 */
		for (i = 0; i < rdev->gart.num_gpu_pages; i++)
			radeon_gart_set_page(rdev, i, rdev->gart.pages_entry[i]);
		mb();
		radeon_gart_tlb_flush(rdev);
	}

	return r;
}