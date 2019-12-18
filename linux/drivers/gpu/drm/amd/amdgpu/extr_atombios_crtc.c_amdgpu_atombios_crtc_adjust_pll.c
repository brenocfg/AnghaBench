#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  ucPostDiv; scalar_t__ ucRefDiv; int /*<<< orphan*/  ulDispPllFreq; } ;
struct TYPE_10__ {scalar_t__ ucTransmitterID; int ucEncodeMode; scalar_t__ ucExtTransmitterID; int /*<<< orphan*/  ucDispPllConfig; void* usPixelClock; } ;
struct TYPE_11__ {TYPE_1__ sOutput; TYPE_4__ sInput; } ;
struct TYPE_8__ {scalar_t__ ucTransmitterID; int ucEncodeMode; void* usPixelClock; int /*<<< orphan*/  ucConfig; } ;
union adjust_pixel_clock {TYPE_5__ v3; TYPE_2__ v1; } ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u8 ;
typedef  int u32 ;
struct drm_encoder {int dummy; } ;
struct drm_display_mode {int clock; } ;
struct drm_device {struct amdgpu_device* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;
struct drm_connector {int dummy; } ;
struct amdgpu_encoder_atom_dig {int /*<<< orphan*/  coherent_mode; } ;
struct amdgpu_encoder {int devices; scalar_t__ encoder_id; int active_device; struct amdgpu_encoder_atom_dig* enc_priv; } ;
struct TYPE_12__ {int /*<<< orphan*/  atom_context; } ;
struct amdgpu_device {TYPE_6__ mode_info; } ;
struct TYPE_9__ {int /*<<< orphan*/  percentage; scalar_t__ refdiv; } ;
struct amdgpu_crtc {int bpc; int /*<<< orphan*/  pll_post_div; int /*<<< orphan*/  pll_flags; scalar_t__ pll_reference_div; TYPE_3__ ss; scalar_t__ ss_enabled; struct drm_encoder* encoder; } ;
struct amdgpu_connector_atom_dig {int dp_clock; } ;
struct amdgpu_connector {struct amdgpu_connector_atom_dig* con_priv; } ;
typedef  int /*<<< orphan*/  args ;

/* Variables and functions */
 int /*<<< orphan*/  ADJUST_DISPLAY_CONFIG_SS_ENABLE ; 
 int /*<<< orphan*/  AMDGPU_PLL_IS_LCD ; 
 int /*<<< orphan*/  AMDGPU_PLL_PREFER_CLOSEST_LOWER ; 
 int /*<<< orphan*/  AMDGPU_PLL_USE_FRAC_FB_DIV ; 
 int /*<<< orphan*/  AMDGPU_PLL_USE_POST_DIV ; 
 int /*<<< orphan*/  AMDGPU_PLL_USE_REF_DIV ; 
 int ATOM_DEVICE_DFP_SUPPORT ; 
 int ATOM_DEVICE_LCD_SUPPORT ; 
 int ATOM_DEVICE_TV_SUPPORT ; 
 int ATOM_ENCODER_MODE_HDMI ; 
 int /*<<< orphan*/  AdjustDisplayPll ; 
 int /*<<< orphan*/  COMMAND ; 
 int /*<<< orphan*/  DISPPLL_CONFIG_COHERENT_MODE ; 
 int /*<<< orphan*/  DISPPLL_CONFIG_DUAL_LINK ; 
 int /*<<< orphan*/  DISPPLL_CONFIG_SS_ENABLE ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,int) ; 
 int /*<<< orphan*/  ENCODER_MODE_IS_DP (int) ; 
 scalar_t__ ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1 ; 
 scalar_t__ ENCODER_OBJECT_ID_NONE ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_atom_execute_table (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_atom_parse_cmd_header (int /*<<< orphan*/ ,int,int*,int*) ; 
 int amdgpu_atombios_encoder_get_encoder_mode (struct drm_encoder*) ; 
 int amdgpu_dig_monitor_is_duallink (struct drm_encoder*,int) ; 
 scalar_t__ amdgpu_encoder_get_dp_bridge_encoder_id (struct drm_encoder*) ; 
 struct drm_connector* amdgpu_get_connector_for_encoder (struct drm_encoder*) ; 
 void* cpu_to_le16 (int) ; 
 int le16_to_cpu (void*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (union adjust_pixel_clock*,int /*<<< orphan*/ ,int) ; 
 struct amdgpu_connector* to_amdgpu_connector (struct drm_connector*) ; 
 struct amdgpu_crtc* to_amdgpu_crtc (struct drm_crtc*) ; 
 struct amdgpu_encoder* to_amdgpu_encoder (struct drm_encoder*) ; 

__attribute__((used)) static u32 amdgpu_atombios_crtc_adjust_pll(struct drm_crtc *crtc,
				    struct drm_display_mode *mode)
{
	struct amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	struct drm_device *dev = crtc->dev;
	struct amdgpu_device *adev = dev->dev_private;
	struct drm_encoder *encoder = amdgpu_crtc->encoder;
	struct amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	struct drm_connector *connector = amdgpu_get_connector_for_encoder(encoder);
	u32 adjusted_clock = mode->clock;
	int encoder_mode = amdgpu_atombios_encoder_get_encoder_mode(encoder);
	u32 dp_clock = mode->clock;
	u32 clock = mode->clock;
	int bpc = amdgpu_crtc->bpc;
	bool is_duallink = amdgpu_dig_monitor_is_duallink(encoder, mode->clock);
	union adjust_pixel_clock args;
	u8 frev, crev;
	int index;

	amdgpu_crtc->pll_flags = AMDGPU_PLL_USE_FRAC_FB_DIV;

	if ((amdgpu_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT | ATOM_DEVICE_DFP_SUPPORT)) ||
	    (amdgpu_encoder_get_dp_bridge_encoder_id(encoder) != ENCODER_OBJECT_ID_NONE)) {
		if (connector) {
			struct amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);
			struct amdgpu_connector_atom_dig *dig_connector =
				amdgpu_connector->con_priv;

			dp_clock = dig_connector->dp_clock;
		}
	}

	/* use recommended ref_div for ss */
	if (amdgpu_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT)) {
		if (amdgpu_crtc->ss_enabled) {
			if (amdgpu_crtc->ss.refdiv) {
				amdgpu_crtc->pll_flags |= AMDGPU_PLL_USE_REF_DIV;
				amdgpu_crtc->pll_reference_div = amdgpu_crtc->ss.refdiv;
				amdgpu_crtc->pll_flags |= AMDGPU_PLL_USE_FRAC_FB_DIV;
			}
		}
	}

	/* DVO wants 2x pixel clock if the DVO chip is in 12 bit mode */
	if (amdgpu_encoder->encoder_id == ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1)
		adjusted_clock = mode->clock * 2;
	if (amdgpu_encoder->active_device & (ATOM_DEVICE_TV_SUPPORT))
		amdgpu_crtc->pll_flags |= AMDGPU_PLL_PREFER_CLOSEST_LOWER;
	if (amdgpu_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT))
		amdgpu_crtc->pll_flags |= AMDGPU_PLL_IS_LCD;


	/* adjust pll for deep color modes */
	if (encoder_mode == ATOM_ENCODER_MODE_HDMI) {
		switch (bpc) {
		case 8:
		default:
			break;
		case 10:
			clock = (clock * 5) / 4;
			break;
		case 12:
			clock = (clock * 3) / 2;
			break;
		case 16:
			clock = clock * 2;
			break;
		}
	}

	/* DCE3+ has an AdjustDisplayPll that will adjust the pixel clock
	 * accordingly based on the encoder/transmitter to work around
	 * special hw requirements.
	 */
	index = GetIndexIntoMasterTable(COMMAND, AdjustDisplayPll);
	if (!amdgpu_atom_parse_cmd_header(adev->mode_info.atom_context, index, &frev,
				   &crev))
		return adjusted_clock;

	memset(&args, 0, sizeof(args));

	switch (frev) {
	case 1:
		switch (crev) {
		case 1:
		case 2:
			args.v1.usPixelClock = cpu_to_le16(clock / 10);
			args.v1.ucTransmitterID = amdgpu_encoder->encoder_id;
			args.v1.ucEncodeMode = encoder_mode;
			if (amdgpu_crtc->ss_enabled && amdgpu_crtc->ss.percentage)
				args.v1.ucConfig |=
					ADJUST_DISPLAY_CONFIG_SS_ENABLE;

			amdgpu_atom_execute_table(adev->mode_info.atom_context,
					   index, (uint32_t *)&args);
			adjusted_clock = le16_to_cpu(args.v1.usPixelClock) * 10;
			break;
		case 3:
			args.v3.sInput.usPixelClock = cpu_to_le16(clock / 10);
			args.v3.sInput.ucTransmitterID = amdgpu_encoder->encoder_id;
			args.v3.sInput.ucEncodeMode = encoder_mode;
			args.v3.sInput.ucDispPllConfig = 0;
			if (amdgpu_crtc->ss_enabled && amdgpu_crtc->ss.percentage)
				args.v3.sInput.ucDispPllConfig |=
					DISPPLL_CONFIG_SS_ENABLE;
			if (ENCODER_MODE_IS_DP(encoder_mode)) {
				args.v3.sInput.ucDispPllConfig |=
					DISPPLL_CONFIG_COHERENT_MODE;
				/* 16200 or 27000 */
				args.v3.sInput.usPixelClock = cpu_to_le16(dp_clock / 10);
			} else if (amdgpu_encoder->devices & (ATOM_DEVICE_DFP_SUPPORT)) {
				struct amdgpu_encoder_atom_dig *dig = amdgpu_encoder->enc_priv;
				if (dig->coherent_mode)
					args.v3.sInput.ucDispPllConfig |=
						DISPPLL_CONFIG_COHERENT_MODE;
				if (is_duallink)
					args.v3.sInput.ucDispPllConfig |=
						DISPPLL_CONFIG_DUAL_LINK;
			}
			if (amdgpu_encoder_get_dp_bridge_encoder_id(encoder) !=
			    ENCODER_OBJECT_ID_NONE)
				args.v3.sInput.ucExtTransmitterID =
					amdgpu_encoder_get_dp_bridge_encoder_id(encoder);
			else
				args.v3.sInput.ucExtTransmitterID = 0;

			amdgpu_atom_execute_table(adev->mode_info.atom_context,
					   index, (uint32_t *)&args);
			adjusted_clock = le32_to_cpu(args.v3.sOutput.ulDispPllFreq) * 10;
			if (args.v3.sOutput.ucRefDiv) {
				amdgpu_crtc->pll_flags |= AMDGPU_PLL_USE_FRAC_FB_DIV;
				amdgpu_crtc->pll_flags |= AMDGPU_PLL_USE_REF_DIV;
				amdgpu_crtc->pll_reference_div = args.v3.sOutput.ucRefDiv;
			}
			if (args.v3.sOutput.ucPostDiv) {
				amdgpu_crtc->pll_flags |= AMDGPU_PLL_USE_FRAC_FB_DIV;
				amdgpu_crtc->pll_flags |= AMDGPU_PLL_USE_POST_DIV;
				amdgpu_crtc->pll_post_div = args.v3.sOutput.ucPostDiv;
			}
			break;
		default:
			DRM_ERROR("Unknown table version %d %d\n", frev, crev);
			return adjusted_clock;
		}
		break;
	default:
		DRM_ERROR("Unknown table version %d %d\n", frev, crev);
		return adjusted_clock;
	}

	return adjusted_clock;
}