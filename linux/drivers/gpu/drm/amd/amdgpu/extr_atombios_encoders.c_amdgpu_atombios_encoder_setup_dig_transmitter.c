#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_17__ ;
typedef  struct TYPE_24__   TYPE_16__ ;
typedef  struct TYPE_23__   TYPE_15__ ;
typedef  struct TYPE_22__   TYPE_14__ ;
typedef  struct TYPE_21__   TYPE_13__ ;
typedef  struct TYPE_20__   TYPE_12__ ;
typedef  struct TYPE_19__   TYPE_11__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
struct TYPE_24__ {int ucAction; int ucLaneNum; int ucConnObjId; int ucDPLaneSet; int ucHPDSel; int ucDigEncoderSel; void* ucDigMode; void* ucPhyId; void* ulSymClock; } ;
struct TYPE_22__ {int ucPhyClkSrcId; int ucCoherentMode; int ucHPDSel; } ;
struct TYPE_23__ {int ucAction; int ucLaneNum; int ucConnObjId; int ucDigEncoderSel; int ucDPLaneSet; TYPE_14__ asConfig; void* ucDigMode; void* ucPhyId; void* usSymClock; } ;
struct TYPE_19__ {int ucLinkSel; int ucEncoderSel; int ucRefClkSource; int ucTransmitterSel; int fCoherentMode; int fDualLinkConnector; } ;
struct TYPE_18__ {int ucLaneSel; int ucLaneSet; } ;
struct TYPE_20__ {int ucAction; int ucLaneNum; TYPE_11__ acConfig; void* usPixelClock; TYPE_10__ asMode; void* usInitInfo; } ;
struct TYPE_33__ {int ucLinkSel; int ucEncoderSel; int ucRefClkSource; int ucTransmitterSel; int fCoherentMode; int fDualLinkConnector; } ;
struct TYPE_32__ {int ucLaneSel; int ucLaneSet; } ;
struct TYPE_34__ {int ucAction; int ucLaneNum; TYPE_8__ acConfig; void* usPixelClock; TYPE_7__ asMode; void* usInitInfo; } ;
struct TYPE_30__ {int ucEncoderSel; int ucLinkSel; int ucTransmitterSel; int fCoherentMode; int fDPConnector; int fDualLinkConnector; } ;
struct TYPE_29__ {int ucLaneSel; int ucLaneSet; } ;
struct TYPE_31__ {int ucAction; TYPE_5__ acConfig; void* usPixelClock; TYPE_4__ asMode; void* usInitInfo; } ;
struct TYPE_27__ {int ucLaneSel; int ucLaneSet; } ;
struct TYPE_28__ {int ucAction; int /*<<< orphan*/  ucConfig; void* usPixelClock; TYPE_2__ asMode; void* usInitInfo; } ;
union dig_transmitter_control {TYPE_16__ v6; TYPE_15__ v5; TYPE_12__ v4; TYPE_9__ v3; TYPE_6__ v2; TYPE_3__ v1; } ;
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct drm_encoder {scalar_t__ crtc; struct drm_device* dev; } ;
struct drm_device {struct amdgpu_device* dev_private; } ;
struct drm_connector {int dummy; } ;
struct amdgpu_encoder_atom_dig {int dig_encoder; int /*<<< orphan*/  linkb; int /*<<< orphan*/  coherent_mode; } ;
struct amdgpu_encoder {int encoder_id; int pixel_clock; int devices; struct amdgpu_encoder_atom_dig* enc_priv; } ;
struct TYPE_25__ {int /*<<< orphan*/  atom_context; } ;
struct TYPE_21__ {int /*<<< orphan*/  dp_extclk; } ;
struct amdgpu_device {int flags; TYPE_17__ mode_info; TYPE_13__ clock; } ;
struct amdgpu_crtc {int pll_id; } ;
struct amdgpu_connector_atom_dig {int dp_clock; int dp_lane_count; } ;
struct TYPE_26__ {int hpd; } ;
struct amdgpu_connector {int connector_object_id; TYPE_1__ hpd; struct amdgpu_connector_atom_dig* con_priv; } ;
typedef  int /*<<< orphan*/  args ;

