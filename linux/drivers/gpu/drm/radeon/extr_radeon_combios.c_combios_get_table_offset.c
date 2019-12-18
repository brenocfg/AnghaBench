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
typedef  int uint16_t ;
struct radeon_device {int bios_header_start; int /*<<< orphan*/  bios; } ;
struct drm_device {struct radeon_device* dev_private; } ;
typedef  enum radeon_combios_table_offset { ____Placeholder_radeon_combios_table_offset } radeon_combios_table_offset ;

/* Variables and functions */
#define  COMBIOS_ASIC_INIT_1_TABLE 172 
#define  COMBIOS_ASIC_INIT_2_TABLE 171 
#define  COMBIOS_ASIC_INIT_3_TABLE 170 
#define  COMBIOS_ASIC_INIT_4_TABLE 169 
#define  COMBIOS_ASIC_INIT_5_TABLE 168 
#define  COMBIOS_BIOS_SUPPORT_TABLE 167 
#define  COMBIOS_COMPONENT_VIDEO_INFO_TABLE 166 
#define  COMBIOS_CONNECTOR_INFO_TABLE 165 
#define  COMBIOS_CRTC_INFO_TABLE 164 
#define  COMBIOS_CRT_INFO_TABLE 163 
#define  COMBIOS_DAC_PROGRAMMING_TABLE 162 
#define  COMBIOS_DETECTED_MEM_TABLE 161 
#define  COMBIOS_DFP_INFO_TABLE 160 
#define  COMBIOS_DYN_CLK_1_TABLE 159 
#define  COMBIOS_DYN_CLK_2_TABLE 158 
#define  COMBIOS_EXT_DAC_INFO_TABLE 157 
#define  COMBIOS_EXT_TMDS_INFO_TABLE 156 
#define  COMBIOS_FAN_SPEED_INFO_TABLE 155 
#define  COMBIOS_GPIO_INFO_TABLE 154 
#define  COMBIOS_HARDCODED_EDID_TABLE 153 
#define  COMBIOS_HW_CONFIG_INFO_TABLE 152 
#define  COMBIOS_I2C_INFO_TABLE 151 
#define  COMBIOS_INTEGRATED_SYSTEM_INFO_TABLE 150 
#define  COMBIOS_LCD_DDC_INFO_TABLE 149 
#define  COMBIOS_LCD_INFO_TABLE 148 
#define  COMBIOS_MAX_COLOR_DEPTH_TABLE 147 
#define  COMBIOS_MEM_CLK_INFO_TABLE 146 
#define  COMBIOS_MEM_CONFIG_TABLE 145 
#define  COMBIOS_MISC_INFO_TABLE 144 
#define  COMBIOS_MOBILE_INFO_TABLE 143 
#define  COMBIOS_MULTIMEDIA_INFO_TABLE 142 
#define  COMBIOS_OEM_INFO_TABLE 141 
#define  COMBIOS_OVERDRIVE_INFO_TABLE 140 
#define  COMBIOS_PLL_INFO_TABLE 139 
#define  COMBIOS_PLL_INIT_TABLE 138 
#define  COMBIOS_POWERPLAY_INFO_TABLE 137 
#define  COMBIOS_POWER_CONNECTOR_INFO_TABLE 136 
#define  COMBIOS_RAM_RESET_TABLE 135 
#define  COMBIOS_RESERVED_MEM_TABLE 134 
#define  COMBIOS_SAVE_MASK_TABLE 133 
#define  COMBIOS_TMDS_POWER_OFF_TABLE 132 
#define  COMBIOS_TMDS_POWER_ON_TABLE 131 
#define  COMBIOS_TMDS_POWER_TABLE 130 
#define  COMBIOS_TV_INFO_TABLE 129 
#define  COMBIOS_TV_STD_PATCH_TABLE 128 
 int RBIOS16 (int) ; 
 int RBIOS8 (int) ; 

__attribute__((used)) static uint16_t combios_get_table_offset(struct drm_device *dev,
					 enum radeon_combios_table_offset table)
{
	struct radeon_device *rdev = dev->dev_private;
	int rev, size;
	uint16_t offset = 0, check_offset;

