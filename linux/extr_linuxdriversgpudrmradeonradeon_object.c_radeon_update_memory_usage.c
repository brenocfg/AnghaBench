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
typedef  int u64 ;
struct radeon_device {int /*<<< orphan*/  vram_usage; int /*<<< orphan*/  gtt_usage; } ;
struct TYPE_2__ {scalar_t__ num_pages; } ;
struct radeon_bo {TYPE_1__ tbo; struct radeon_device* rdev; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
#define  TTM_PL_TT 129 
#define  TTM_PL_VRAM 128 
 int /*<<< orphan*/  atomic64_add (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic64_sub (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void radeon_update_memory_usage(struct radeon_bo *bo,
				       unsigned mem_type, int sign)
{
	struct radeon_device *rdev = bo->rdev;
	u64 size = (u64)bo->tbo.num_pages << PAGE_SHIFT;

	switch (mem_type) {
	case TTM_PL_TT:
		if (sign > 0)
			atomic64_add(size, &rdev->gtt_usage);
		else
			atomic64_sub(size, &rdev->gtt_usage);
		break;
	case TTM_PL_VRAM:
		if (sign > 0)
			atomic64_add(size, &rdev->vram_usage);
		else
			atomic64_sub(size, &rdev->vram_usage);
		break;
	}
}