#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_19__ {int ucAction; int ucDigId; } ;
struct TYPE_18__ {int ucAction; int ucDigId; int ucLaneNum; int ucLinkRateIn270Mhz; void* ucBitPerColor; int /*<<< orphan*/  ulPixelClock; void* ucDigMode; } ;
struct TYPE_17__ {int ucAction; int ucPanelMode; int ucDigId; } ;
struct TYPE_20__ {TYPE_6__ asCmdParam; TYPE_5__ asStreamParam; TYPE_4__ asDPPanelModeParam; } ;
struct TYPE_15__ {int ucDigSel; } ;
struct TYPE_16__ {int ucAction; int ucPanelMode; int ucLaneNum; int ucHPD_ID; void* ucBitPerColor; TYPE_2__ acConfig; void* ucEncoderMode; void* usPixelClock; } ;
struct TYPE_12__ {int ucAction; int ucLaneNum; int /*<<< orphan*/  ucConfig; void* ucEncoderMode; void* usPixelClock; } ;
struct TYPE_14__ {int ucDigSel; } ;
struct TYPE_13__ {int ucPanelMode; int ucAction; int ucLaneNum; void* ucBitPerColor; TYPE_1__ acConfig; void* ucEncoderMode; void* usPixelClock; } ;
union dig_encoder_control {TYPE_7__ v5; TYPE_3__ v4; TYPE_10__ v1; TYPE_11__ v3; } ;
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {struct amdgpu_device* dev_private; } ;
struct drm_connector {int dummy; } ;
struct amdgpu_encoder_atom_dig {int dig_encoder; int /*<<< orphan*/  linkb; } ;
struct amdgpu_encoder {int pixel_clock; int /*<<< orphan*/  encoder_id; struct amdgpu_encoder_atom_dig* enc_priv; } ;
struct TYPE_22__ {int /*<<< orphan*/  atom_context; } ;
struct amdgpu_device {TYPE_9__ mode_info; } ;
struct amdgpu_connector_atom_dig {int dp_clock; int dp_lane_count; } ;
struct TYPE_21__ {int hpd; } ;
struct amdgpu_connector {TYPE_8__ hpd; struct amdgpu_connector_atom_dig* con_priv; } ;
typedef  int /*<<< orphan*/  args ;

/* Variables and functions */
 int AMDGPU_HPD_NONE ; 
#define  ATOM_ENCODER_CMD_DP_LINK_TRAINING_COMPLETE 141 
#define  ATOM_ENCODER_CMD_DP_LINK_TRAINING_PATTERN1 140 
#define  ATOM_ENCODER_CMD_DP_LINK_TRAINING_PATTERN2 139 
#define  ATOM_ENCODER_CMD_DP_LINK_TRAINING_PATTERN3 138 
#define  ATOM_ENCODER_CMD_DP_LINK_TRAINING_PATTERN4 137 
#define  ATOM_ENCODER_CMD_DP_LINK_TRAINING_START 136 
#define  ATOM_ENCODER_CMD_DP_VIDEO_OFF 135 
#define  ATOM_ENCODER_CMD_DP_VIDEO_ON 134 
#define  ATOM_ENCODER_CMD_SETUP_PANEL_MODE 133 
#define  ATOM_ENCODER_CMD_STREAM_SETUP 132 
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
 int /*<<< orphan*/  DIGxEncoderControl ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,...) ; 
 int /*<<< orphan*/  ENCODER_MODE_IS_DP (void*) ; 
