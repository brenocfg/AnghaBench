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
struct radeon_encoder_atom_dig {int lcd_misc; } ;
struct radeon_encoder {struct radeon_encoder_atom_dig* enc_priv; } ;
struct radeon_device {int dummy; } ;
struct radeon_connector_atom_dig {int /*<<< orphan*/  dp_sink_type; } ;
struct radeon_connector {int pixelclock_for_modeset; struct radeon_connector_atom_dig* con_priv; int /*<<< orphan*/  use_digital; } ;
struct drm_encoder {int dummy; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct drm_connector_helper_funcs {struct drm_encoder* (* best_encoder ) (struct drm_connector*) ;} ;
struct TYPE_2__ {int bpc; int max_tmds_clock; int edid_hdmi_dc_modes; } ;
struct drm_connector {int connector_type; TYPE_1__ display_info; int /*<<< orphan*/  name; struct drm_connector_helper_funcs* helper_private; struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_IS_DCE4 (struct radeon_device*) ; 
 int /*<<< orphan*/  ASIC_IS_DCE41 (struct radeon_device*) ; 
 int /*<<< orphan*/  ASIC_IS_DCE5 (struct radeon_device*) ; 
 int ATOM_PANEL_MISC_V13_6BIT_PER_COLOR ; 
 int ATOM_PANEL_MISC_V13_8BIT_PER_COLOR ; 
 int /*<<< orphan*/  CONNECTOR_OBJECT_ID_DISPLAYPORT ; 
 int /*<<< orphan*/  CONNECTOR_OBJECT_ID_eDP ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ,...) ; 
 int DRM_EDID_HDMI_DC_30 ; 
#define  DRM_MODE_CONNECTOR_DVID 134 
#define  DRM_MODE_CONNECTOR_DVII 133 
#define  DRM_MODE_CONNECTOR_DisplayPort 132 
#define  DRM_MODE_CONNECTOR_HDMIA 131 
#define  DRM_MODE_CONNECTOR_HDMIB 130 
#define  DRM_MODE_CONNECTOR_LVDS 129 
#define  DRM_MODE_CONNECTOR_eDP 128 
 scalar_t__ drm_detect_hdmi_monitor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_connector_edid (struct drm_connector*) ; 
 scalar_t__ radeon_deep_color ; 
 struct drm_encoder* stub1 (struct drm_connector*) ; 
 struct radeon_connector* to_radeon_connector (struct drm_connector*) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

int radeon_get_monitor_bpc(struct drm_connector *connector)
{
	struct drm_device *dev = connector->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_connector *radeon_connector = to_radeon_connector(connector);
	struct radeon_connector_atom_dig *dig_connector;
	int bpc = 8;
	int mode_clock, max_tmds_clock;

	switch (connector->connector_type) {
	case DRM_MODE_CONNECTOR_DVII:
	case DRM_MODE_CONNECTOR_HDMIB:
		if (radeon_connector->use_digital) {
			if (drm_detect_hdmi_monitor(radeon_connector_edid(connector))) {
				if (connector->display_info.bpc)
					bpc = connector->display_info.bpc;
			}
		}
		break;
	case DRM_MODE_CONNECTOR_DVID:
	case DRM_MODE_CONNECTOR_HDMIA:
		if (drm_detect_hdmi_monitor(radeon_connector_edid(connector))) {
			if (connector->display_info.bpc)
				bpc = connector->display_info.bpc;
		}
		break;
	case DRM_MODE_CONNECTOR_DisplayPort:
		dig_connector = radeon_connector->con_priv;
		if ((dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_DISPLAYPORT) ||
		    (dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_eDP) ||
		    drm_detect_hdmi_monitor(radeon_connector_edid(connector))) {
			if (connector->display_info.bpc)
				bpc = connector->display_info.bpc;
		}
		break;
	case DRM_MODE_CONNECTOR_eDP:
	case DRM_MODE_CONNECTOR_LVDS:
		if (connector->display_info.bpc)
			bpc = connector->display_info.bpc;
		else if (ASIC_IS_DCE41(rdev) || ASIC_IS_DCE5(rdev)) {
			const struct drm_connector_helper_funcs *connector_funcs =
				connector->helper_private;
			struct drm_encoder *encoder = connector_funcs->best_encoder(connector);
			struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
			struct radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;

			if (dig->lcd_misc & ATOM_PANEL_MISC_V13_6BIT_PER_COLOR)
				bpc = 6;
			else if (dig->lcd_misc & ATOM_PANEL_MISC_V13_8BIT_PER_COLOR)
				bpc = 8;
		}
		break;
	}

	if (drm_detect_hdmi_monitor(radeon_connector_edid(connector))) {
		/* hdmi deep color only implemented on DCE4+ */
		if ((bpc > 8) && !ASIC_IS_DCE4(rdev)) {
			DRM_DEBUG("%s: HDMI deep color %d bpc unsupported. Using 8 bpc.\n",
					  connector->name, bpc);
			bpc = 8;
		}

		/*
		 * Pre DCE-8 hw can't handle > 12 bpc, and more than 12 bpc doesn't make
		 * much sense without support for > 12 bpc framebuffers. RGB 4:4:4 at
		 * 12 bpc is always supported on hdmi deep color sinks, as this is
		 * required by the HDMI-1.3 spec. Clamp to a safe 12 bpc maximum.
		 */
		if (bpc > 12) {
			DRM_DEBUG("%s: HDMI deep color %d bpc unsupported. Using 12 bpc.\n",
					  connector->name, bpc);
			bpc = 12;
		}

		/* Any defined maximum tmds clock limit we must not exceed? */
		if (connector->display_info.max_tmds_clock > 0) {
			/* mode_clock is clock in kHz for mode to be modeset on this connector */
			mode_clock = radeon_connector->pixelclock_for_modeset;

			/* Maximum allowable input clock in kHz */
			max_tmds_clock = connector->display_info.max_tmds_clock;

			DRM_DEBUG("%s: hdmi mode dotclock %d kHz, max tmds input clock %d kHz.\n",
					  connector->name, mode_clock, max_tmds_clock);

			/* Check if bpc is within clock limit. Try to degrade gracefully otherwise */
			if ((bpc == 12) && (mode_clock * 3/2 > max_tmds_clock)) {
				if ((connector->display_info.edid_hdmi_dc_modes & DRM_EDID_HDMI_DC_30) &&
					(mode_clock * 5/4 <= max_tmds_clock))
					bpc = 10;
				else
					bpc = 8;

				DRM_DEBUG("%s: HDMI deep color 12 bpc exceeds max tmds clock. Using %d bpc.\n",
						  connector->name, bpc);
			}

			if ((bpc == 10) && (mode_clock * 5/4 > max_tmds_clock)) {
				bpc = 8;
				DRM_DEBUG("%s: HDMI deep color 10 bpc exceeds max tmds clock. Using %d bpc.\n",
						  connector->name, bpc);
			}
		}
		else if (bpc > 8) {
			/* max_tmds_clock missing, but hdmi spec mandates it for deep color. */
			DRM_DEBUG("%s: Required max tmds clock for HDMI deep color missing. Using 8 bpc.\n",
					  connector->name);
			bpc = 8;
		}
	}

	if ((radeon_deep_color == 0) && (bpc > 8)) {
		DRM_DEBUG("%s: Deep color disabled. Set radeon module param deep_color=1 to enable.\n",
				  connector->name);
		bpc = 8;
	}

	DRM_DEBUG("%s: Display bpc=%d, returned bpc=%d\n",
			  connector->name, connector->display_info.bpc, bpc);

	return bpc;
}