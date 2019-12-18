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
struct TYPE_2__ {int /*<<< orphan*/ * wb_obj; int /*<<< orphan*/ * wb; } ;
struct radeon_device {TYPE_1__ wb; } ;

/* Variables and functions */
 int /*<<< orphan*/  radeon_bo_kunmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_bo_reserve (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  radeon_bo_unpin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_bo_unref (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  radeon_bo_unreserve (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_wb_disable (struct radeon_device*) ; 

void radeon_wb_fini(struct radeon_device *rdev)
{
	radeon_wb_disable(rdev);
	if (rdev->wb.wb_obj) {
		if (!radeon_bo_reserve(rdev->wb.wb_obj, false)) {
			radeon_bo_kunmap(rdev->wb.wb_obj);
			radeon_bo_unpin(rdev->wb.wb_obj);
			radeon_bo_unreserve(rdev->wb.wb_obj);
		}
		radeon_bo_unref(&rdev->wb.wb_obj);
		rdev->wb.wb = NULL;
		rdev->wb.wb_obj = NULL;
	}
}