#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int ucMisc; int ucAction; int /*<<< orphan*/  ucTemporal; int /*<<< orphan*/  ucSpatial; int /*<<< orphan*/  ucFRC; int /*<<< orphan*/  ucTruncate; void* usPixelClock; } ;
struct TYPE_4__ {int ucMisc; int ucAction; void* usPixelClock; } ;
union lvds_encoder_control {TYPE_2__ v2; TYPE_1__ v1; } ;
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct radeon_encoder_atom_dig {int lcd_misc; int /*<<< orphan*/  linkb; int /*<<< orphan*/  coherent_mode; } ;
struct radeon_encoder {int encoder_id; int devices; int pixel_clock; struct radeon_encoder_atom_dig* enc_priv; } ;
struct TYPE_6__ {int /*<<< orphan*/  atom_context; } ;
struct radeon_device {TYPE_3__ mode_info; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {struct radeon_device* dev_private; } ;
typedef  int /*<<< orphan*/  args ;

/* Variables and functions */
 int ATOM_DEVICE_LCD_SUPPORT ; 
 scalar_t__ ATOM_ENCODER_MODE_HDMI ; 
 int ATOM_PANEL_MISC_888RGB ; 
 int ATOM_PANEL_MISC_DUAL ; 
 int ATOM_PANEL_MISC_GREY_LEVEL_SHIFT ; 
 int ATOM_PANEL_MISC_SPATIAL ; 
 int ATOM_PANEL_MISC_TEMPORAL ; 
 int /*<<< orphan*/  COMMAND ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,int) ; 
