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
struct radeon_ring {int dummy; } ;
struct TYPE_3__ {int max_hw_contexts; } ;
struct TYPE_4__ {TYPE_1__ si; } ;
struct radeon_device {struct radeon_ring* ring; TYPE_2__ config; } ;

/* Variables and functions */
 int CAYMAN_RING_TYPE_CP2_INDEX ; 
 int /*<<< orphan*/  CE_PARTITION_BASE ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int PACKET3_BASE_INDEX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PACKET3_CLEAR_STATE ; 
 int PACKET3_COMPUTE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PACKET3_ME_INITIALIZE ; 
 int PACKET3_ME_INITIALIZE_DEVICE_ID (int) ; 
 int PACKET3_PREAMBLE_BEGIN_CLEAR_STATE ; 
 int /*<<< orphan*/  PACKET3_PREAMBLE_CNTL ; 
 int PACKET3_PREAMBLE_END_CLEAR_STATE ; 
 int /*<<< orphan*/  PACKET3_SET_BASE ; 
 int /*<<< orphan*/  PACKET3_SET_CONTEXT_REG ; 
 size_t RADEON_RING_TYPE_GFX_INDEX ; 
 int radeon_ring_lock (struct radeon_device*,struct radeon_ring*,int) ; 
 int /*<<< orphan*/  radeon_ring_unlock_commit (struct radeon_device*,struct radeon_ring*,int) ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,int) ; 
 int /*<<< orphan*/  si_cp_enable (struct radeon_device*,int) ; 
 int si_default_size ; 
 int* si_default_state ; 

__attribute__((used)) static int si_cp_start(struct radeon_device *rdev)
{
	struct radeon_ring *ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	int r, i;

	r = radeon_ring_lock(rdev, ring, 7 + 4);
	if (r) {
		DRM_ERROR("radeon: cp failed to lock ring (%d).\n", r);
		return r;
	}
	/* init the CP */
	radeon_ring_write(ring, PACKET3(PACKET3_ME_INITIALIZE, 5));
	radeon_ring_write(ring, 0x1);
	radeon_ring_write(ring, 0x0);
	radeon_ring_write(ring, rdev->config.si.max_hw_contexts - 1);
	radeon_ring_write(ring, PACKET3_ME_INITIALIZE_DEVICE_ID(1));
	radeon_ring_write(ring, 0);
	radeon_ring_write(ring, 0);

	/* init the CE partitions */
	radeon_ring_write(ring, PACKET3(PACKET3_SET_BASE, 2));
	radeon_ring_write(ring, PACKET3_BASE_INDEX(CE_PARTITION_BASE));
	radeon_ring_write(ring, 0xc000);
	radeon_ring_write(ring, 0xe000);
	radeon_ring_unlock_commit(rdev, ring, false);

	si_cp_enable(rdev, true);

	r = radeon_ring_lock(rdev, ring, si_default_size + 10);
	if (r) {
		DRM_ERROR("radeon: cp failed to lock ring (%d).\n", r);
		return r;
	}

	/* setup clear context state */
	radeon_ring_write(ring, PACKET3(PACKET3_PREAMBLE_CNTL, 0));
	radeon_ring_write(ring, PACKET3_PREAMBLE_BEGIN_CLEAR_STATE);

	for (i = 0; i < si_default_size; i++)
		radeon_ring_write(ring, si_default_state[i]);

	radeon_ring_write(ring, PACKET3(PACKET3_PREAMBLE_CNTL, 0));
	radeon_ring_write(ring, PACKET3_PREAMBLE_END_CLEAR_STATE);

	/* set clear context state */
	radeon_ring_write(ring, PACKET3(PACKET3_CLEAR_STATE, 0));
	radeon_ring_write(ring, 0);

	radeon_ring_write(ring, PACKET3(PACKET3_SET_CONTEXT_REG, 2));
	radeon_ring_write(ring, 0x00000316);
	radeon_ring_write(ring, 0x0000000e); /* VGT_VERTEX_REUSE_BLOCK_CNTL */
	radeon_ring_write(ring, 0x00000010); /* VGT_OUT_DEALLOC_CNTL */

	radeon_ring_unlock_commit(rdev, ring, false);

	for (i = RADEON_RING_TYPE_GFX_INDEX; i <= CAYMAN_RING_TYPE_CP2_INDEX; ++i) {
		ring = &rdev->ring[i];
		r = radeon_ring_lock(rdev, ring, 2);

		/* clear the compute context state */
		radeon_ring_write(ring, PACKET3_COMPUTE(PACKET3_CLEAR_STATE, 0));
		radeon_ring_write(ring, 0);

		radeon_ring_unlock_commit(rdev, ring, false);
	}

	return 0;
}