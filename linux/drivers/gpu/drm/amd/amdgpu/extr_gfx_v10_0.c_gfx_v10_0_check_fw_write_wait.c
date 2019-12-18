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
struct TYPE_2__ {int cp_fw_write_wait; int me_fw_version; int me_feature_version; int pfp_fw_version; int pfp_feature_version; int mec_fw_version; int mec_feature_version; } ;
struct amdgpu_device {int asic_type; TYPE_1__ gfx; } ;

/* Variables and functions */
#define  CHIP_NAVI10 130 
#define  CHIP_NAVI12 129 
#define  CHIP_NAVI14 128 
 int /*<<< orphan*/  DRM_WARN_ONCE (char*) ; 

__attribute__((used)) static void gfx_v10_0_check_fw_write_wait(struct amdgpu_device *adev)
{
	adev->gfx.cp_fw_write_wait = false;

	switch (adev->asic_type) {
	case CHIP_NAVI10:
	case CHIP_NAVI12:
	case CHIP_NAVI14:
		if ((adev->gfx.me_fw_version >= 0x00000046) &&
		    (adev->gfx.me_feature_version >= 27) &&
		    (adev->gfx.pfp_fw_version >= 0x00000068) &&
		    (adev->gfx.pfp_feature_version >= 27) &&
		    (adev->gfx.mec_fw_version >= 0x0000005b) &&
		    (adev->gfx.mec_feature_version >= 27))
			adev->gfx.cp_fw_write_wait = true;
		break;
	default:
		break;
	}

	if (adev->gfx.cp_fw_write_wait == false)
		DRM_WARN_ONCE("Warning: check cp_fw_version and update it to realize \
			      GRBM requires 1-cycle delay in cp firmware\n");
}