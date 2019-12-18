#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int pp_feature; } ;
struct TYPE_6__ {int /*<<< orphan*/  is_rlc_v2_1; } ;
struct TYPE_7__ {int rlc_fw_version; int rlc_feature_version; TYPE_2__ rlc; } ;
struct amdgpu_device {int asic_type; int rev_id; int pg_flags; TYPE_4__ pm; TYPE_3__ gfx; TYPE_1__* pdev; } ;
struct TYPE_5__ {int device; } ;

/* Variables and functions */
 int AMD_PG_SUPPORT_CP ; 
 int AMD_PG_SUPPORT_GFX_PG ; 
 int AMD_PG_SUPPORT_RLC_SMU_HS ; 
#define  CHIP_RAVEN 132 
#define  CHIP_RENOIR 131 
#define  CHIP_VEGA10 130 
#define  CHIP_VEGA12 129 
#define  CHIP_VEGA20 128 
 int PP_GFXOFF_MASK ; 

__attribute__((used)) static void gfx_v9_0_check_if_need_gfxoff(struct amdgpu_device *adev)
{
	switch (adev->asic_type) {
	case CHIP_VEGA10:
	case CHIP_VEGA12:
	case CHIP_VEGA20:
		break;
	case CHIP_RAVEN:
		if (!(adev->rev_id >= 0x8 || adev->pdev->device == 0x15d8)
			&&((adev->gfx.rlc_fw_version != 106 &&
			     adev->gfx.rlc_fw_version < 531) ||
			    (adev->gfx.rlc_fw_version == 53815) ||
			    (adev->gfx.rlc_feature_version < 1) ||
			    !adev->gfx.rlc.is_rlc_v2_1))
			adev->pm.pp_feature &= ~PP_GFXOFF_MASK;

		if (adev->pm.pp_feature & PP_GFXOFF_MASK)
			adev->pg_flags |= AMD_PG_SUPPORT_GFX_PG |
				AMD_PG_SUPPORT_CP |
				AMD_PG_SUPPORT_RLC_SMU_HS;
		break;
	case CHIP_RENOIR:
		if (adev->pm.pp_feature & PP_GFXOFF_MASK)
			adev->pg_flags |= AMD_PG_SUPPORT_GFX_PG |
				AMD_PG_SUPPORT_CP |
				AMD_PG_SUPPORT_RLC_SMU_HS;
		break;
	default:
		break;
	}
}