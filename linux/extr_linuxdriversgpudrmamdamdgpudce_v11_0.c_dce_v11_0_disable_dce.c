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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTC_CONTROL ; 
 int /*<<< orphan*/  CRTC_MASTER_EN ; 
 int REG_GET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int REG_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RREG32 (scalar_t__) ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 
 scalar_t__ amdgpu_atombios_has_dce_engine_info (struct amdgpu_device*) ; 
 scalar_t__* crtc_offsets ; 
 int dce_v11_0_get_num_crtc (struct amdgpu_device*) ; 
 int /*<<< orphan*/  dce_v11_0_set_vga_render_state (struct amdgpu_device*,int) ; 
 scalar_t__ mmCRTC_CONTROL ; 
 scalar_t__ mmCRTC_UPDATE_LOCK ; 

void dce_v11_0_disable_dce(struct amdgpu_device *adev)
{
	/*Disable VGA render and enabled crtc, if has DCE engine*/
	if (amdgpu_atombios_has_dce_engine_info(adev)) {
		u32 tmp;
		int crtc_enabled, i;

		dce_v11_0_set_vga_render_state(adev, false);

		/*Disable crtc*/
		for (i = 0; i < dce_v11_0_get_num_crtc(adev); i++) {
			crtc_enabled = REG_GET_FIELD(RREG32(mmCRTC_CONTROL + crtc_offsets[i]),
									 CRTC_CONTROL, CRTC_MASTER_EN);
			if (crtc_enabled) {
				WREG32(mmCRTC_UPDATE_LOCK + crtc_offsets[i], 1);
				tmp = RREG32(mmCRTC_CONTROL + crtc_offsets[i]);
				tmp = REG_SET_FIELD(tmp, CRTC_CONTROL, CRTC_MASTER_EN, 0);
				WREG32(mmCRTC_CONTROL + crtc_offsets[i], tmp);
				WREG32(mmCRTC_UPDATE_LOCK + crtc_offsets[i], 0);
			}
		}
	}
}