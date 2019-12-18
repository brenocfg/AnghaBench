#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int ucDigSel; } ;
struct TYPE_14__ {int ucAction; int ucPanelMode; int ucLaneNum; int ucHPD_ID; void* ucBitPerColor; TYPE_1__ acConfig; void* ucEncoderMode; void* usPixelClock; } ;
struct TYPE_11__ {int ucAction; int ucLaneNum; int /*<<< orphan*/  ucConfig; void* ucEncoderMode; void* usPixelClock; } ;
struct TYPE_12__ {int ucDigSel; } ;
struct TYPE_13__ {int ucPanelMode; int ucAction; int ucLaneNum; void* ucBitPerColor; TYPE_5__ acConfig; void* ucEncoderMode; void* usPixelClock; } ;
union dig_encoder_control {TYPE_7__ v4; TYPE_4__ v1; TYPE_6__ v3; } ;
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct radeon_encoder_atom_dig {int dig_encoder; int /*<<< orphan*/  linkb; } ;
struct radeon_encoder {int pixel_clock; int /*<<< orphan*/  encoder_id; struct radeon_encoder_atom_dig* enc_priv; } ;
struct TYPE_10__ {int /*<<< orphan*/  atom_context; } ;
struct radeon_device {TYPE_3__ mode_info; } ;
struct radeon_connector_atom_dig {int dp_clock; int dp_lane_count; } ;
struct TYPE_9__ {int hpd; } ;
struct radeon_connector {TYPE_2__ hpd; struct radeon_connector_atom_dig* con_priv; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct drm_connector {int dummy; } ;
typedef  int /*<<< orphan*/  args ;

/* Variables and functions */
 scalar_t__ ASIC_IS_DCE4 (struct radeon_device*) ; 
 int ATOM_ENCODER_CMD_SETUP_PANEL_MODE ; 
 int /*<<< orphan*/  ATOM_ENCODER_CONFIG_DPLINKRATE_2_70GHZ ; 
 int /*<<< orphan*/  ATOM_ENCODER_CONFIG_LINKA ; 
 int /*<<< orphan*/  ATOM_ENCODER_CONFIG_LINKB ; 
 int /*<<< orphan*/  ATOM_ENCODER_CONFIG_V2_TRANSMITTER1 ; 
 int /*<<< orphan*/  ATOM_ENCODER_CONFIG_V2_TRANSMITTER2 ; 
 int /*<<< orphan*/  ATOM_ENCODER_CONFIG_V2_TRANSMITTER3 ; 
 int /*<<< orphan*/  ATOM_ENCODER_CONFIG_V3_DPLINKRATE_2_70GHZ ; 
 int /*<<< orphan*/  ATOM_ENCODER_CONFIG_V4_DPLINKRATE_1_62GHZ ; 
 int /*<<< orphan*/  ATOM_ENCODER_CONFIG_V4_DPLINKRATE_2_70GHZ ; 
 int /*<<< orphan*/  ATOM_ENCODER_CONFIG_V4_DPLINKRATE_3_24GHZ ; 
 int /*<<< orphan*/  ATOM_ENCODER_CONFIG_V4_DPLINKRATE_5_40GHZ ; 
 int /*<<< orphan*/  COMMAND ; 
 int /*<<< orphan*/  DIG1EncoderControl ; 
 int /*<<< orphan*/  DIG2EncoderControl ; 
 int /*<<< orphan*/  DIGxEncoderControl ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,int) ; 
 int /*<<< orphan*/  ENCODER_MODE_IS_DP (void*) ; 
