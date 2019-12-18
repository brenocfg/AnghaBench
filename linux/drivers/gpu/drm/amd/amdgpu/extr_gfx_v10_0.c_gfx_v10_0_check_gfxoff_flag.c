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
struct TYPE_2__ {int /*<<< orphan*/  pp_feature; } ;
struct amdgpu_device {int asic_type; TYPE_1__ pm; } ;

/* Variables and functions */
#define  CHIP_NAVI10 128 
 int /*<<< orphan*/  PP_GFXOFF_MASK ; 

__attribute__((used)) static void gfx_v10_0_check_gfxoff_flag(struct amdgpu_device *adev)
{
	switch (adev->asic_type) {
	case CHIP_NAVI10:
		adev->pm.pp_feature &= ~PP_GFXOFF_MASK;
		break;
	default:
		break;
	}
}