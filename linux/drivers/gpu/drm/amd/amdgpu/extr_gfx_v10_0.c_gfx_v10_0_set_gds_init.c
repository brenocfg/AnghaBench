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
struct TYPE_2__ {int gds_size; int gds_compute_max_wave_id; int gws_size; int oa_size; } ;
struct amdgpu_device {int asic_type; TYPE_1__ gds; } ;

/* Variables and functions */
#define  CHIP_NAVI10 128 

__attribute__((used)) static void gfx_v10_0_set_gds_init(struct amdgpu_device *adev)
{
	/* init asic gds info */
	switch (adev->asic_type) {
	case CHIP_NAVI10:
	default:
		adev->gds.gds_size = 0x10000;
		adev->gds.gds_compute_max_wave_id = 0x4ff;
		break;
	}

	adev->gds.gws_size = 64;
	adev->gds.oa_size = 16;
}