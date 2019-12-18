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
typedef  int u32 ;
struct radeon_device {int usec_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 scalar_t__ RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMC_MESSAGE_0 ; 
 int /*<<< orphan*/  SMC_RESP_0 ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int trinity_notify_message_to_smu(struct radeon_device *rdev, u32 id)
{
	int i;
	u32 v = 0;

	WREG32(SMC_MESSAGE_0, id);
	for (i = 0; i < rdev->usec_timeout; i++) {
		if (RREG32(SMC_RESP_0) != 0)
			break;
		udelay(1);
	}
	v = RREG32(SMC_RESP_0);

	if (v != 1) {
		if (v == 0xFF) {
			DRM_ERROR("SMC failed to handle the message!\n");
			return -EINVAL;
		} else if (v == 0xFE) {
			DRM_ERROR("Unknown SMC message!\n");
			return -EINVAL;
		}
	}

	return 0;
}