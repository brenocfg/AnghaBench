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
typedef  int /*<<< orphan*/  u8 ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {struct amdgpu_device* dev_private; } ;
struct amdgpu_encoder_atom_dig {int /*<<< orphan*/  backlight_level; } ;
struct amdgpu_encoder {int devices; int encoder_id; struct amdgpu_encoder_atom_dig* enc_priv; struct drm_encoder base; } ;
struct TYPE_2__ {int firmware_flags; } ;
struct amdgpu_device {TYPE_1__ mode_info; } ;

/* Variables and functions */
 int ATOM_BIOS_INFO_BL_CONTROLLED_BY_GPU ; 
 int ATOM_DEVICE_LCD_SUPPORT ; 
 int /*<<< orphan*/  ATOM_TRANSMITTER_ACTION_BL_BRIGHTNESS_CONTROL ; 
 int /*<<< orphan*/  ATOM_TRANSMITTER_ACTION_LCD_BLOFF ; 
 int /*<<< orphan*/  ATOM_TRANSMITTER_ACTION_LCD_BLON ; 
#define  ENCODER_OBJECT_ID_INTERNAL_KLDSCP_LVTMA 132 
#define  ENCODER_OBJECT_ID_INTERNAL_UNIPHY 131 
#define  ENCODER_OBJECT_ID_INTERNAL_UNIPHY1 130 
#define  ENCODER_OBJECT_ID_INTERNAL_UNIPHY2 129 
#define  ENCODER_OBJECT_ID_INTERNAL_UNIPHY3 128 
 int /*<<< orphan*/  amdgpu_atombios_encoder_set_backlight_level_to_reg (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_atombios_encoder_setup_dig_transmitter (struct drm_encoder*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
amdgpu_atombios_encoder_set_backlight_level(struct amdgpu_encoder *amdgpu_encoder,
				     u8 level)
{
	struct drm_encoder *encoder = &amdgpu_encoder->base;
	struct drm_device *dev = amdgpu_encoder->base.dev;
	struct amdgpu_device *adev = dev->dev_private;
	struct amdgpu_encoder_atom_dig *dig;

	if (!(adev->mode_info.firmware_flags & ATOM_BIOS_INFO_BL_CONTROLLED_BY_GPU))
		return;

	if ((amdgpu_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT)) &&
	    amdgpu_encoder->enc_priv) {
		dig = amdgpu_encoder->enc_priv;
		dig->backlight_level = level;
		amdgpu_atombios_encoder_set_backlight_level_to_reg(adev, dig->backlight_level);

		switch (amdgpu_encoder->encoder_id) {
		case ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
		case ENCODER_OBJECT_ID_INTERNAL_KLDSCP_LVTMA:
		case ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
		case ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
		case ENCODER_OBJECT_ID_INTERNAL_UNIPHY3:
			if (dig->backlight_level == 0)
				amdgpu_atombios_encoder_setup_dig_transmitter(encoder,
								       ATOM_TRANSMITTER_ACTION_LCD_BLOFF, 0, 0);
			else {
				amdgpu_atombios_encoder_setup_dig_transmitter(encoder,
								       ATOM_TRANSMITTER_ACTION_BL_BRIGHTNESS_CONTROL, 0, 0);
				amdgpu_atombios_encoder_setup_dig_transmitter(encoder,
								       ATOM_TRANSMITTER_ACTION_LCD_BLON, 0, 0);
			}
			break;
		default:
			break;
		}
	}
}