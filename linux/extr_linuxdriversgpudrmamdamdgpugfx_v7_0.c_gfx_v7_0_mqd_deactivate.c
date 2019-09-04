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
struct amdgpu_device {int usec_timeout; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmCP_HQD_ACTIVE ; 
 int /*<<< orphan*/  mmCP_HQD_DEQUEUE_REQUEST ; 
 int /*<<< orphan*/  mmCP_HQD_PQ_RPTR ; 
 int /*<<< orphan*/  mmCP_HQD_PQ_WPTR ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int gfx_v7_0_mqd_deactivate(struct amdgpu_device *adev)
{
	int i;

	/* disable the queue if it's active */
	if (RREG32(mmCP_HQD_ACTIVE) & 1) {
		WREG32(mmCP_HQD_DEQUEUE_REQUEST, 1);
		for (i = 0; i < adev->usec_timeout; i++) {
			if (!(RREG32(mmCP_HQD_ACTIVE) & 1))
				break;
			udelay(1);
		}

		if (i == adev->usec_timeout)
			return -ETIMEDOUT;

		WREG32(mmCP_HQD_DEQUEUE_REQUEST, 0);
		WREG32(mmCP_HQD_PQ_RPTR, 0);
		WREG32(mmCP_HQD_PQ_WPTR, 0);
	}

	return 0;
}