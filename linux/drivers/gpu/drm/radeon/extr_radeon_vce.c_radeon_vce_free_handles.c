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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/ * handles; struct drm_file** filp; } ;
struct radeon_device {TYPE_1__ vce; } ;
struct drm_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int RADEON_MAX_VCE_HANDLES ; 
 int /*<<< orphan*/  TN_RING_TYPE_VCE1_INDEX ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int radeon_vce_get_destroy_msg (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_vce_note_usage (struct radeon_device*) ; 

void radeon_vce_free_handles(struct radeon_device *rdev, struct drm_file *filp)
{
	int i, r;
	for (i = 0; i < RADEON_MAX_VCE_HANDLES; ++i) {
		uint32_t handle = atomic_read(&rdev->vce.handles[i]);
		if (!handle || rdev->vce.filp[i] != filp)
			continue;

		radeon_vce_note_usage(rdev);

		r = radeon_vce_get_destroy_msg(rdev, TN_RING_TYPE_VCE1_INDEX,
					       handle, NULL);
		if (r)
			DRM_ERROR("Error destroying VCE handle (%d)!\n", r);

		rdev->vce.filp[i] = NULL;
		atomic_set(&rdev->vce.handles[i], 0);
	}
}