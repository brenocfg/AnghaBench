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
struct TYPE_12__ {int /*<<< orphan*/  ucPostDiv; scalar_t__ ucRefDiv; int /*<<< orphan*/  ulDispPllFreq; } ;
struct TYPE_10__ {scalar_t__ ucTransmitterID; int ucEncodeMode; scalar_t__ ucExtTransmitterID; int /*<<< orphan*/  ucDispPllConfig; void* usPixelClock; } ;
struct TYPE_13__ {TYPE_5__ sOutput; TYPE_3__ sInput; } ;
struct TYPE_8__ {scalar_t__ ucTransmitterID; int ucEncodeMode; void* usPixelClock; int /*<<< orphan*/  ucConfig; } ;
union adjust_pixel_clock {TYPE_6__ v3; TYPE_1__ v1; } ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u8 ;
typedef  int u32 ;
struct radeon_encoder_mst {int /*<<< orphan*/  coherent_mode; TYPE_7__* connector; } ;
struct radeon_encoder_atom_dig {int /*<<< orphan*/  coherent_mode; TYPE_7__* connector; } ;
struct radeon_encoder {int devices; scalar_t__ encoder_id; int active_device; struct radeon_encoder_mst* enc_priv; scalar_t__ is_mst_encoder; } ;
struct TYPE_11__ {int /*<<< orphan*/  atom_context; } ;
struct radeon_device {scalar_t__ family; TYPE_4__ mode_info; } ;
struct TYPE_9__ {int /*<<< orphan*/  percentage; scalar_t__ refdiv; } ;
struct radeon_crtc {int bpc; int /*<<< orphan*/  pll_post_div; int /*<<< orphan*/  pll_flags; scalar_t__ pll_reference_div; TYPE_2__ ss; scalar_t__ ss_enabled; struct drm_encoder* encoder; } ;
struct radeon_connector_atom_dig {int dp_clock; } ;
struct radeon_connector {struct radeon_connector_atom_dig* con_priv; } ;
struct drm_encoder {scalar_t__ encoder_type; } ;
struct drm_display_mode {int clock; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;
struct drm_connector {int dummy; } ;
typedef  int /*<<< orphan*/  args ;
struct TYPE_14__ {struct radeon_connector_atom_dig* con_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADJUST_DISPLAY_CONFIG_SS_ENABLE ; 
 scalar_t__ ASIC_IS_AVIVO (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE3 (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE32 (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE41 (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE61 (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE8 (struct radeon_device*) ; 
 int ATOM_DEVICE_DFP_SUPPORT ; 
 int ATOM_DEVICE_LCD_SUPPORT ; 
 int ATOM_DEVICE_TV_SUPPORT ; 
 int ATOM_ENCODER_MODE_HDMI ; 
 int /*<<< orphan*/  AdjustDisplayPll ; 
 scalar_t__ CHIP_RS600 ; 
 scalar_t__ CHIP_RS690 ; 
 scalar_t__ CHIP_RS740 ; 
 scalar_t__ CHIP_RS780 ; 
 scalar_t__ CHIP_RS880 ; 
 scalar_t__ CHIP_RV770 ; 
 int /*<<< orphan*/  COMMAND ; 
 int /*<<< orphan*/  DISPPLL_CONFIG_COHERENT_MODE ; 
 int /*<<< orphan*/  DISPPLL_CONFIG_DUAL_LINK ; 
 int /*<<< orphan*/  DISPPLL_CONFIG_SS_ENABLE ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,int) ; 
 scalar_t__ DRM_MODE_ENCODER_DAC ; 
 scalar_t__ DRM_MODE_ENCODER_LVDS ; 
 int /*<<< orphan*/  ENCODER_MODE_IS_DP (int) ; 
 scalar_t__ ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1 ; 
 scalar_t__ ENCODER_OBJECT_ID_NONE ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RADEON_PLL_IS_LCD ; 
 int /*<<< orphan*/  RADEON_PLL_LEGACY ; 
 int /*<<< orphan*/  RADEON_PLL_NO_ODD_POST_DIV ; 
 int /*<<< orphan*/  RADEON_PLL_PREFER_CLOSEST_LOWER ; 
 int /*<<< orphan*/  RADEON_PLL_PREFER_HIGH_FB_DIV ; 
 int /*<<< orphan*/  RADEON_PLL_PREFER_LOW_REF_DIV ; 
 int /*<<< orphan*/  RADEON_PLL_PREFER_MINM_OVER_MAXP ; 
 int /*<<< orphan*/  RADEON_PLL_USE_FRAC_FB_DIV ; 
 int /*<<< orphan*/  RADEON_PLL_USE_POST_DIV ; 
 int /*<<< orphan*/  RADEON_PLL_USE_REF_DIV ; 
 int /*<<< orphan*/  atom_execute_table (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atom_parse_cmd_header (int /*<<< orphan*/ ,int,int*,int*) ; 
 int atombios_get_encoder_mode (struct drm_encoder*) ; 
 void* cpu_to_le16 (int) ; 
 int le16_to_cpu (void*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (union adjust_pixel_clock*,int /*<<< orphan*/ ,int) ; 
 int radeon_dig_monitor_is_duallink (struct drm_encoder*,int) ; 
 scalar_t__ radeon_encoder_get_dp_bridge_encoder_id (struct drm_encoder*) ; 
 struct drm_connector* radeon_get_connector_for_encoder (struct drm_encoder*) ; 
 struct radeon_connector* to_radeon_connector (struct drm_connector*) ; 
 struct radeon_crtc* to_radeon_crtc (struct drm_crtc*) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

__attribute__((used)) static u32 atombios_adjust_pll(struct drm_crtc *crtc,
			       struct drm_display_mode *mode)
{
	struct radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	struct drm_device *dev = crtc->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct drm_encoder *encoder = radeon_crtc->encoder;
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	struct drm_connector *connector = radeon_get_connector_for_encoder(encoder);
	u32 adjusted_clock = mode->clock;
	int encoder_mode = atombios_get_encoder_mode(encoder);
	u32 dp_clock = mode->clock;
	u32 clock = mode->clock;
	int bpc = radeon_crtc->bpc;
	bool is_duallink = radeon_dig_monitor_is_duallink(encoder, mode->clock);

	/* reset the pll flags */
	radeon_crtc->pll_flags = 0;

	if (ASIC_IS_AVIVO(rdev)) {
		if ((rdev->family == CHIP_RS600) ||
		    (rdev->family == CHIP_RS690) ||
		    (rdev->family == CHIP_RS740))
			radeon_crtc->pll_flags |= (/*RADEON_PLL_USE_FRAC_FB_DIV |*/
				RADEON_PLL_PREFER_CLOSEST_LOWER);

		if (ASIC_IS_DCE32(rdev) && mode->clock > 200000)	/* range limits??? */
			radeon_crtc->pll_flags |= RADEON_PLL_PREFER_HIGH_FB_DIV;
		else
			radeon_crtc->pll_flags |= RADEON_PLL_PREFER_LOW_REF_DIV;

		if (rdev->family < CHIP_RV770)
			radeon_crtc->pll_flags |= RADEON_PLL_PREFER_MINM_OVER_MAXP;
		/* use frac fb div on APUs */
		if (ASIC_IS_DCE41(rdev) || ASIC_IS_DCE61(rdev) || ASIC_IS_DCE8(rdev))
			radeon_crtc->pll_flags |= RADEON_PLL_USE_FRAC_FB_DIV;
		/* use frac fb div on RS780/RS880 */
		if (((rdev->family == CHIP_RS780) || (rdev->family == CHIP_RS880))
		    && !radeon_crtc->ss_enabled)
			radeon_crtc->pll_flags |= RADEON_PLL_USE_FRAC_FB_DIV;
		if (ASIC_IS_DCE32(rdev) && mode->clock > 165000)
			radeon_crtc->pll_flags |= RADEON_PLL_USE_FRAC_FB_DIV;
	} else {
		radeon_crtc->pll_flags |= RADEON_PLL_LEGACY;

		if (mode->clock > 200000)	/* range limits??? */
			radeon_crtc->pll_flags |= RADEON_PLL_PREFER_HIGH_FB_DIV;
		else
			radeon_crtc->pll_flags |= RADEON_PLL_PREFER_LOW_REF_DIV;
	}

	if ((radeon_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT | ATOM_DEVICE_DFP_SUPPORT)) ||
	    (radeon_encoder_get_dp_bridge_encoder_id(encoder) != ENCODER_OBJECT_ID_NONE)) {
		if (connector) {
			struct radeon_connector *radeon_connector = to_radeon_connector(connector);
			struct radeon_connector_atom_dig *dig_connector =
				radeon_connector->con_priv;

			dp_clock = dig_connector->dp_clock;
		}
	}

	if (radeon_encoder->is_mst_encoder) {
		struct radeon_encoder_mst *mst_enc = radeon_encoder->enc_priv;
		struct radeon_connector_atom_dig *dig_connector = mst_enc->connector->con_priv;

		dp_clock = dig_connector->dp_clock;
	}

	/* use recommended ref_div for ss */
	if (radeon_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT)) {
		if (radeon_crtc->ss_enabled) {
			if (radeon_crtc->ss.refdiv) {
				radeon_crtc->pll_flags |= RADEON_PLL_USE_REF_DIV;
				radeon_crtc->pll_reference_div = radeon_crtc->ss.refdiv;
				if (ASIC_IS_AVIVO(rdev) &&
				    rdev->family != CHIP_RS780 &&
				    rdev->family != CHIP_RS880)
					radeon_crtc->pll_flags |= RADEON_PLL_USE_FRAC_FB_DIV;
			}
		}
	}

	if (ASIC_IS_AVIVO(rdev)) {
		/* DVO wants 2x pixel clock if the DVO chip is in 12 bit mode */
		if (radeon_encoder->encoder_id == ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1)
			adjusted_clock = mode->clock * 2;
		if (radeon_encoder->active_device & (ATOM_DEVICE_TV_SUPPORT))
			radeon_crtc->pll_flags |= RADEON_PLL_PREFER_CLOSEST_LOWER;
		if (radeon_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT))
			radeon_crtc->pll_flags |= RADEON_PLL_IS_LCD;
	} else {
		if (encoder->encoder_type != DRM_MODE_ENCODER_DAC)
			radeon_crtc->pll_flags |= RADEON_PLL_NO_ODD_POST_DIV;
		if (encoder->encoder_type == DRM_MODE_ENCODER_LVDS)
			radeon_crtc->pll_flags |= RADEON_PLL_USE_REF_DIV;
	}

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
	if (ASIC_IS_DCE3(rdev)) {
		union adjust_pixel_clock args;
		u8 frev, crev;
		int index;

		index = GetIndexIntoMasterTable(COMMAND, AdjustDisplayPll);
		if (!atom_parse_cmd_header(rdev->mode_info.atom_context, index, &frev,
					   &crev))
			return adjusted_clock;

		memset(&args, 0, sizeof(args));

		switch (frev) {
		case 1:
			switch (crev) {
			case 1:
			case 2:
				args.v1.usPixelClock = cpu_to_le16(clock / 10);
				args.v1.ucTransmitterID = radeon_encoder->encoder_id;
				args.v1.ucEncodeMode = encoder_mode;
				if (radeon_crtc->ss_enabled && radeon_crtc->ss.percentage)
					args.v1.ucConfig |=
						ADJUST_DISPLAY_CONFIG_SS_ENABLE;

				atom_execute_table(rdev->mode_info.atom_context,
						   index, (uint32_t *)&args);
				adjusted_clock = le16_to_cpu(args.v1.usPixelClock) * 10;
				break;
			case 3:
				args.v3.sInput.usPixelClock = cpu_to_le16(clock / 10);
				args.v3.sInput.ucTransmitterID = radeon_encoder->encoder_id;
				args.v3.sInput.ucEncodeMode = encoder_mode;
				args.v3.sInput.ucDispPllConfig = 0;
				if (radeon_crtc->ss_enabled && radeon_crtc->ss.percentage)
					args.v3.sInput.ucDispPllConfig |=
						DISPPLL_CONFIG_SS_ENABLE;
				if (ENCODER_MODE_IS_DP(encoder_mode)) {
					args.v3.sInput.ucDispPllConfig |=
						DISPPLL_CONFIG_COHERENT_MODE;
					/* 16200 or 27000 */
					args.v3.sInput.usPixelClock = cpu_to_le16(dp_clock / 10);
				} else if (radeon_encoder->devices & (ATOM_DEVICE_DFP_SUPPORT)) {
					struct radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;
					if (dig->coherent_mode)
						args.v3.sInput.ucDispPllConfig |=
							DISPPLL_CONFIG_COHERENT_MODE;
					if (is_duallink)
						args.v3.sInput.ucDispPllConfig |=
							DISPPLL_CONFIG_DUAL_LINK;
				}
				if (radeon_encoder_get_dp_bridge_encoder_id(encoder) !=
				    ENCODER_OBJECT_ID_NONE)
					args.v3.sInput.ucExtTransmitterID =
						radeon_encoder_get_dp_bridge_encoder_id(encoder);
				else
					args.v3.sInput.ucExtTransmitterID = 0;

				atom_execute_table(rdev->mode_info.atom_context,
						   index, (uint32_t *)&args);
				adjusted_clock = le32_to_cpu(args.v3.sOutput.ulDispPllFreq) * 10;
				if (args.v3.sOutput.ucRefDiv) {
					radeon_crtc->pll_flags |= RADEON_PLL_USE_FRAC_FB_DIV;
					radeon_crtc->pll_flags |= RADEON_PLL_USE_REF_DIV;
					radeon_crtc->pll_reference_div = args.v3.sOutput.ucRefDiv;
				}
				if (args.v3.sOutput.ucPostDiv) {
					radeon_crtc->pll_flags |= RADEON_PLL_USE_FRAC_FB_DIV;
					radeon_crtc->pll_flags |= RADEON_PLL_USE_POST_DIV;
					radeon_crtc->pll_post_div = args.v3.sOutput.ucPostDiv;
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
	}
	return adjusted_clock;
}