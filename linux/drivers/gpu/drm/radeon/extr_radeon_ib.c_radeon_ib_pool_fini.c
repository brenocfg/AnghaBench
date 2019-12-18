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
struct radeon_device {int ib_pool_ready; int /*<<< orphan*/  ring_tmp_bo; } ;

/* Variables and functions */
 int /*<<< orphan*/  radeon_sa_bo_manager_fini (struct radeon_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_sa_bo_manager_suspend (struct radeon_device*,int /*<<< orphan*/ *) ; 

void radeon_ib_pool_fini(struct radeon_device *rdev)
{
	if (rdev->ib_pool_ready) {
		radeon_sa_bo_manager_suspend(rdev, &rdev->ring_tmp_bo);
		radeon_sa_bo_manager_fini(rdev, &rdev->ring_tmp_bo);
		rdev->ib_pool_ready = false;
	}
}