/* Variables and functions */
 int AMDGPU_HPD_NONE ; 
 int AMD_IS_APU ; 
 int ATOM_DEVICE_DFP_SUPPORT ; 
 void* ATOM_PHY_ID_UNIPHYA ; 
 void* ATOM_PHY_ID_UNIPHYB ; 
 void* ATOM_PHY_ID_UNIPHYC ; 
 void* ATOM_PHY_ID_UNIPHYD ; 
 void* ATOM_PHY_ID_UNIPHYE ; 
 void* ATOM_PHY_ID_UNIPHYF ; 
 void* ATOM_PHY_ID_UNIPHYG ; 
 int ATOM_TRANSMITTER_ACTION_INIT ; 
 int ATOM_TRANSMITTER_ACTION_SETUP_VSEMPH ; 
 int /*<<< orphan*/  ATOM_TRANSMITTER_CONFIG_8LANE_LINK ; 
 int /*<<< orphan*/  ATOM_TRANSMITTER_CONFIG_CLKSRC_PPLL ; 
 int /*<<< orphan*/  ATOM_TRANSMITTER_CONFIG_COHERENT ; 
 int /*<<< orphan*/  ATOM_TRANSMITTER_CONFIG_DIG1_ENCODER ; 
 int /*<<< orphan*/  ATOM_TRANSMITTER_CONFIG_DIG2_ENCODER ; 
 int /*<<< orphan*/  ATOM_TRANSMITTER_CONFIG_LANE_0_3 ; 
 int /*<<< orphan*/  ATOM_TRANSMITTER_CONFIG_LANE_0_7 ; 
 int /*<<< orphan*/  ATOM_TRANSMITTER_CONFIG_LANE_12_15 ; 
 int /*<<< orphan*/  ATOM_TRANSMITTER_CONFIG_LANE_4_7 ; 
 int /*<<< orphan*/  ATOM_TRANSMITTER_CONFIG_LANE_8_11 ; 
 int /*<<< orphan*/  ATOM_TRANSMITTER_CONFIG_LANE_8_15 ; 
 int /*<<< orphan*/  ATOM_TRANSMITTER_CONFIG_LINKA ; 
 int /*<<< orphan*/  ATOM_TRANSMITTER_CONFIG_LINKB ; 
 int /*<<< orphan*/  COMMAND ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,int) ; 
 int /*<<< orphan*/  DVOOutputControl ; 
 scalar_t__ ENCODER_MODE_IS_DP (void*) ; 
