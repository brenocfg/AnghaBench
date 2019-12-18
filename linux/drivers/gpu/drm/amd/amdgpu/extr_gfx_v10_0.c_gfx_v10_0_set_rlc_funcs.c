#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * funcs; } ;
struct TYPE_4__ {TYPE_1__ rlc; } ;
struct amdgpu_device {int asic_type; TYPE_2__ gfx; } ;

/* Variables and functions */
#define  CHIP_NAVI10 130 
#define  CHIP_NAVI12 129 
#define  CHIP_NAVI14 128 
 int /*<<< orphan*/  gfx_v10_0_rlc_funcs ; 

__attribute__((used)) static void gfx_v10_0_set_rlc_funcs(struct amdgpu_device *adev)
{
	switch (adev->asic_type) {
	case CHIP_NAVI10:
	case CHIP_NAVI14:
	case CHIP_NAVI12:
		adev->gfx.rlc.funcs = &gfx_v10_0_rlc_funcs;
		break;
	default:
		break;
	}
}