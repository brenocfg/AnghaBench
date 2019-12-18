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
struct TYPE_2__ {int /*<<< orphan*/ * cp_table_obj; int /*<<< orphan*/ * clear_state_obj; int /*<<< orphan*/ * save_restore_obj; } ;
struct radeon_device {TYPE_1__ rlc; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int radeon_bo_reserve (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  radeon_bo_unpin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_bo_unref (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  radeon_bo_unreserve (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void sumo_rlc_fini(struct radeon_device *rdev)
{
	int r;

	/* save restore block */
	if (rdev->rlc.save_restore_obj) {
		r = radeon_bo_reserve(rdev->rlc.save_restore_obj, false);
		if (unlikely(r != 0))
			dev_warn(rdev->dev, "(%d) reserve RLC sr bo failed\n", r);
		radeon_bo_unpin(rdev->rlc.save_restore_obj);
		radeon_bo_unreserve(rdev->rlc.save_restore_obj);

		radeon_bo_unref(&rdev->rlc.save_restore_obj);
		rdev->rlc.save_restore_obj = NULL;
	}

	/* clear state block */
	if (rdev->rlc.clear_state_obj) {
		r = radeon_bo_reserve(rdev->rlc.clear_state_obj, false);
		if (unlikely(r != 0))
			dev_warn(rdev->dev, "(%d) reserve RLC c bo failed\n", r);
		radeon_bo_unpin(rdev->rlc.clear_state_obj);
		radeon_bo_unreserve(rdev->rlc.clear_state_obj);

		radeon_bo_unref(&rdev->rlc.clear_state_obj);
		rdev->rlc.clear_state_obj = NULL;
	}

	/* clear state block */
	if (rdev->rlc.cp_table_obj) {
		r = radeon_bo_reserve(rdev->rlc.cp_table_obj, false);
		if (unlikely(r != 0))
			dev_warn(rdev->dev, "(%d) reserve RLC cp table bo failed\n", r);
		radeon_bo_unpin(rdev->rlc.cp_table_obj);
		radeon_bo_unreserve(rdev->rlc.cp_table_obj);

		radeon_bo_unref(&rdev->rlc.cp_table_obj);
		rdev->rlc.cp_table_obj = NULL;
	}
}