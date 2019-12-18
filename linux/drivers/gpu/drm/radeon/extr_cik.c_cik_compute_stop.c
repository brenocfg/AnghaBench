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
typedef  scalar_t__ u32 ;
struct radeon_ring {int /*<<< orphan*/  queue; int /*<<< orphan*/  pipe; int /*<<< orphan*/  me; } ;
struct radeon_device {scalar_t__ usec_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP_HQD_ACTIVE ; 
 int /*<<< orphan*/  CP_HQD_DEQUEUE_REQUEST ; 
 int /*<<< orphan*/  CP_HQD_PQ_RPTR ; 
 int /*<<< orphan*/  CP_HQD_PQ_WPTR ; 
 int /*<<< orphan*/  CP_PQ_WPTR_POLL_CNTL ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 scalar_t__ WPTR_POLL_EN ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cik_srbm_select (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void cik_compute_stop(struct radeon_device *rdev,
			     struct radeon_ring *ring)
{
	u32 j, tmp;

	cik_srbm_select(rdev, ring->me, ring->pipe, ring->queue, 0);
	/* Disable wptr polling. */
	tmp = RREG32(CP_PQ_WPTR_POLL_CNTL);
	tmp &= ~WPTR_POLL_EN;
	WREG32(CP_PQ_WPTR_POLL_CNTL, tmp);
	/* Disable HQD. */
	if (RREG32(CP_HQD_ACTIVE) & 1) {
		WREG32(CP_HQD_DEQUEUE_REQUEST, 1);
		for (j = 0; j < rdev->usec_timeout; j++) {
			if (!(RREG32(CP_HQD_ACTIVE) & 1))
				break;
			udelay(1);
		}
		WREG32(CP_HQD_DEQUEUE_REQUEST, 0);
		WREG32(CP_HQD_PQ_RPTR, 0);
		WREG32(CP_HQD_PQ_WPTR, 0);
	}
	cik_srbm_select(rdev, 0, 0, 0, 0);
}