#define  ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1 133 
#define  ENCODER_OBJECT_ID_INTERNAL_KLDSCP_LVTMA 132 
#define  ENCODER_OBJECT_ID_INTERNAL_UNIPHY 131 
#define  ENCODER_OBJECT_ID_INTERNAL_UNIPHY1 130 
#define  ENCODER_OBJECT_ID_INTERNAL_UNIPHY2 129 
#define  ENCODER_OBJECT_ID_INTERNAL_UNIPHY3 128 
 int ENCODER_REFCLK_SRC_DCPLL ; 
 void* ENCODER_REFCLK_SRC_EXTCLK ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LVTMATransmitterControl ; 
 int OBJECT_ID_MASK ; 
 int OBJECT_ID_SHIFT ; 
 int /*<<< orphan*/  UNIPHYTransmitterControl ; 
 int /*<<< orphan*/  amdgpu_atom_execute_table (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_atom_parse_cmd_header (int /*<<< orphan*/ ,int,int*,int*) ; 
 void* amdgpu_atombios_encoder_get_encoder_mode (struct drm_encoder*) ; 
 int /*<<< orphan*/  amdgpu_dig_monitor_is_duallink (struct drm_encoder*,int) ; 
 struct drm_connector* amdgpu_get_connector_for_encoder (struct drm_encoder*) ; 
 struct drm_connector* amdgpu_get_connector_for_encoder_init (struct drm_encoder*) ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  memset (union dig_transmitter_control*,int /*<<< orphan*/ ,int) ; 
 struct amdgpu_connector* to_amdgpu_connector (struct drm_connector*) ; 
 struct amdgpu_crtc* to_amdgpu_crtc (scalar_t__) ; 
 struct amdgpu_encoder* to_amdgpu_encoder (struct drm_encoder*) ; 

void
amdgpu_atombios_encoder_setup_dig_transmitter(struct drm_encoder *encoder, int action,
					      uint8_t lane_num, uint8_t lane_set)
{
	struct drm_device *dev = encoder->dev;
	struct amdgpu_device *adev = dev->dev_private;
	struct amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	struct amdgpu_encoder_atom_dig *dig = amdgpu_encoder->enc_priv;
	struct drm_connector *connector;
	union dig_transmitter_control args;
	int index = 0;
	uint8_t frev, crev;
	bool is_dp = false;
	int pll_id = 0;
	int dp_clock = 0;
	int dp_lane_count = 0;
	int connector_object_id = 0;
	int igp_lane_info = 0;
	int dig_encoder = dig->dig_encoder;
	int hpd_id = AMDGPU_HPD_NONE;

	if (action == ATOM_TRANSMITTER_ACTION_INIT) {
		connector = amdgpu_get_connector_for_encoder_init(encoder);
		/* just needed to avoid bailing in the encoder check.  the encoder
		 * isn't used for init
		 */
		dig_encoder = 0;
	} else
		connector = amdgpu_get_connector_for_encoder(encoder);

	if (connector) {
		struct amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);
		struct amdgpu_connector_atom_dig *dig_connector =
			amdgpu_connector->con_priv;

		hpd_id = amdgpu_connector->hpd.hpd;
		dp_clock = dig_connector->dp_clock;
		dp_lane_count = dig_connector->dp_lane_count;
		connector_object_id =
			(amdgpu_connector->connector_object_id & OBJECT_ID_MASK) >> OBJECT_ID_SHIFT;
	}

	if (encoder->crtc) {
		struct amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(encoder->crtc);
		pll_id = amdgpu_crtc->pll_id;
	}

	/* no dig encoder assigned */
	if (dig_encoder == -1)
		return;

	if (ENCODER_MODE_IS_DP(amdgpu_atombios_encoder_get_encoder_mode(encoder)))
		is_dp = true;

	memset(&args, 0, sizeof(args));

	switch (amdgpu_encoder->encoder_id) {
	case ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1:
		index = GetIndexIntoMasterTable(COMMAND, DVOOutputControl);
		break;
	case ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
	case ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
	case ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
	case ENCODER_OBJECT_ID_INTERNAL_UNIPHY3:
		index = GetIndexIntoMasterTable(COMMAND, UNIPHYTransmitterControl);
		break;
	case ENCODER_OBJECT_ID_INTERNAL_KLDSCP_LVTMA:
		index = GetIndexIntoMasterTable(COMMAND, LVTMATransmitterControl);
		break;
	}

	if (!amdgpu_atom_parse_cmd_header(adev->mode_info.atom_context, index, &frev, &crev))
		return;

	switch (frev) {
	case 1:
		switch (crev) {
		case 1:
			args.v1.ucAction = action;
			if (action == ATOM_TRANSMITTER_ACTION_INIT) {
				args.v1.usInitInfo = cpu_to_le16(connector_object_id);
			} else if (action == ATOM_TRANSMITTER_ACTION_SETUP_VSEMPH) {
				args.v1.asMode.ucLaneSel = lane_num;
				args.v1.asMode.ucLaneSet = lane_set;
			} else {
				if (is_dp)
					args.v1.usPixelClock = cpu_to_le16(dp_clock / 10);
				else if (amdgpu_dig_monitor_is_duallink(encoder, amdgpu_encoder->pixel_clock))
					args.v1.usPixelClock = cpu_to_le16((amdgpu_encoder->pixel_clock / 2) / 10);
				else
					args.v1.usPixelClock = cpu_to_le16(amdgpu_encoder->pixel_clock / 10);
			}

			args.v1.ucConfig = ATOM_TRANSMITTER_CONFIG_CLKSRC_PPLL;

			if (dig_encoder)
				args.v1.ucConfig |= ATOM_TRANSMITTER_CONFIG_DIG2_ENCODER;
			else
				args.v1.ucConfig |= ATOM_TRANSMITTER_CONFIG_DIG1_ENCODER;

			if ((adev->flags & AMD_IS_APU) &&
			    (amdgpu_encoder->encoder_id == ENCODER_OBJECT_ID_INTERNAL_UNIPHY)) {
				if (is_dp ||
				    !amdgpu_dig_monitor_is_duallink(encoder, amdgpu_encoder->pixel_clock)) {
					if (igp_lane_info & 0x1)
						args.v1.ucConfig |= ATOM_TRANSMITTER_CONFIG_LANE_0_3;
					else if (igp_lane_info & 0x2)
						args.v1.ucConfig |= ATOM_TRANSMITTER_CONFIG_LANE_4_7;
					else if (igp_lane_info & 0x4)
						args.v1.ucConfig |= ATOM_TRANSMITTER_CONFIG_LANE_8_11;
					else if (igp_lane_info & 0x8)
						args.v1.ucConfig |= ATOM_TRANSMITTER_CONFIG_LANE_12_15;
				} else {
					if (igp_lane_info & 0x3)
						args.v1.ucConfig |= ATOM_TRANSMITTER_CONFIG_LANE_0_7;
					else if (igp_lane_info & 0xc)
						args.v1.ucConfig |= ATOM_TRANSMITTER_CONFIG_LANE_8_15;
				}
			}

			if (dig->linkb)
				args.v1.ucConfig |= ATOM_TRANSMITTER_CONFIG_LINKB;
			else
				args.v1.ucConfig |= ATOM_TRANSMITTER_CONFIG_LINKA;

			if (is_dp)
				args.v1.ucConfig |= ATOM_TRANSMITTER_CONFIG_COHERENT;
			else if (amdgpu_encoder->devices & (ATOM_DEVICE_DFP_SUPPORT)) {
				if (dig->coherent_mode)
					args.v1.ucConfig |= ATOM_TRANSMITTER_CONFIG_COHERENT;
				if (amdgpu_dig_monitor_is_duallink(encoder, amdgpu_encoder->pixel_clock))
					args.v1.ucConfig |= ATOM_TRANSMITTER_CONFIG_8LANE_LINK;
			}
			break;
		case 2:
			args.v2.ucAction = action;
			if (action == ATOM_TRANSMITTER_ACTION_INIT) {
				args.v2.usInitInfo = cpu_to_le16(connector_object_id);
			} else if (action == ATOM_TRANSMITTER_ACTION_SETUP_VSEMPH) {
				args.v2.asMode.ucLaneSel = lane_num;
				args.v2.asMode.ucLaneSet = lane_set;
			} else {
				if (is_dp)
					args.v2.usPixelClock = cpu_to_le16(dp_clock / 10);
				else if (amdgpu_dig_monitor_is_duallink(encoder, amdgpu_encoder->pixel_clock))
					args.v2.usPixelClock = cpu_to_le16((amdgpu_encoder->pixel_clock / 2) / 10);
				else
					args.v2.usPixelClock = cpu_to_le16(amdgpu_encoder->pixel_clock / 10);
			}

			args.v2.acConfig.ucEncoderSel = dig_encoder;
			if (dig->linkb)
				args.v2.acConfig.ucLinkSel = 1;

			switch (amdgpu_encoder->encoder_id) {
			case ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
				args.v2.acConfig.ucTransmitterSel = 0;
				break;
			case ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
				args.v2.acConfig.ucTransmitterSel = 1;
				break;
			case ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
				args.v2.acConfig.ucTransmitterSel = 2;
				break;
			}

			if (is_dp) {
				args.v2.acConfig.fCoherentMode = 1;
				args.v2.acConfig.fDPConnector = 1;
			} else if (amdgpu_encoder->devices & (ATOM_DEVICE_DFP_SUPPORT)) {
				if (dig->coherent_mode)
					args.v2.acConfig.fCoherentMode = 1;
				if (amdgpu_dig_monitor_is_duallink(encoder, amdgpu_encoder->pixel_clock))
					args.v2.acConfig.fDualLinkConnector = 1;
			}
			break;
		case 3:
			args.v3.ucAction = action;
			if (action == ATOM_TRANSMITTER_ACTION_INIT) {
				args.v3.usInitInfo = cpu_to_le16(connector_object_id);
			} else if (action == ATOM_TRANSMITTER_ACTION_SETUP_VSEMPH) {
				args.v3.asMode.ucLaneSel = lane_num;
				args.v3.asMode.ucLaneSet = lane_set;
			} else {
				if (is_dp)
					args.v3.usPixelClock = cpu_to_le16(dp_clock / 10);
				else if (amdgpu_dig_monitor_is_duallink(encoder, amdgpu_encoder->pixel_clock))
					args.v3.usPixelClock = cpu_to_le16((amdgpu_encoder->pixel_clock / 2) / 10);
				else
					args.v3.usPixelClock = cpu_to_le16(amdgpu_encoder->pixel_clock / 10);
			}

			if (is_dp)
				args.v3.ucLaneNum = dp_lane_count;
			else if (amdgpu_dig_monitor_is_duallink(encoder, amdgpu_encoder->pixel_clock))
				args.v3.ucLaneNum = 8;
			else
				args.v3.ucLaneNum = 4;

			if (dig->linkb)
				args.v3.acConfig.ucLinkSel = 1;
			if (dig_encoder & 1)
				args.v3.acConfig.ucEncoderSel = 1;

			/* Select the PLL for the PHY
			 * DP PHY should be clocked from external src if there is
			 * one.
			 */
			/* On DCE4, if there is an external clock, it generates the DP ref clock */
			if (is_dp && adev->clock.dp_extclk)
				args.v3.acConfig.ucRefClkSource = 2; /* external src */
			else
				args.v3.acConfig.ucRefClkSource = pll_id;

			switch (amdgpu_encoder->encoder_id) {
			case ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
				args.v3.acConfig.ucTransmitterSel = 0;
				break;
			case ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
				args.v3.acConfig.ucTransmitterSel = 1;
				break;
			case ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
				args.v3.acConfig.ucTransmitterSel = 2;
				break;
			}

			if (is_dp)
				args.v3.acConfig.fCoherentMode = 1; /* DP requires coherent */
			else if (amdgpu_encoder->devices & (ATOM_DEVICE_DFP_SUPPORT)) {
				if (dig->coherent_mode)
					args.v3.acConfig.fCoherentMode = 1;
				if (amdgpu_dig_monitor_is_duallink(encoder, amdgpu_encoder->pixel_clock))
					args.v3.acConfig.fDualLinkConnector = 1;
			}
			break;
		case 4:
			args.v4.ucAction = action;
			if (action == ATOM_TRANSMITTER_ACTION_INIT) {
				args.v4.usInitInfo = cpu_to_le16(connector_object_id);
			} else if (action == ATOM_TRANSMITTER_ACTION_SETUP_VSEMPH) {
				args.v4.asMode.ucLaneSel = lane_num;
				args.v4.asMode.ucLaneSet = lane_set;
			} else {
				if (is_dp)
					args.v4.usPixelClock = cpu_to_le16(dp_clock / 10);
				else if (amdgpu_dig_monitor_is_duallink(encoder, amdgpu_encoder->pixel_clock))
					args.v4.usPixelClock = cpu_to_le16((amdgpu_encoder->pixel_clock / 2) / 10);
				else
					args.v4.usPixelClock = cpu_to_le16(amdgpu_encoder->pixel_clock / 10);
			}

			if (is_dp)
				args.v4.ucLaneNum = dp_lane_count;
			else if (amdgpu_dig_monitor_is_duallink(encoder, amdgpu_encoder->pixel_clock))
				args.v4.ucLaneNum = 8;
			else
				args.v4.ucLaneNum = 4;

			if (dig->linkb)
				args.v4.acConfig.ucLinkSel = 1;
			if (dig_encoder & 1)
				args.v4.acConfig.ucEncoderSel = 1;

			/* Select the PLL for the PHY
			 * DP PHY should be clocked from external src if there is
			 * one.
			 */
			/* On DCE5 DCPLL usually generates the DP ref clock */
			if (is_dp) {
				if (adev->clock.dp_extclk)
					args.v4.acConfig.ucRefClkSource = ENCODER_REFCLK_SRC_EXTCLK;
				else
					args.v4.acConfig.ucRefClkSource = ENCODER_REFCLK_SRC_DCPLL;
			} else
				args.v4.acConfig.ucRefClkSource = pll_id;

			switch (amdgpu_encoder->encoder_id) {
			case ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
				args.v4.acConfig.ucTransmitterSel = 0;
				break;
			case ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
				args.v4.acConfig.ucTransmitterSel = 1;
				break;
			case ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
				args.v4.acConfig.ucTransmitterSel = 2;
				break;
			}

			if (is_dp)
				args.v4.acConfig.fCoherentMode = 1; /* DP requires coherent */
			else if (amdgpu_encoder->devices & (ATOM_DEVICE_DFP_SUPPORT)) {
				if (dig->coherent_mode)
					args.v4.acConfig.fCoherentMode = 1;
				if (amdgpu_dig_monitor_is_duallink(encoder, amdgpu_encoder->pixel_clock))
					args.v4.acConfig.fDualLinkConnector = 1;
			}
			break;
		case 5:
			args.v5.ucAction = action;
			if (is_dp)
				args.v5.usSymClock = cpu_to_le16(dp_clock / 10);
			else
				args.v5.usSymClock = cpu_to_le16(amdgpu_encoder->pixel_clock / 10);

			switch (amdgpu_encoder->encoder_id) {
			case ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
				if (dig->linkb)
					args.v5.ucPhyId = ATOM_PHY_ID_UNIPHYB;
				else
					args.v5.ucPhyId = ATOM_PHY_ID_UNIPHYA;
				break;
			case ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
				if (dig->linkb)
					args.v5.ucPhyId = ATOM_PHY_ID_UNIPHYD;
				else
					args.v5.ucPhyId = ATOM_PHY_ID_UNIPHYC;
				break;
			case ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
				if (dig->linkb)
					args.v5.ucPhyId = ATOM_PHY_ID_UNIPHYF;
				else
					args.v5.ucPhyId = ATOM_PHY_ID_UNIPHYE;
				break;
			case ENCODER_OBJECT_ID_INTERNAL_UNIPHY3:
				args.v5.ucPhyId = ATOM_PHY_ID_UNIPHYG;
				break;
			}
			if (is_dp)
				args.v5.ucLaneNum = dp_lane_count;
			else if (amdgpu_dig_monitor_is_duallink(encoder, amdgpu_encoder->pixel_clock))
				args.v5.ucLaneNum = 8;
			else
				args.v5.ucLaneNum = 4;
			args.v5.ucConnObjId = connector_object_id;
			args.v5.ucDigMode = amdgpu_atombios_encoder_get_encoder_mode(encoder);

			if (is_dp && adev->clock.dp_extclk)
				args.v5.asConfig.ucPhyClkSrcId = ENCODER_REFCLK_SRC_EXTCLK;
			else
				args.v5.asConfig.ucPhyClkSrcId = pll_id;

			if (is_dp)
				args.v5.asConfig.ucCoherentMode = 1; /* DP requires coherent */
			else if (amdgpu_encoder->devices & (ATOM_DEVICE_DFP_SUPPORT)) {
				if (dig->coherent_mode)
					args.v5.asConfig.ucCoherentMode = 1;
			}
			if (hpd_id == AMDGPU_HPD_NONE)
				args.v5.asConfig.ucHPDSel = 0;
			else
				args.v5.asConfig.ucHPDSel = hpd_id + 1;
			args.v5.ucDigEncoderSel = 1 << dig_encoder;
			args.v5.ucDPLaneSet = lane_set;
			break;
		case 6:
			args.v6.ucAction = action;
			if (is_dp)
				args.v6.ulSymClock = cpu_to_le32(dp_clock / 10);
			else
				args.v6.ulSymClock = cpu_to_le32(amdgpu_encoder->pixel_clock / 10);

			switch (amdgpu_encoder->encoder_id) {
			case ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
				if (dig->linkb)
					args.v6.ucPhyId = ATOM_PHY_ID_UNIPHYB;
				else
					args.v6.ucPhyId = ATOM_PHY_ID_UNIPHYA;
				break;
			case ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
				if (dig->linkb)
					args.v6.ucPhyId = ATOM_PHY_ID_UNIPHYD;
				else
					args.v6.ucPhyId = ATOM_PHY_ID_UNIPHYC;
				break;
			case ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
				if (dig->linkb)
					args.v6.ucPhyId = ATOM_PHY_ID_UNIPHYF;
				else
					args.v6.ucPhyId = ATOM_PHY_ID_UNIPHYE;
				break;
			case ENCODER_OBJECT_ID_INTERNAL_UNIPHY3:
				args.v6.ucPhyId = ATOM_PHY_ID_UNIPHYG;
				break;
			}
			if (is_dp)
				args.v6.ucLaneNum = dp_lane_count;
			else if (amdgpu_dig_monitor_is_duallink(encoder, amdgpu_encoder->pixel_clock))
				args.v6.ucLaneNum = 8;
			else
				args.v6.ucLaneNum = 4;
			args.v6.ucConnObjId = connector_object_id;
			if (action == ATOM_TRANSMITTER_ACTION_SETUP_VSEMPH)
				args.v6.ucDPLaneSet = lane_set;
			else
				args.v6.ucDigMode = amdgpu_atombios_encoder_get_encoder_mode(encoder);

			if (hpd_id == AMDGPU_HPD_NONE)
				args.v6.ucHPDSel = 0;
			else
				args.v6.ucHPDSel = hpd_id + 1;
			args.v6.ucDigEncoderSel = 1 << dig_encoder;
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