#define  ENCODER_OBJECT_ID_INTERNAL_KLDSCP_TMDS1 131 
#define  ENCODER_OBJECT_ID_INTERNAL_LVDS 130 
#define  ENCODER_OBJECT_ID_INTERNAL_LVTM1 129 
#define  ENCODER_OBJECT_ID_INTERNAL_TMDS1 128 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LVDSEncoderControl ; 
 int PANEL_ENCODER_MISC_COHERENT ; 
 int PANEL_ENCODER_MISC_DUAL ; 
 int PANEL_ENCODER_MISC_HDMI_TYPE ; 
 int PANEL_ENCODER_MISC_TMDS_LINKB ; 
 int /*<<< orphan*/  PANEL_ENCODER_SPATIAL_DITHER_DEPTH ; 
 int /*<<< orphan*/  PANEL_ENCODER_SPATIAL_DITHER_EN ; 
 int /*<<< orphan*/  PANEL_ENCODER_TEMPORAL_DITHER_DEPTH ; 
 int /*<<< orphan*/  PANEL_ENCODER_TEMPORAL_DITHER_EN ; 
 int /*<<< orphan*/  PANEL_ENCODER_TEMPORAL_LEVEL_4 ; 
 int /*<<< orphan*/  TMDS1EncoderControl ; 
 int /*<<< orphan*/  TMDS2EncoderControl ; 
 int /*<<< orphan*/  atom_execute_table (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atom_parse_cmd_header (int /*<<< orphan*/ ,int,int*,int*) ; 
 scalar_t__ atombios_get_encoder_mode (struct drm_encoder*) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  memset (union lvds_encoder_control*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radeon_dig_monitor_is_duallink (struct drm_encoder*,int) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

void
atombios_digital_setup(struct drm_encoder *encoder, int action)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	struct radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;
	union lvds_encoder_control args;
	int index = 0;
	int hdmi_detected = 0;
	uint8_t frev, crev;

	if (!dig)
		return;

	if (atombios_get_encoder_mode(encoder) == ATOM_ENCODER_MODE_HDMI)
		hdmi_detected = 1;

	memset(&args, 0, sizeof(args));

	switch (radeon_encoder->encoder_id) {
	case ENCODER_OBJECT_ID_INTERNAL_LVDS:
		index = GetIndexIntoMasterTable(COMMAND, LVDSEncoderControl);
		break;
	case ENCODER_OBJECT_ID_INTERNAL_TMDS1:
	case ENCODER_OBJECT_ID_INTERNAL_KLDSCP_TMDS1:
		index = GetIndexIntoMasterTable(COMMAND, TMDS1EncoderControl);
		break;
	case ENCODER_OBJECT_ID_INTERNAL_LVTM1:
		if (radeon_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT))
			index = GetIndexIntoMasterTable(COMMAND, LVDSEncoderControl);
		else
			index = GetIndexIntoMasterTable(COMMAND, TMDS2EncoderControl);
		break;
	}

	if (!atom_parse_cmd_header(rdev->mode_info.atom_context, index, &frev, &crev))
		return;

	switch (frev) {
	case 1:
	case 2:
		switch (crev) {
		case 1:
			args.v1.ucMisc = 0;
			args.v1.ucAction = action;
			if (hdmi_detected)
				args.v1.ucMisc |= PANEL_ENCODER_MISC_HDMI_TYPE;
			args.v1.usPixelClock = cpu_to_le16(radeon_encoder->pixel_clock / 10);
			if (radeon_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT)) {
				if (dig->lcd_misc & ATOM_PANEL_MISC_DUAL)
					args.v1.ucMisc |= PANEL_ENCODER_MISC_DUAL;
				if (dig->lcd_misc & ATOM_PANEL_MISC_888RGB)
					args.v1.ucMisc |= ATOM_PANEL_MISC_888RGB;
			} else {
				if (dig->linkb)
					args.v1.ucMisc |= PANEL_ENCODER_MISC_TMDS_LINKB;
				if (radeon_dig_monitor_is_duallink(encoder, radeon_encoder->pixel_clock))
					args.v1.ucMisc |= PANEL_ENCODER_MISC_DUAL;
				/*if (pScrn->rgbBits == 8) */
				args.v1.ucMisc |= ATOM_PANEL_MISC_888RGB;
			}
			break;
		case 2:
		case 3:
			args.v2.ucMisc = 0;
			args.v2.ucAction = action;
			if (crev == 3) {
				if (dig->coherent_mode)
					args.v2.ucMisc |= PANEL_ENCODER_MISC_COHERENT;
			}
			if (hdmi_detected)
				args.v2.ucMisc |= PANEL_ENCODER_MISC_HDMI_TYPE;
			args.v2.usPixelClock = cpu_to_le16(radeon_encoder->pixel_clock / 10);
			args.v2.ucTruncate = 0;
			args.v2.ucSpatial = 0;
			args.v2.ucTemporal = 0;
			args.v2.ucFRC = 0;
			if (radeon_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT)) {
				if (dig->lcd_misc & ATOM_PANEL_MISC_DUAL)
					args.v2.ucMisc |= PANEL_ENCODER_MISC_DUAL;
				if (dig->lcd_misc & ATOM_PANEL_MISC_SPATIAL) {
					args.v2.ucSpatial = PANEL_ENCODER_SPATIAL_DITHER_EN;
					if (dig->lcd_misc & ATOM_PANEL_MISC_888RGB)
						args.v2.ucSpatial |= PANEL_ENCODER_SPATIAL_DITHER_DEPTH;
				}
				if (dig->lcd_misc & ATOM_PANEL_MISC_TEMPORAL) {
					args.v2.ucTemporal = PANEL_ENCODER_TEMPORAL_DITHER_EN;
					if (dig->lcd_misc & ATOM_PANEL_MISC_888RGB)
						args.v2.ucTemporal |= PANEL_ENCODER_TEMPORAL_DITHER_DEPTH;
					if (((dig->lcd_misc >> ATOM_PANEL_MISC_GREY_LEVEL_SHIFT) & 0x3) == 2)
						args.v2.ucTemporal |= PANEL_ENCODER_TEMPORAL_LEVEL_4;
				}
			} else {
				if (dig->linkb)
					args.v2.ucMisc |= PANEL_ENCODER_MISC_TMDS_LINKB;
				if (radeon_dig_monitor_is_duallink(encoder, radeon_encoder->pixel_clock))
					args.v2.ucMisc |= PANEL_ENCODER_MISC_DUAL;
			}
			break;
		default:
			DRM_ERROR("Unknown table version %d, %d\n", frev, crev);
			break;
		}
		break;
	default:
		DRM_ERROR("Unknown table version %d, %d\n", frev, crev);
		break;
	}

	atom_execute_table(rdev->mode_info.atom_context, index, (uint32_t *)&args);
}