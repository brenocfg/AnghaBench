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
typedef  int uint32_t ;
struct radeon_ring {int idx; } ;
struct radeon_fence {int dummy; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int R600_RING_TYPE_UVD_INDEX ; 
 int TN_RING_TYPE_VCE1_INDEX ; 
 int TN_RING_TYPE_VCE2_INDEX ; 
 int radeon_fence_emit (struct radeon_device*,struct radeon_fence**,int) ; 
 int radeon_ring_lock (struct radeon_device*,struct radeon_ring*,int) ; 
 int /*<<< orphan*/  radeon_ring_unlock_commit (struct radeon_device*,struct radeon_ring*,int) ; 
 int /*<<< orphan*/  radeon_ring_unlock_undo (struct radeon_device*,struct radeon_ring*) ; 
 int radeon_uvd_get_create_msg (struct radeon_device*,int,int,int /*<<< orphan*/ *) ; 
 int radeon_uvd_get_destroy_msg (struct radeon_device*,int,int,struct radeon_fence**) ; 
 int radeon_vce_get_create_msg (struct radeon_device*,int,int,int /*<<< orphan*/ *) ; 
 int radeon_vce_get_destroy_msg (struct radeon_device*,int,int,struct radeon_fence**) ; 

__attribute__((used)) static int radeon_test_create_and_emit_fence(struct radeon_device *rdev,
					     struct radeon_ring *ring,
					     struct radeon_fence **fence)
{
	uint32_t handle = ring->idx ^ 0xdeafbeef;
	int r;

	if (ring->idx == R600_RING_TYPE_UVD_INDEX) {
		r = radeon_uvd_get_create_msg(rdev, ring->idx, handle, NULL);
		if (r) {
			DRM_ERROR("Failed to get dummy create msg\n");
			return r;
		}

		r = radeon_uvd_get_destroy_msg(rdev, ring->idx, handle, fence);
		if (r) {
			DRM_ERROR("Failed to get dummy destroy msg\n");
			return r;
		}

	} else if (ring->idx == TN_RING_TYPE_VCE1_INDEX ||
		   ring->idx == TN_RING_TYPE_VCE2_INDEX) {
		r = radeon_vce_get_create_msg(rdev, ring->idx, handle, NULL);
		if (r) {
			DRM_ERROR("Failed to get dummy create msg\n");
			return r;
		}

		r = radeon_vce_get_destroy_msg(rdev, ring->idx, handle, fence);
		if (r) {
			DRM_ERROR("Failed to get dummy destroy msg\n");
			return r;
		}

	} else {
		r = radeon_ring_lock(rdev, ring, 64);
		if (r) {
			DRM_ERROR("Failed to lock ring A %d\n", ring->idx);
			return r;
		}
		r = radeon_fence_emit(rdev, fence, ring->idx);
		if (r) {
			DRM_ERROR("Failed to emit fence\n");
			radeon_ring_unlock_undo(rdev, ring);
			return r;
		}
		radeon_ring_unlock_commit(rdev, ring, false);
	}
	return 0;
}