#define  ENCODER_OBJECT_ID_INTERNAL_KLDSCP_LVTMA 131 
#define  ENCODER_OBJECT_ID_INTERNAL_UNIPHY 130 
#define  ENCODER_OBJECT_ID_INTERNAL_UNIPHY1 129 
#define  ENCODER_OBJECT_ID_INTERNAL_UNIPHY2 128 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_atom_execute_table (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_atom_parse_cmd_header (int /*<<< orphan*/ ,int,int*,int*) ; 
 void* amdgpu_atombios_encoder_get_bpc (struct drm_encoder*) ; 
 void* amdgpu_atombios_encoder_get_encoder_mode (struct drm_encoder*) ; 
 int /*<<< orphan*/  amdgpu_dig_monitor_is_duallink (struct drm_encoder*,int) ; 
 struct drm_connector* amdgpu_get_connector_for_encoder (struct drm_encoder*) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  memset (union dig_encoder_control*,int /*<<< orphan*/ ,int) ; 
 struct amdgpu_connector* to_amdgpu_connector (struct drm_connector*) ; 
 struct amdgpu_encoder* to_amdgpu_encoder (struct drm_encoder*) ; 

void
amdgpu_atombios_encoder_setup_dig_encoder(struct drm_encoder *encoder,
				   int action, int panel_mode)
{
	struct drm_device *dev = encoder->dev;
	struct amdgpu_device *adev = dev->dev_private;
	struct amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	struct amdgpu_encoder_atom_dig *dig = amdgpu_encoder->enc_priv;
	struct drm_connector *connector = amdgpu_get_connector_for_encoder(encoder);
	union dig_encoder_control args;
	int index = GetIndexIntoMasterTable(COMMAND, DIGxEncoderControl);
	uint8_t frev, crev;
	int dp_clock = 0;
	int dp_lane_count = 0;
	int hpd_id = AMDGPU_HPD_NONE;

	if (connector) {
		struct amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);
		struct amdgpu_connector_atom_dig *dig_connector =
			amdgpu_connector->con_priv;

		dp_clock = dig_connector->dp_clock;
		dp_lane_count = dig_connector->dp_lane_count;
		hpd_id = amdgpu_connector->hpd.hpd;
	}

	/* no dig encoder assigned */
	if (dig->dig_encoder == -1)
		return;

	memset(&args, 0, sizeof(args));

	if (!amdgpu_atom_parse_cmd_header(adev->mode_info.atom_context, index, &frev, &crev))
		return;

	switch (frev) {
	case 1:
		switch (crev) {
		case 1:
			args.v1.ucAction = action;
			args.v1.usPixelClock = cpu_to_le16(amdgpu_encoder->pixel_clock / 10);
			if (action == ATOM_ENCODER_CMD_SETUP_PANEL_MODE)
				args.v3.ucPanelMode = panel_mode;
			else
				args.v1.ucEncoderMode = amdgpu_atombios_encoder_get_encoder_mode(encoder);

			if (ENCODER_MODE_IS_DP(args.v1.ucEncoderMode))
				args.v1.ucLaneNum = dp_lane_count;
			else if (amdgpu_dig_monitor_is_duallink(encoder, amdgpu_encoder->pixel_clock))
				args.v1.ucLaneNum = 8;
			else
				args.v1.ucLaneNum = 4;

			if (ENCODER_MODE_IS_DP(args.v1.ucEncoderMode) && (dp_clock == 270000))
				args.v1.ucConfig |= ATOM_ENCODER_CONFIG_DPLINKRATE_2_70GHZ;
			switch (amdgpu_encoder->encoder_id) {
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
			break;
		case 2:
		case 3:
			args.v3.ucAction = action;
			args.v3.usPixelClock = cpu_to_le16(amdgpu_encoder->pixel_clock / 10);
			if (action == ATOM_ENCODER_CMD_SETUP_PANEL_MODE)
				args.v3.ucPanelMode = panel_mode;
			else
				args.v3.ucEncoderMode = amdgpu_atombios_encoder_get_encoder_mode(encoder);

			if (ENCODER_MODE_IS_DP(args.v3.ucEncoderMode))
				args.v3.ucLaneNum = dp_lane_count;
			else if (amdgpu_dig_monitor_is_duallink(encoder, amdgpu_encoder->pixel_clock))
				args.v3.ucLaneNum = 8;
			else
				args.v3.ucLaneNum = 4;

			if (ENCODER_MODE_IS_DP(args.v3.ucEncoderMode) && (dp_clock == 270000))
				args.v1.ucConfig |= ATOM_ENCODER_CONFIG_V3_DPLINKRATE_2_70GHZ;
			args.v3.acConfig.ucDigSel = dig->dig_encoder;
			args.v3.ucBitPerColor = amdgpu_atombios_encoder_get_bpc(encoder);
			break;
		case 4:
			args.v4.ucAction = action;
			args.v4.usPixelClock = cpu_to_le16(amdgpu_encoder->pixel_clock / 10);
			if (action == ATOM_ENCODER_CMD_SETUP_PANEL_MODE)
				args.v4.ucPanelMode = panel_mode;
			else
				args.v4.ucEncoderMode = amdgpu_atombios_encoder_get_encoder_mode(encoder);

			if (ENCODER_MODE_IS_DP(args.v4.ucEncoderMode))
				args.v4.ucLaneNum = dp_lane_count;
			else if (amdgpu_dig_monitor_is_duallink(encoder, amdgpu_encoder->pixel_clock))
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
			args.v4.acConfig.ucDigSel = dig->dig_encoder;
			args.v4.ucBitPerColor = amdgpu_atombios_encoder_get_bpc(encoder);
			if (hpd_id == AMDGPU_HPD_NONE)
				args.v4.ucHPD_ID = 0;
			else
				args.v4.ucHPD_ID = hpd_id + 1;
			break;
		case 5:
			switch (action) {
			case ATOM_ENCODER_CMD_SETUP_PANEL_MODE:
				args.v5.asDPPanelModeParam.ucAction = action;
				args.v5.asDPPanelModeParam.ucPanelMode = panel_mode;
				args.v5.asDPPanelModeParam.ucDigId = dig->dig_encoder;
				break;
			case ATOM_ENCODER_CMD_STREAM_SETUP:
				args.v5.asStreamParam.ucAction = action;
				args.v5.asStreamParam.ucDigId = dig->dig_encoder;
				args.v5.asStreamParam.ucDigMode =
					amdgpu_atombios_encoder_get_encoder_mode(encoder);
				if (ENCODER_MODE_IS_DP(args.v5.asStreamParam.ucDigMode))
					args.v5.asStreamParam.ucLaneNum = dp_lane_count;
				else if (amdgpu_dig_monitor_is_duallink(encoder,
									amdgpu_encoder->pixel_clock))
					args.v5.asStreamParam.ucLaneNum = 8;
				else
					args.v5.asStreamParam.ucLaneNum = 4;
				args.v5.asStreamParam.ulPixelClock =
					cpu_to_le32(amdgpu_encoder->pixel_clock / 10);
				args.v5.asStreamParam.ucBitPerColor =
					amdgpu_atombios_encoder_get_bpc(encoder);
				args.v5.asStreamParam.ucLinkRateIn270Mhz = dp_clock / 27000;
				break;
			case ATOM_ENCODER_CMD_DP_LINK_TRAINING_START:
			case ATOM_ENCODER_CMD_DP_LINK_TRAINING_PATTERN1:
			case ATOM_ENCODER_CMD_DP_LINK_TRAINING_PATTERN2:
			case ATOM_ENCODER_CMD_DP_LINK_TRAINING_PATTERN3:
			case ATOM_ENCODER_CMD_DP_LINK_TRAINING_PATTERN4:
			case ATOM_ENCODER_CMD_DP_LINK_TRAINING_COMPLETE:
			case ATOM_ENCODER_CMD_DP_VIDEO_OFF:
			case ATOM_ENCODER_CMD_DP_VIDEO_ON:
				args.v5.asCmdParam.ucAction = action;
				args.v5.asCmdParam.ucDigId = dig->dig_encoder;
				break;
			default:
				DRM_ERROR("Unsupported action 0x%x\n", action);
				break;
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

	amdgpu_atom_execute_table(adev->mode_info.atom_context, index, (uint32_t *)&args);

}