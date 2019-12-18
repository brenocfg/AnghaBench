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
struct radeon_device {scalar_t__ usec_timeout; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMC_MESSAGE_0 ; 
 scalar_t__ SMC_MSG_MASK ; 
 int /*<<< orphan*/  SMC_RESP_0 ; 
 scalar_t__ SMC_RESP_MASK ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

int kv_notify_message_to_smu(struct radeon_device *rdev, u32 id)
{
	u32 i;
	u32 tmp = 0;

	WREG32(SMC_MESSAGE_0, id & SMC_MSG_MASK);

	for (i = 0; i < rdev->usec_timeout; i++) {
		if ((RREG32(SMC_RESP_0) & SMC_RESP_MASK) != 0)
			break;
		udelay(1);
	}
	tmp = RREG32(SMC_RESP_0) & SMC_RESP_MASK;

	if (tmp != 1) {
		if (tmp == 0xFF)
			return -EINVAL;
		else if (tmp == 0xFE)
			return -EINVAL;
	}

	return 0;
}