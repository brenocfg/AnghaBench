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
typedef  scalar_t__ uint32_t ;
struct radeon_fence {int dummy; } ;
struct TYPE_2__ {int max_handles; int /*<<< orphan*/ * handles; int /*<<< orphan*/ ** filp; int /*<<< orphan*/ * vcpu_bo; } ;
struct radeon_device {TYPE_1__ uvd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  R600_RING_TYPE_UVD_INDEX ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_fence_unref (struct radeon_fence**) ; 
 int /*<<< orphan*/  radeon_fence_wait (struct radeon_fence*,int) ; 
 int radeon_uvd_get_destroy_msg (struct radeon_device*,int /*<<< orphan*/ ,scalar_t__,struct radeon_fence**) ; 
 int /*<<< orphan*/  radeon_uvd_note_usage (struct radeon_device*) ; 

int radeon_uvd_suspend(struct radeon_device *rdev)
{
	int i, r;

	if (rdev->uvd.vcpu_bo == NULL)
		return 0;

	for (i = 0; i < rdev->uvd.max_handles; ++i) {
		uint32_t handle = atomic_read(&rdev->uvd.handles[i]);
		if (handle != 0) {
			struct radeon_fence *fence;

			radeon_uvd_note_usage(rdev);

			r = radeon_uvd_get_destroy_msg(rdev,
				R600_RING_TYPE_UVD_INDEX, handle, &fence);
			if (r) {
				DRM_ERROR("Error destroying UVD (%d)!\n", r);
				continue;
			}

			radeon_fence_wait(fence, false);
			radeon_fence_unref(&fence);

			rdev->uvd.filp[i] = NULL;
			atomic_set(&rdev->uvd.handles[i], 0);
		}
	}

	return 0;
}