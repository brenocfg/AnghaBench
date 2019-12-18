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
typedef  size_t u32 ;
struct TYPE_2__ {size_t num_crtc; } ;
struct amdgpu_device {TYPE_1__ mode_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTC_CONTROL ; 
 int /*<<< orphan*/  CRTC_MASTER_EN ; 
 scalar_t__ REG_GET_FIELD (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t RREG32 (scalar_t__) ; 
 scalar_t__* crtc_offsets ; 
 scalar_t__ mmCRTC_CONTROL ; 
 scalar_t__ mmCRTC_STATUS_HV_COUNT ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static bool dce_v11_0_is_display_hung(struct amdgpu_device *adev)
{
	u32 crtc_hung = 0;
	u32 crtc_status[6];
	u32 i, j, tmp;

	for (i = 0; i < adev->mode_info.num_crtc; i++) {
		tmp = RREG32(mmCRTC_CONTROL + crtc_offsets[i]);
		if (REG_GET_FIELD(tmp, CRTC_CONTROL, CRTC_MASTER_EN)) {
			crtc_status[i] = RREG32(mmCRTC_STATUS_HV_COUNT + crtc_offsets[i]);
			crtc_hung |= (1 << i);
		}
	}

	for (j = 0; j < 10; j++) {
		for (i = 0; i < adev->mode_info.num_crtc; i++) {
			if (crtc_hung & (1 << i)) {
				tmp = RREG32(mmCRTC_STATUS_HV_COUNT + crtc_offsets[i]);
				if (tmp != crtc_status[i])
					crtc_hung &= ~(1 << i);
			}
		}
		if (crtc_hung == 0)
			return false;
		udelay(100);
	}

	return true;
}