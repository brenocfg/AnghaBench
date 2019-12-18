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
struct amdgpu_device {int asic_type; int rev_id; TYPE_1__ gds; } ;

/* Variables and functions */
#define  CHIP_ARCTURUS 132 
#define  CHIP_RAVEN 131 
#define  CHIP_VEGA10 130 
#define  CHIP_VEGA12 129 
#define  CHIP_VEGA20 128 

__attribute__((used)) static void gfx_v9_0_set_gds_init(struct amdgpu_device *adev)
{
	/* init asci gds info */
	switch (adev->asic_type) {
	case CHIP_VEGA10:
	case CHIP_VEGA12:
	case CHIP_VEGA20:
		adev->gds.gds_size = 0x10000;
		break;
	case CHIP_RAVEN:
	case CHIP_ARCTURUS:
		adev->gds.gds_size = 0x1000;
		break;
	default:
		adev->gds.gds_size = 0x10000;
		break;
	}

	switch (adev->asic_type) {
	case CHIP_VEGA10:
	case CHIP_VEGA20:
		adev->gds.gds_compute_max_wave_id = 0x7ff;
		break;
	case CHIP_VEGA12:
		adev->gds.gds_compute_max_wave_id = 0x27f;
		break;
	case CHIP_RAVEN:
		if (adev->rev_id >= 0x8)
			adev->gds.gds_compute_max_wave_id = 0x77; /* raven2 */
		else
			adev->gds.gds_compute_max_wave_id = 0x15f; /* raven1 */
		break;
	case CHIP_ARCTURUS:
		adev->gds.gds_compute_max_wave_id = 0xfff;
		break;
	default:
		/* this really depends on the chip */
		adev->gds.gds_compute_max_wave_id = 0x7ff;
		break;
	}

	adev->gds.gws_size = 64;
	adev->gds.oa_size = 16;
}