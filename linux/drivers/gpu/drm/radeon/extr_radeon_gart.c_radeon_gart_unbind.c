#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ ptr; int /*<<< orphan*/ * pages_entry; int /*<<< orphan*/ ** pages; int /*<<< orphan*/  ready; } ;
struct TYPE_3__ {int /*<<< orphan*/  entry; } ;
struct radeon_device {TYPE_2__ gart; TYPE_1__ dummy_page; } ;

/* Variables and functions */
 unsigned int PAGE_SIZE ; 
 unsigned int RADEON_GPU_PAGE_SIZE ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  radeon_gart_set_page (struct radeon_device*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_gart_tlb_flush (struct radeon_device*) ; 

void radeon_gart_unbind(struct radeon_device *rdev, unsigned offset,
			int pages)
{
	unsigned t;
	unsigned p;
	int i, j;

	if (!rdev->gart.ready) {
		WARN(1, "trying to unbind memory from uninitialized GART !\n");
		return;
	}
	t = offset / RADEON_GPU_PAGE_SIZE;
	p = t / (PAGE_SIZE / RADEON_GPU_PAGE_SIZE);
	for (i = 0; i < pages; i++, p++) {
		if (rdev->gart.pages[p]) {
			rdev->gart.pages[p] = NULL;
			for (j = 0; j < (PAGE_SIZE / RADEON_GPU_PAGE_SIZE); j++, t++) {
				rdev->gart.pages_entry[t] = rdev->dummy_page.entry;
				if (rdev->gart.ptr) {
					radeon_gart_set_page(rdev, t,
							     rdev->dummy_page.entry);
				}
			}
		}
	}
	if (rdev->gart.ptr) {
		mb();
		radeon_gart_tlb_flush(rdev);
	}
}