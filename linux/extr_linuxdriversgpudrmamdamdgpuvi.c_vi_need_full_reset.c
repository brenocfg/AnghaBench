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
#define  CHIP_CARRIZO 135 
#define  CHIP_FIJI 134 
#define  CHIP_POLARIS10 133 
#define  CHIP_POLARIS11 132 
#define  CHIP_POLARIS12 131 
#define  CHIP_STONEY 130 
#define  CHIP_TONGA 129 
#define  CHIP_TOPAZ 128 

__attribute__((used)) static bool vi_need_full_reset(struct amdgpu_device *adev)
{
	switch (adev->asic_type) {
	case CHIP_CARRIZO:
	case CHIP_STONEY:
		/* CZ has hang issues with full reset at the moment */
		return false;
	case CHIP_FIJI:
	case CHIP_TONGA:
		/* XXX: soft reset should work on fiji and tonga */
		return true;
	case CHIP_POLARIS10:
	case CHIP_POLARIS11:
	case CHIP_POLARIS12:
	case CHIP_TOPAZ:
	default:
		/* change this when we support soft reset */
		return true;
	}
}