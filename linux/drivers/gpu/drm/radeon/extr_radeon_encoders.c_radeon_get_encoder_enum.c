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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct radeon_device {int /*<<< orphan*/  family; } ;
struct drm_device {struct radeon_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_IS_AVIVO (struct radeon_device*) ; 
#define  ATOM_DEVICE_CRT1_SUPPORT 137 
#define  ATOM_DEVICE_CRT2_SUPPORT 136 
#define  ATOM_DEVICE_CV_SUPPORT 135 
#define  ATOM_DEVICE_DFP1_SUPPORT 134 
#define  ATOM_DEVICE_DFP2_SUPPORT 133 
#define  ATOM_DEVICE_DFP3_SUPPORT 132 
#define  ATOM_DEVICE_LCD1_SUPPORT 131 
#define  ATOM_DEVICE_LCD2_SUPPORT 130 
#define  ATOM_DEVICE_TV1_SUPPORT 129 
#define  ATOM_DEVICE_TV2_SUPPORT 128 
 int /*<<< orphan*/  CHIP_RS300 ; 
 int /*<<< orphan*/  CHIP_RS400 ; 
 int /*<<< orphan*/  CHIP_RS480 ; 
 int /*<<< orphan*/  CHIP_RS600 ; 
 int /*<<< orphan*/  CHIP_RS690 ; 
 int /*<<< orphan*/  CHIP_RS740 ; 
 int ENCODER_INTERNAL_DAC1_ENUM_ID1 ; 
 int ENCODER_INTERNAL_DAC2_ENUM_ID1 ; 
 int ENCODER_INTERNAL_DDI_ENUM_ID1 ; 
 int ENCODER_INTERNAL_DVO1_ENUM_ID1 ; 
 int ENCODER_INTERNAL_KLDSCP_DAC1_ENUM_ID1 ; 
 int ENCODER_INTERNAL_KLDSCP_DAC2_ENUM_ID1 ; 
 int ENCODER_INTERNAL_KLDSCP_DVO1_ENUM_ID1 ; 
 int ENCODER_INTERNAL_KLDSCP_TMDS1_ENUM_ID1 ; 
 int ENCODER_INTERNAL_LVDS_ENUM_ID1 ; 
 int ENCODER_INTERNAL_LVTM1_ENUM_ID1 ; 
 int ENCODER_INTERNAL_TMDS1_ENUM_ID1 ; 

uint32_t
radeon_get_encoder_enum(struct drm_device *dev, uint32_t supported_device, uint8_t dac)
{
	struct radeon_device *rdev = dev->dev_private;
	uint32_t ret = 0;

	switch (supported_device) {
	case ATOM_DEVICE_CRT1_SUPPORT:
	case ATOM_DEVICE_TV1_SUPPORT:
	case ATOM_DEVICE_TV2_SUPPORT:
	case ATOM_DEVICE_CRT2_SUPPORT:
	case ATOM_DEVICE_CV_SUPPORT:
		switch (dac) {
		case 1: /* dac a */
			if ((rdev->family == CHIP_RS300) ||
			    (rdev->family == CHIP_RS400) ||
			    (rdev->family == CHIP_RS480))
				ret = ENCODER_INTERNAL_DAC2_ENUM_ID1;
			else if (ASIC_IS_AVIVO(rdev))
				ret = ENCODER_INTERNAL_KLDSCP_DAC1_ENUM_ID1;
			else
				ret = ENCODER_INTERNAL_DAC1_ENUM_ID1;
			break;
		case 2: /* dac b */
			if (ASIC_IS_AVIVO(rdev))
				ret = ENCODER_INTERNAL_KLDSCP_DAC2_ENUM_ID1;
			else {
				/*if (rdev->family == CHIP_R200)
				  ret = ENCODER_INTERNAL_DVO1_ENUM_ID1;
				  else*/
				ret = ENCODER_INTERNAL_DAC2_ENUM_ID1;
			}
			break;
		case 3: /* external dac */
			if (ASIC_IS_AVIVO(rdev))
				ret = ENCODER_INTERNAL_KLDSCP_DVO1_ENUM_ID1;
			else
				ret = ENCODER_INTERNAL_DVO1_ENUM_ID1;
			break;
		}
		break;
	case ATOM_DEVICE_LCD1_SUPPORT:
		if (ASIC_IS_AVIVO(rdev))
			ret = ENCODER_INTERNAL_LVTM1_ENUM_ID1;
		else
			ret = ENCODER_INTERNAL_LVDS_ENUM_ID1;
		break;
	case ATOM_DEVICE_DFP1_SUPPORT:
		if ((rdev->family == CHIP_RS300) ||
		    (rdev->family == CHIP_RS400) ||
		    (rdev->family == CHIP_RS480))
			ret = ENCODER_INTERNAL_DVO1_ENUM_ID1;
		else if (ASIC_IS_AVIVO(rdev))
			ret = ENCODER_INTERNAL_KLDSCP_TMDS1_ENUM_ID1;
		else
			ret = ENCODER_INTERNAL_TMDS1_ENUM_ID1;
		break;
	case ATOM_DEVICE_LCD2_SUPPORT:
	case ATOM_DEVICE_DFP2_SUPPORT:
		if ((rdev->family == CHIP_RS600) ||
		    (rdev->family == CHIP_RS690) ||
		    (rdev->family == CHIP_RS740))
			ret = ENCODER_INTERNAL_DDI_ENUM_ID1;
		else if (ASIC_IS_AVIVO(rdev))
			ret = ENCODER_INTERNAL_KLDSCP_DVO1_ENUM_ID1;
		else
			ret = ENCODER_INTERNAL_DVO1_ENUM_ID1;
		break;
	case ATOM_DEVICE_DFP3_SUPPORT:
		ret = ENCODER_INTERNAL_LVTM1_ENUM_ID1;
		break;
	}

	return ret;
}