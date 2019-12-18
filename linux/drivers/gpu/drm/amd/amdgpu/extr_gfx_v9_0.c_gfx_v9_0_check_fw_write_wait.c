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
struct TYPE_2__ {int me_fw_write_wait; int mec_fw_write_wait; int mec_fw_version; int mec_feature_version; int pfp_fw_version; int pfp_feature_version; int me_fw_version; int me_feature_version; } ;
struct amdgpu_device {int asic_type; TYPE_1__ gfx; } ;

/* Variables and functions */
#define  CHIP_RAVEN 131 
#define  CHIP_VEGA10 130 
#define  CHIP_VEGA12 129 
#define  CHIP_VEGA20 128 
 int /*<<< orphan*/  DRM_WARN_ONCE (char*) ; 

__attribute__((used)) static void gfx_v9_0_check_fw_write_wait(struct amdgpu_device *adev)
{
	adev->gfx.me_fw_write_wait = false;
	adev->gfx.mec_fw_write_wait = false;

	if ((adev->gfx.mec_fw_version < 0x000001a5) ||
	    (adev->gfx.mec_feature_version < 46) ||
	    (adev->gfx.pfp_fw_version < 0x000000b7) ||
	    (adev->gfx.pfp_feature_version < 46))
		DRM_WARN_ONCE("Warning: check cp_fw_version and update it to realize \
			      GRBM requires 1-cycle delay in cp firmware\n");

	switch (adev->asic_type) {
	case CHIP_VEGA10:
		if ((adev->gfx.me_fw_version >= 0x0000009c) &&
		    (adev->gfx.me_feature_version >= 42) &&
		    (adev->gfx.pfp_fw_version >=  0x000000b1) &&
		    (adev->gfx.pfp_feature_version >= 42))
			adev->gfx.me_fw_write_wait = true;

		if ((adev->gfx.mec_fw_version >=  0x00000193) &&
		    (adev->gfx.mec_feature_version >= 42))
			adev->gfx.mec_fw_write_wait = true;
		break;
	case CHIP_VEGA12:
		if ((adev->gfx.me_fw_version >= 0x0000009c) &&
		    (adev->gfx.me_feature_version >= 44) &&
		    (adev->gfx.pfp_fw_version >=  0x000000b2) &&
		    (adev->gfx.pfp_feature_version >= 44))
			adev->gfx.me_fw_write_wait = true;

		if ((adev->gfx.mec_fw_version >=  0x00000196) &&
		    (adev->gfx.mec_feature_version >= 44))
			adev->gfx.mec_fw_write_wait = true;
		break;
	case CHIP_VEGA20:
		if ((adev->gfx.me_fw_version >= 0x0000009c) &&
		    (adev->gfx.me_feature_version >= 44) &&
		    (adev->gfx.pfp_fw_version >=  0x000000b2) &&
		    (adev->gfx.pfp_feature_version >= 44))
			adev->gfx.me_fw_write_wait = true;

		if ((adev->gfx.mec_fw_version >=  0x00000197) &&
		    (adev->gfx.mec_feature_version >= 44))
			adev->gfx.mec_fw_write_wait = true;
		break;
	case CHIP_RAVEN:
		if ((adev->gfx.me_fw_version >= 0x0000009c) &&
		    (adev->gfx.me_feature_version >= 42) &&
		    (adev->gfx.pfp_fw_version >=  0x000000b1) &&
		    (adev->gfx.pfp_feature_version >= 42))
			adev->gfx.me_fw_write_wait = true;

		if ((adev->gfx.mec_fw_version >=  0x00000192) &&
		    (adev->gfx.mec_feature_version >= 42))
			adev->gfx.mec_fw_write_wait = true;
		break;
	default:
		break;
	}
}