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
struct drm_file {int dummy; } ;
struct amdgpu_ring {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * handles; struct drm_file** filp; struct amdgpu_ring* ring; } ;
struct amdgpu_device {TYPE_1__ vce; } ;

/* Variables and functions */
 int AMDGPU_MAX_VCE_HANDLES ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int amdgpu_vce_get_destroy_msg (struct amdgpu_ring*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void amdgpu_vce_free_handles(struct amdgpu_device *adev, struct drm_file *filp)
{
	struct amdgpu_ring *ring = &adev->vce.ring[0];
	int i, r;
	for (i = 0; i < AMDGPU_MAX_VCE_HANDLES; ++i) {
		uint32_t handle = atomic_read(&adev->vce.handles[i]);

		if (!handle || adev->vce.filp[i] != filp)
			continue;

		r = amdgpu_vce_get_destroy_msg(ring, handle, false, NULL);
		if (r)
			DRM_ERROR("Error destroying VCE handle (%d)!\n", r);

		adev->vce.filp[i] = NULL;
		atomic_set(&adev->vce.handles[i], 0);
	}
}