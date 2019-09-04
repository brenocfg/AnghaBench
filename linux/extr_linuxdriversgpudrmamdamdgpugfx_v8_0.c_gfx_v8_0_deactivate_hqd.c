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
typedef  int /*<<< orphan*/  u32 ;
struct amdgpu_device {int usec_timeout; } ;

/* Variables and functions */
 int CP_HQD_ACTIVE__ACTIVE_MASK ; 
 int /*<<< orphan*/  CP_HQD_DEQUEUE_REQUEST ; 
 int /*<<< orphan*/  DEQUEUE_REQ ; 
 int ETIMEDOUT ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmCP_HQD_ACTIVE ; 
 int /*<<< orphan*/  mmCP_HQD_DEQUEUE_REQUEST ; 
 int /*<<< orphan*/  mmCP_HQD_PQ_RPTR ; 
 int /*<<< orphan*/  mmCP_HQD_PQ_WPTR ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int gfx_v8_0_deactivate_hqd(struct amdgpu_device *adev, u32 req)
{
	int i, r = 0;

	if (RREG32(mmCP_HQD_ACTIVE) & CP_HQD_ACTIVE__ACTIVE_MASK) {
		WREG32_FIELD(CP_HQD_DEQUEUE_REQUEST, DEQUEUE_REQ, req);
		for (i = 0; i < adev->usec_timeout; i++) {
			if (!(RREG32(mmCP_HQD_ACTIVE) & CP_HQD_ACTIVE__ACTIVE_MASK))
				break;
			udelay(1);
		}
		if (i == adev->usec_timeout)
			r = -ETIMEDOUT;
	}
	WREG32(mmCP_HQD_DEQUEUE_REQUEST, 0);
	WREG32(mmCP_HQD_PQ_RPTR, 0);
	WREG32(mmCP_HQD_PQ_WPTR, 0);

	return r;
}