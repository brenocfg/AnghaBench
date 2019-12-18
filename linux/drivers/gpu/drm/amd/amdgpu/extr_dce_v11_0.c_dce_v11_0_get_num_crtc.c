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
struct amdgpu_device {int asic_type; } ;

/* Variables and functions */
#define  CHIP_CARRIZO 133 
#define  CHIP_POLARIS10 132 
#define  CHIP_POLARIS11 131 
#define  CHIP_POLARIS12 130 
#define  CHIP_STONEY 129 
#define  CHIP_VEGAM 128 

__attribute__((used)) static int dce_v11_0_get_num_crtc (struct amdgpu_device *adev)
{
	int num_crtc = 0;

	switch (adev->asic_type) {
	case CHIP_CARRIZO:
		num_crtc = 3;
		break;
	case CHIP_STONEY:
		num_crtc = 2;
		break;
	case CHIP_POLARIS10:
	case CHIP_VEGAM:
		num_crtc = 6;
		break;
	case CHIP_POLARIS11:
	case CHIP_POLARIS12:
		num_crtc = 5;
		break;
	default:
		num_crtc = 0;
	}
	return num_crtc;
}