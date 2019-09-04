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
struct radeon_ring {int ready; } ;
struct radeon_device {int family; struct radeon_ring* ring; } ;

/* Variables and functions */
#define  CHIP_RV610 132 
#define  CHIP_RV620 131 
#define  CHIP_RV630 130 
#define  CHIP_RV635 129 
#define  CHIP_RV670 128 
 int CHIP_RV740 ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int /*<<< orphan*/  MC_CONFIG ; 
 int PACKET0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t R600_RING_TYPE_UVD_INDEX ; 
 int /*<<< orphan*/  RS_DQ_RD_RET_CONF ; 
 int /*<<< orphan*/  UVD_SEMA_CNTL ; 
 int /*<<< orphan*/  UVD_SEMA_SIGNAL_INCOMPLETE_TIMEOUT_CNTL ; 
 int /*<<< orphan*/  UVD_SEMA_TIMEOUT_STATUS ; 
 int /*<<< orphan*/  UVD_SEMA_WAIT_FAULT_TIMEOUT_CNTL ; 
 int /*<<< orphan*/  UVD_SEMA_WAIT_INCOMPLETE_TIMEOUT_CNTL ; 
 int /*<<< orphan*/  UVD_VCPU_CNTL ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int,int) ; 
 int radeon_ring_lock (struct radeon_device*,struct radeon_ring*,int) ; 
 int radeon_ring_test (struct radeon_device*,size_t,struct radeon_ring*) ; 
 int /*<<< orphan*/  radeon_ring_unlock_commit (struct radeon_device*,struct radeon_ring*,int) ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,int) ; 
 int /*<<< orphan*/  radeon_set_uvd_clocks (struct radeon_device*,int,int) ; 
 int uvd_v1_0_start (struct radeon_device*) ; 

int uvd_v1_0_init(struct radeon_device *rdev)
{
	struct radeon_ring *ring = &rdev->ring[R600_RING_TYPE_UVD_INDEX];
	uint32_t tmp;
	int r;

	/* raise clocks while booting up the VCPU */
	if (rdev->family < CHIP_RV740)
		radeon_set_uvd_clocks(rdev, 10000, 10000);
	else
		radeon_set_uvd_clocks(rdev, 53300, 40000);

	r = uvd_v1_0_start(rdev);
	if (r)
		goto done;

	ring->ready = true;
	r = radeon_ring_test(rdev, R600_RING_TYPE_UVD_INDEX, ring);
	if (r) {
		ring->ready = false;
		goto done;
	}

	r = radeon_ring_lock(rdev, ring, 10);
	if (r) {
		DRM_ERROR("radeon: ring failed to lock UVD ring (%d).\n", r);
		goto done;
	}

	tmp = PACKET0(UVD_SEMA_WAIT_FAULT_TIMEOUT_CNTL, 0);
	radeon_ring_write(ring, tmp);
	radeon_ring_write(ring, 0xFFFFF);

	tmp = PACKET0(UVD_SEMA_WAIT_INCOMPLETE_TIMEOUT_CNTL, 0);
	radeon_ring_write(ring, tmp);
	radeon_ring_write(ring, 0xFFFFF);

	tmp = PACKET0(UVD_SEMA_SIGNAL_INCOMPLETE_TIMEOUT_CNTL, 0);
	radeon_ring_write(ring, tmp);
	radeon_ring_write(ring, 0xFFFFF);

	/* Clear timeout status bits */
	radeon_ring_write(ring, PACKET0(UVD_SEMA_TIMEOUT_STATUS, 0));
	radeon_ring_write(ring, 0x8);

	radeon_ring_write(ring, PACKET0(UVD_SEMA_CNTL, 0));
	radeon_ring_write(ring, 3);

	radeon_ring_unlock_commit(rdev, ring, false);

done:
	/* lower clocks again */
	radeon_set_uvd_clocks(rdev, 0, 0);

	if (!r) {
		switch (rdev->family) {
		case CHIP_RV610:
		case CHIP_RV630:
		case CHIP_RV620:
			/* 64byte granularity workaround */
			WREG32(MC_CONFIG, 0);
			WREG32(MC_CONFIG, 1 << 4);
			WREG32(RS_DQ_RD_RET_CONF, 0x3f);
			WREG32(MC_CONFIG, 0x1f);

			/* fall through */
		case CHIP_RV670:
		case CHIP_RV635:

			/* write clean workaround */
			WREG32_P(UVD_VCPU_CNTL, 0x10, ~0x10);
			break;

		default:
			/* TODO: Do we need more? */
			break;
		}

		DRM_INFO("UVD initialized successfully.\n");
	}

	return r;
}