	if (!rdev->bios)
		return 0;

	switch (table) {
		/* absolute offset tables */
	case COMBIOS_ASIC_INIT_1_TABLE:
		check_offset = 0xc;
		break;
	case COMBIOS_BIOS_SUPPORT_TABLE:
		check_offset = 0x14;
		break;
	case COMBIOS_DAC_PROGRAMMING_TABLE:
		check_offset = 0x2a;
		break;
	case COMBIOS_MAX_COLOR_DEPTH_TABLE:
		check_offset = 0x2c;
		break;
	case COMBIOS_CRTC_INFO_TABLE:
		check_offset = 0x2e;
		break;
	case COMBIOS_PLL_INFO_TABLE:
		check_offset = 0x30;
		break;
	case COMBIOS_TV_INFO_TABLE:
		check_offset = 0x32;
		break;
	case COMBIOS_DFP_INFO_TABLE:
		check_offset = 0x34;
		break;
	case COMBIOS_HW_CONFIG_INFO_TABLE:
		check_offset = 0x36;
		break;
	case COMBIOS_MULTIMEDIA_INFO_TABLE:
		check_offset = 0x38;
		break;
	case COMBIOS_TV_STD_PATCH_TABLE:
		check_offset = 0x3e;
		break;
	case COMBIOS_LCD_INFO_TABLE:
		check_offset = 0x40;
		break;
	case COMBIOS_MOBILE_INFO_TABLE:
		check_offset = 0x42;
		break;
	case COMBIOS_PLL_INIT_TABLE:
		check_offset = 0x46;
		break;
	case COMBIOS_MEM_CONFIG_TABLE:
		check_offset = 0x48;
		break;
	case COMBIOS_SAVE_MASK_TABLE:
		check_offset = 0x4a;
		break;
	case COMBIOS_HARDCODED_EDID_TABLE:
		check_offset = 0x4c;
		break;
	case COMBIOS_ASIC_INIT_2_TABLE:
		check_offset = 0x4e;
		break;
	case COMBIOS_CONNECTOR_INFO_TABLE:
		check_offset = 0x50;
		break;
	case COMBIOS_DYN_CLK_1_TABLE:
		check_offset = 0x52;
		break;
	case COMBIOS_RESERVED_MEM_TABLE:
		check_offset = 0x54;
		break;
	case COMBIOS_EXT_TMDS_INFO_TABLE:
		check_offset = 0x58;
		break;
	case COMBIOS_MEM_CLK_INFO_TABLE:
		check_offset = 0x5a;
		break;
	case COMBIOS_EXT_DAC_INFO_TABLE:
		check_offset = 0x5c;
		break;
	case COMBIOS_MISC_INFO_TABLE:
		check_offset = 0x5e;
		break;
	case COMBIOS_CRT_INFO_TABLE:
		check_offset = 0x60;
		break;
	case COMBIOS_INTEGRATED_SYSTEM_INFO_TABLE:
		check_offset = 0x62;
		break;
	case COMBIOS_COMPONENT_VIDEO_INFO_TABLE:
		check_offset = 0x64;
		break;
	case COMBIOS_FAN_SPEED_INFO_TABLE:
		check_offset = 0x66;
		break;
	case COMBIOS_OVERDRIVE_INFO_TABLE:
		check_offset = 0x68;
		break;
	case COMBIOS_OEM_INFO_TABLE:
		check_offset = 0x6a;
		break;
	case COMBIOS_DYN_CLK_2_TABLE:
		check_offset = 0x6c;
		break;
	case COMBIOS_POWER_CONNECTOR_INFO_TABLE:
		check_offset = 0x6e;
		break;
	case COMBIOS_I2C_INFO_TABLE:
		check_offset = 0x70;
		break;
		/* relative offset tables */
	case COMBIOS_ASIC_INIT_3_TABLE:	/* offset from misc info */
		check_offset =
		    combios_get_table_offset(dev, COMBIOS_MISC_INFO_TABLE);
		if (check_offset) {
			rev = RBIOS8(check_offset);
			if (rev > 0) {
				check_offset = RBIOS16(check_offset + 0x3);
				if (check_offset)
					offset = check_offset;
			}
		}
		break;
	case COMBIOS_ASIC_INIT_4_TABLE:	/* offset from misc info */
		check_offset =
		    combios_get_table_offset(dev, COMBIOS_MISC_INFO_TABLE);
		if (check_offset) {
			rev = RBIOS8(check_offset);
			if (rev > 0) {
				check_offset = RBIOS16(check_offset + 0x5);
				if (check_offset)
					offset = check_offset;
			}
		}
		break;
	case COMBIOS_DETECTED_MEM_TABLE:	/* offset from misc info */
		check_offset =
		    combios_get_table_offset(dev, COMBIOS_MISC_INFO_TABLE);
		if (check_offset) {
			rev = RBIOS8(check_offset);
			if (rev > 0) {
				check_offset = RBIOS16(check_offset + 0x7);
				if (check_offset)
					offset = check_offset;
			}
		}
		break;
	case COMBIOS_ASIC_INIT_5_TABLE:	/* offset from misc info */
		check_offset =
		    combios_get_table_offset(dev, COMBIOS_MISC_INFO_TABLE);
		if (check_offset) {
			rev = RBIOS8(check_offset);
			if (rev == 2) {
				check_offset = RBIOS16(check_offset + 0x9);
				if (check_offset)
					offset = check_offset;
			}
		}
		break;
	case COMBIOS_RAM_RESET_TABLE:	/* offset from mem config */
		check_offset =
		    combios_get_table_offset(dev, COMBIOS_MEM_CONFIG_TABLE);
		if (check_offset) {
			while (RBIOS8(check_offset++));
			check_offset += 2;
			if (check_offset)
				offset = check_offset;
		}
		break;
	case COMBIOS_POWERPLAY_INFO_TABLE:	/* offset from mobile info */
		check_offset =
		    combios_get_table_offset(dev, COMBIOS_MOBILE_INFO_TABLE);
		if (check_offset) {
			check_offset = RBIOS16(check_offset + 0x11);
			if (check_offset)
				offset = check_offset;
		}
		break;
	case COMBIOS_GPIO_INFO_TABLE:	/* offset from mobile info */
		check_offset =
		    combios_get_table_offset(dev, COMBIOS_MOBILE_INFO_TABLE);
		if (check_offset) {
			check_offset = RBIOS16(check_offset + 0x13);
			if (check_offset)
				offset = check_offset;
		}
		break;
	case COMBIOS_LCD_DDC_INFO_TABLE:	/* offset from mobile info */
		check_offset =
		    combios_get_table_offset(dev, COMBIOS_MOBILE_INFO_TABLE);
		if (check_offset) {
			check_offset = RBIOS16(check_offset + 0x15);
			if (check_offset)
				offset = check_offset;
		}
		break;
	case COMBIOS_TMDS_POWER_TABLE:	/* offset from mobile info */
		check_offset =
		    combios_get_table_offset(dev, COMBIOS_MOBILE_INFO_TABLE);
		if (check_offset) {
			check_offset = RBIOS16(check_offset + 0x17);
			if (check_offset)
				offset = check_offset;
		}
		break;
	case COMBIOS_TMDS_POWER_ON_TABLE:	/* offset from tmds power */
		check_offset =
		    combios_get_table_offset(dev, COMBIOS_TMDS_POWER_TABLE);
		if (check_offset) {
			check_offset = RBIOS16(check_offset + 0x2);
			if (check_offset)
				offset = check_offset;
		}
		break;
	case COMBIOS_TMDS_POWER_OFF_TABLE:	/* offset from tmds power */
		check_offset =
		    combios_get_table_offset(dev, COMBIOS_TMDS_POWER_TABLE);
		if (check_offset) {
			check_offset = RBIOS16(check_offset + 0x4);
			if (check_offset)
				offset = check_offset;
		}
		break;
	default:
		check_offset = 0;
		break;
	}

	size = RBIOS8(rdev->bios_header_start + 0x6);
	/* check absolute offset tables */
	if (table < COMBIOS_ASIC_INIT_3_TABLE && check_offset && check_offset < size)
		offset = RBIOS16(rdev->bios_header_start + check_offset);

	return offset;
}