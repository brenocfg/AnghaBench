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
#define  CHIP_FIJI 129 
#define  CHIP_TONGA 128 

__attribute__((used)) static int dce_v10_0_get_num_crtc(struct amdgpu_device *adev)
{
	int num_crtc = 0;

	switch (adev->asic_type) {
	case CHIP_FIJI:
	case CHIP_TONGA:
		num_crtc = 6;
		break;
	default:
		num_crtc = 0;
	}
	return num_crtc;
}