#define  ENCODER_OBJECT_ID_INTERNAL_KLDSCP_LVTMA 131 
#define  ENCODER_OBJECT_ID_INTERNAL_UNIPHY 130 
#define  ENCODER_OBJECT_ID_INTERNAL_UNIPHY1 129 
#define  ENCODER_OBJECT_ID_INTERNAL_UNIPHY2 128 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RADEON_HPD_NONE ; 
 int /*<<< orphan*/  atom_execute_table (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atom_parse_cmd_header (int /*<<< orphan*/ ,int,int*,int*) ; 
 void* atombios_get_encoder_mode (struct drm_encoder*) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  memset (union dig_encoder_control*,int /*<<< orphan*/ ,int) ; 
 void* radeon_atom_get_bpc (struct drm_encoder*) ; 
 int /*<<< orphan*/  radeon_dig_monitor_is_duallink (struct drm_encoder*,int) ; 
 struct drm_connector* radeon_get_connector_for_encoder (struct drm_encoder*) ; 
 struct radeon_connector* to_radeon_connector (struct drm_connector*) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

void
atombios_dig_encoder_setup2(struct drm_encoder *encoder, int action, int panel_mode, int enc_override)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	struct radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;
	struct drm_connector *connector = radeon_get_connector_for_encoder(encoder);
	union dig_encoder_control args;
	int index = 0;
	uint8_t frev, crev;
	int dp_clock = 0;
	int dp_lane_count = 0;
	int hpd_id = RADEON_HPD_NONE;

	if (connector) {
		struct radeon_connector *radeon_connector = to_radeon_connector(connector);
		struct radeon_connector_atom_dig *dig_connector =
			radeon_connector->con_priv;

		dp_clock = dig_connector->dp_clock;
		dp_lane_count = dig_connector->dp_lane_count;
		hpd_id = radeon_connector->hpd.hpd;
	}

	/* no dig encoder assigned */
	if (dig->dig_encoder == -1)
		return;

	memset(&args, 0, sizeof(args));

	if (ASIC_IS_DCE4(rdev))
		index = GetIndexIntoMasterTable(COMMAND, DIGxEncoderControl);
	else {
		if (dig->dig_encoder)
			index = GetIndexIntoMasterTable(COMMAND, DIG2EncoderControl);
		else
			index = GetIndexIntoMasterTable(COMMAND, DIG1EncoderControl);
	}

	if (!atom_parse_cmd_header(rdev->mode_info.atom_context, index, &frev, &crev))
		return;

	switch (frev) {
	case 1:
		switch (crev) {
		case 1:
			args.v1.ucAction = action;
			args.v1.usPixelClock = cpu_to_le16(radeon_encoder->pixel_clock / 10);
			if (action == ATOM_ENCODER_CMD_SETUP_PANEL_MODE)
				args.v3.ucPanelMode = panel_mode;
			else
				args.v1.ucEncoderMode = atombios_get_encoder_mode(encoder);

			if (ENCODER_MODE_IS_DP(args.v1.ucEncoderMode))
				args.v1.ucLaneNum = dp_lane_count;
			else if (radeon_dig_monitor_is_duallink(encoder, radeon_encoder->pixel_clock))
				args.v1.ucLaneNum = 8;
			else
				args.v1.ucLaneNum = 4;

			switch (radeon_encoder->encoder_id) {
			case ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
				args.v1.ucConfig = ATOM_ENCODER_CONFIG_V2_TRANSMITTER1;
				break;
			case ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
			case ENCODER_OBJECT_ID_INTERNAL_KLDSCP_LVTMA:
				args.v1.ucConfig = ATOM_ENCODER_CONFIG_V2_TRANSMITTER2;
				break;
			case ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
				args.v1.ucConfig = ATOM_ENCODER_CONFIG_V2_TRANSMITTER3;
				break;
			}
			if (dig->linkb)
				args.v1.ucConfig |= ATOM_ENCODER_CONFIG_LINKB;
			else
				args.v1.ucConfig |= ATOM_ENCODER_CONFIG_LINKA;

			if (ENCODER_MODE_IS_DP(args.v1.ucEncoderMode) && (dp_clock == 270000))
				args.v1.ucConfig |= ATOM_ENCODER_CONFIG_DPLINKRATE_2_70GHZ;

			break;
		case 2:
		case 3:
			args.v3.ucAction = action;
			args.v3.usPixelClock = cpu_to_le16(radeon_encoder->pixel_clock / 10);
			if (action == ATOM_ENCODER_CMD_SETUP_PANEL_MODE)
				args.v3.ucPanelMode = panel_mode;
			else
				args.v3.ucEncoderMode = atombios_get_encoder_mode(encoder);

			if (ENCODER_MODE_IS_DP(args.v3.ucEncoderMode))
				args.v3.ucLaneNum = dp_lane_count;
			else if (radeon_dig_monitor_is_duallink(encoder, radeon_encoder->pixel_clock))
				args.v3.ucLaneNum = 8;
			else
				args.v3.ucLaneNum = 4;

			if (ENCODER_MODE_IS_DP(args.v3.ucEncoderMode) && (dp_clock == 270000))
				args.v1.ucConfig |= ATOM_ENCODER_CONFIG_V3_DPLINKRATE_2_70GHZ;
			if (enc_override != -1)
				args.v3.acConfig.ucDigSel = enc_override;
			else
				args.v3.acConfig.ucDigSel = dig->dig_encoder;
			args.v3.ucBitPerColor = radeon_atom_get_bpc(encoder);
			break;
		case 4:
			args.v4.ucAction = action;
			args.v4.usPixelClock = cpu_to_le16(radeon_encoder->pixel_clock / 10);
			if (action == ATOM_ENCODER_CMD_SETUP_PANEL_MODE)
				args.v4.ucPanelMode = panel_mode;
			else
				args.v4.ucEncoderMode = atombios_get_encoder_mode(encoder);

			if (ENCODER_MODE_IS_DP(args.v4.ucEncoderMode))
				args.v4.ucLaneNum = dp_lane_count;
			else if (radeon_dig_monitor_is_duallink(encoder, radeon_encoder->pixel_clock))
				args.v4.ucLaneNum = 8;
			else
				args.v4.ucLaneNum = 4;

			if (ENCODER_MODE_IS_DP(args.v4.ucEncoderMode)) {
				if (dp_clock == 540000)
					args.v1.ucConfig |= ATOM_ENCODER_CONFIG_V4_DPLINKRATE_5_40GHZ;
				else if (dp_clock == 324000)
					args.v1.ucConfig |= ATOM_ENCODER_CONFIG_V4_DPLINKRATE_3_24GHZ;
				else if (dp_clock == 270000)
					args.v1.ucConfig |= ATOM_ENCODER_CONFIG_V4_DPLINKRATE_2_70GHZ;
				else
					args.v1.ucConfig |= ATOM_ENCODER_CONFIG_V4_DPLINKRATE_1_62GHZ;
			}

			if (enc_override != -1)
				args.v4.acConfig.ucDigSel = enc_override;
			else
				args.v4.acConfig.ucDigSel = dig->dig_encoder;
			args.v4.ucBitPerColor = radeon_atom_get_bpc(encoder);
			if (hpd_id == RADEON_HPD_NONE)
				args.v4.ucHPD_ID = 0;
			else
				args.v4.ucHPD_ID = hpd_id + 1;
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