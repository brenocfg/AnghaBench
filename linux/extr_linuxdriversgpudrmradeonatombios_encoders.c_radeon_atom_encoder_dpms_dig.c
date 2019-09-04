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
struct radeon_encoder_atom_dig {int /*<<< orphan*/  active_mst_links; int /*<<< orphan*/  backlight_level; int /*<<< orphan*/  panel_mode; } ;
struct radeon_encoder {int devices; struct radeon_encoder_atom_dig* enc_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  bl_encoder; } ;
struct radeon_device {TYPE_1__ mode_info; } ;
struct radeon_connector_atom_dig {int edp_on; } ;
struct radeon_connector {struct radeon_connector_atom_dig* con_priv; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct drm_connector {int /*<<< orphan*/  connector_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_IS_DCE4 (struct radeon_device*) ; 
 int /*<<< orphan*/  ASIC_IS_DCE41 (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE5 (struct radeon_device*) ; 
 int /*<<< orphan*/  ASIC_IS_DCE61 (struct radeon_device*) ; 
 int ATOM_DEVICE_LCD_SUPPORT ; 
 int /*<<< orphan*/  ATOM_DISABLE ; 
 int /*<<< orphan*/  ATOM_ENABLE ; 
 int /*<<< orphan*/  ATOM_ENCODER_CMD_DP_VIDEO_OFF ; 
 int /*<<< orphan*/  ATOM_ENCODER_CMD_DP_VIDEO_ON ; 
 int /*<<< orphan*/  ATOM_ENCODER_CMD_SETUP ; 
 int /*<<< orphan*/  ATOM_ENCODER_CMD_SETUP_PANEL_MODE ; 
 int /*<<< orphan*/  ATOM_TRANSMITTER_ACTION_DISABLE ; 
 int /*<<< orphan*/  ATOM_TRANSMITTER_ACTION_ENABLE ; 
 int /*<<< orphan*/  ATOM_TRANSMITTER_ACTION_LCD_BLOFF ; 
 int /*<<< orphan*/  ATOM_TRANSMITTER_ACTION_LCD_BLON ; 
 int /*<<< orphan*/  ATOM_TRANSMITTER_ACTION_POWER_OFF ; 
 int /*<<< orphan*/  ATOM_TRANSMITTER_ACTION_POWER_ON ; 
 int /*<<< orphan*/  ATOM_TRANSMITTER_ACTION_SETUP ; 
 int /*<<< orphan*/  DP_PANEL_MODE_EXTERNAL_DP_MODE ; 
 int /*<<< orphan*/  DP_SET_POWER_D3 ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_eDP ; 
#define  DRM_MODE_DPMS_OFF 131 
#define  DRM_MODE_DPMS_ON 130 
#define  DRM_MODE_DPMS_STANDBY 129 
#define  DRM_MODE_DPMS_SUSPEND 128 
 int /*<<< orphan*/  ENCODER_MODE_IS_DP (int /*<<< orphan*/ ) ; 
 scalar_t__ ENCODER_OBJECT_ID_TRAVIS ; 
 int /*<<< orphan*/  EXTERNAL_ENCODER_ACTION_V3_ENCODER_SETUP ; 
 int /*<<< orphan*/  atombios_dig_encoder_setup (struct drm_encoder*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atombios_dig_transmitter_setup (struct drm_encoder*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atombios_external_encoder_setup (struct drm_encoder*,struct drm_encoder*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atombios_get_encoder_mode (struct drm_encoder*) ; 
 int /*<<< orphan*/  atombios_set_backlight_level (struct radeon_encoder*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atombios_set_edp_panel_power (struct drm_connector*,int /*<<< orphan*/ ) ; 
 scalar_t__ radeon_connector_encoder_get_dp_bridge_encoder_id (struct drm_connector*) ; 
 int /*<<< orphan*/  radeon_dp_get_panel_mode (struct drm_encoder*,struct drm_connector*) ; 
 int /*<<< orphan*/  radeon_dp_link_train (struct drm_encoder*,struct drm_connector*) ; 
 int /*<<< orphan*/  radeon_dp_set_rx_power_state (struct drm_connector*,int /*<<< orphan*/ ) ; 
 struct drm_connector* radeon_get_connector_for_encoder (struct drm_encoder*) ; 
 struct drm_encoder* radeon_get_external_encoder (struct drm_encoder*) ; 
 struct radeon_connector* to_radeon_connector (struct drm_connector*) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void
radeon_atom_encoder_dpms_dig(struct drm_encoder *encoder, int mode)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	struct drm_encoder *ext_encoder = radeon_get_external_encoder(encoder);
	struct radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;
	struct drm_connector *connector = radeon_get_connector_for_encoder(encoder);
	struct radeon_connector *radeon_connector = NULL;
	struct radeon_connector_atom_dig *radeon_dig_connector = NULL;
	bool travis_quirk = false;

	if (connector) {
		radeon_connector = to_radeon_connector(connector);
		radeon_dig_connector = radeon_connector->con_priv;
		if ((radeon_connector_encoder_get_dp_bridge_encoder_id(connector) ==
		     ENCODER_OBJECT_ID_TRAVIS) &&
		    (radeon_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT)) &&
		    !ASIC_IS_DCE5(rdev))
			travis_quirk = true;
	}

	switch (mode) {
	case DRM_MODE_DPMS_ON:
		if (ASIC_IS_DCE41(rdev) || ASIC_IS_DCE5(rdev)) {
			if (!connector)
				dig->panel_mode = DP_PANEL_MODE_EXTERNAL_DP_MODE;
			else
				dig->panel_mode = radeon_dp_get_panel_mode(encoder, connector);

			/* setup and enable the encoder */
			atombios_dig_encoder_setup(encoder, ATOM_ENCODER_CMD_SETUP, 0);
			atombios_dig_encoder_setup(encoder,
						   ATOM_ENCODER_CMD_SETUP_PANEL_MODE,
						   dig->panel_mode);
			if (ext_encoder) {
				if (ASIC_IS_DCE41(rdev) || ASIC_IS_DCE61(rdev))
					atombios_external_encoder_setup(encoder, ext_encoder,
									EXTERNAL_ENCODER_ACTION_V3_ENCODER_SETUP);
			}
		} else if (ASIC_IS_DCE4(rdev)) {
			/* setup and enable the encoder */
			atombios_dig_encoder_setup(encoder, ATOM_ENCODER_CMD_SETUP, 0);
		} else {
			/* setup and enable the encoder and transmitter */
			atombios_dig_encoder_setup(encoder, ATOM_ENABLE, 0);
			atombios_dig_transmitter_setup(encoder, ATOM_TRANSMITTER_ACTION_SETUP, 0, 0);
		}
		if (ENCODER_MODE_IS_DP(atombios_get_encoder_mode(encoder)) && connector) {
			if (connector->connector_type == DRM_MODE_CONNECTOR_eDP) {
				atombios_set_edp_panel_power(connector,
							     ATOM_TRANSMITTER_ACTION_POWER_ON);
				radeon_dig_connector->edp_on = true;
			}
		}
		/* enable the transmitter */
		atombios_dig_transmitter_setup(encoder, ATOM_TRANSMITTER_ACTION_ENABLE, 0, 0);
		if (ENCODER_MODE_IS_DP(atombios_get_encoder_mode(encoder)) && connector) {
			/* DP_SET_POWER_D0 is set in radeon_dp_link_train */
			radeon_dp_link_train(encoder, connector);
			if (ASIC_IS_DCE4(rdev))
				atombios_dig_encoder_setup(encoder, ATOM_ENCODER_CMD_DP_VIDEO_ON, 0);
		}
		if (radeon_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT)) {
			if (rdev->mode_info.bl_encoder)
				atombios_set_backlight_level(radeon_encoder, dig->backlight_level);
			else
				atombios_dig_transmitter_setup(encoder,
							       ATOM_TRANSMITTER_ACTION_LCD_BLON, 0, 0);
		}
		if (ext_encoder)
			atombios_external_encoder_setup(encoder, ext_encoder, ATOM_ENABLE);
		break;
	case DRM_MODE_DPMS_STANDBY:
	case DRM_MODE_DPMS_SUSPEND:
	case DRM_MODE_DPMS_OFF:

		/* don't power off encoders with active MST links */
		if (dig->active_mst_links)
			return;

		if (ASIC_IS_DCE4(rdev)) {
			if (ENCODER_MODE_IS_DP(atombios_get_encoder_mode(encoder)) && connector)
				atombios_dig_encoder_setup(encoder, ATOM_ENCODER_CMD_DP_VIDEO_OFF, 0);
		}
		if (ext_encoder)
			atombios_external_encoder_setup(encoder, ext_encoder, ATOM_DISABLE);
		if (radeon_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT))
			atombios_dig_transmitter_setup(encoder,
						       ATOM_TRANSMITTER_ACTION_LCD_BLOFF, 0, 0);

		if (ENCODER_MODE_IS_DP(atombios_get_encoder_mode(encoder)) &&
		    connector && !travis_quirk)
			radeon_dp_set_rx_power_state(connector, DP_SET_POWER_D3);
		if (ASIC_IS_DCE4(rdev)) {
			/* disable the transmitter */
			atombios_dig_transmitter_setup(encoder,
						       ATOM_TRANSMITTER_ACTION_DISABLE, 0, 0);
		} else {
			/* disable the encoder and transmitter */
			atombios_dig_transmitter_setup(encoder,
						       ATOM_TRANSMITTER_ACTION_DISABLE, 0, 0);
			atombios_dig_encoder_setup(encoder, ATOM_DISABLE, 0);
		}
		if (ENCODER_MODE_IS_DP(atombios_get_encoder_mode(encoder)) && connector) {
			if (travis_quirk)
				radeon_dp_set_rx_power_state(connector, DP_SET_POWER_D3);
			if (connector->connector_type == DRM_MODE_CONNECTOR_eDP) {
				atombios_set_edp_panel_power(connector,
							     ATOM_TRANSMITTER_ACTION_POWER_OFF);
				radeon_dig_connector->edp_on = false;
			}
		}
		break;
	}
}