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
struct TYPE_2__ {int /*<<< orphan*/ * vcpu_bo; } ;
struct radeon_device {int /*<<< orphan*/  uvd_fw; int /*<<< orphan*/ * ring; TYPE_1__ uvd; } ;

/* Variables and functions */
 size_t R600_RING_TYPE_UVD_INDEX ; 
 int /*<<< orphan*/  radeon_bo_kunmap (int /*<<< orphan*/ *) ; 
 int radeon_bo_reserve (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  radeon_bo_unpin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_bo_unref (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  radeon_bo_unreserve (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_ring_fini (struct radeon_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ ) ; 

void radeon_uvd_fini(struct radeon_device *rdev)
{
	int r;

	if (rdev->uvd.vcpu_bo == NULL)
		return;

	r = radeon_bo_reserve(rdev->uvd.vcpu_bo, false);
	if (!r) {
		radeon_bo_kunmap(rdev->uvd.vcpu_bo);
		radeon_bo_unpin(rdev->uvd.vcpu_bo);
		radeon_bo_unreserve(rdev->uvd.vcpu_bo);
	}

	radeon_bo_unref(&rdev->uvd.vcpu_bo);

	radeon_ring_fini(rdev, &rdev->ring[R600_RING_TYPE_UVD_INDEX]);

	release_firmware(rdev->uvd_fw);
}