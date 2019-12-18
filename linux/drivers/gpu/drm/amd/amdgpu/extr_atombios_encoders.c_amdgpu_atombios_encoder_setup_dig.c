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
struct drm_encoder {int dummy; } ;
struct drm_connector {scalar_t__ connector_type; } ;
struct amdgpu_encoder_atom_dig {int /*<<< orphan*/  backlight_level; int /*<<< orphan*/  panel_mode; } ;
struct amdgpu_encoder {int devices; struct amdgpu_encoder_atom_dig* enc_priv; } ;
struct amdgpu_connector_atom_dig {int edp_on; } ;
struct amdgpu_connector {struct amdgpu_connector_atom_dig* con_priv; } ;

/* Variables and functions */
 int ATOM_DEVICE_LCD_SUPPORT ; 
 int ATOM_DISABLE ; 
 int ATOM_ENABLE ; 
 int /*<<< orphan*/  ATOM_ENCODER_CMD_DP_VIDEO_OFF ; 
 int /*<<< orphan*/  ATOM_ENCODER_CMD_DP_VIDEO_ON ; 
 int /*<<< orphan*/  ATOM_ENCODER_CMD_SETUP ; 
 int /*<<< orphan*/  ATOM_ENCODER_CMD_SETUP_PANEL_MODE ; 
 int /*<<< orphan*/  ATOM_TRANSMITTER_ACTION_DISABLE ; 
 int /*<<< orphan*/  ATOM_TRANSMITTER_ACTION_ENABLE ; 
 int /*<<< orphan*/  ATOM_TRANSMITTER_ACTION_LCD_BLOFF ; 
 int /*<<< orphan*/  ATOM_TRANSMITTER_ACTION_POWER_OFF ; 
 int /*<<< orphan*/  ATOM_TRANSMITTER_ACTION_POWER_ON ; 
 int /*<<< orphan*/  DP_PANEL_MODE_EXTERNAL_DP_MODE ; 
 int /*<<< orphan*/  DP_SET_POWER_D3 ; 
 scalar_t__ DRM_MODE_CONNECTOR_eDP ; 
 scalar_t__ ENCODER_MODE_IS_DP (int /*<<< orphan*/ ) ; 
 int EXTERNAL_ENCODER_ACTION_V3_ENCODER_SETUP ; 
 int /*<<< orphan*/  amdgpu_atombios_dp_get_panel_mode (struct drm_encoder*,struct drm_connector*) ; 
 int /*<<< orphan*/  amdgpu_atombios_dp_link_train (struct drm_encoder*,struct drm_connector*) ; 
 int /*<<< orphan*/  amdgpu_atombios_dp_set_rx_power_state (struct drm_connector*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_atombios_encoder_get_encoder_mode (struct drm_encoder*) ; 
 int /*<<< orphan*/  amdgpu_atombios_encoder_set_backlight_level (struct amdgpu_encoder*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_atombios_encoder_set_edp_panel_power (struct drm_connector*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_atombios_encoder_setup_dig_encoder (struct drm_encoder*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_atombios_encoder_setup_dig_transmitter (struct drm_encoder*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_atombios_encoder_setup_external_encoder (struct drm_encoder*,struct drm_encoder*,int) ; 
 struct drm_connector* amdgpu_get_connector_for_encoder (struct drm_encoder*) ; 
 struct drm_encoder* amdgpu_get_external_encoder (struct drm_encoder*) ; 
 struct amdgpu_connector* to_amdgpu_connector (struct drm_connector*) ; 
 struct amdgpu_encoder* to_amdgpu_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void
amdgpu_atombios_encoder_setup_dig(struct drm_encoder *encoder, int action)
{
	struct amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	struct drm_encoder *ext_encoder = amdgpu_get_external_encoder(encoder);
	struct amdgpu_encoder_atom_dig *dig = amdgpu_encoder->enc_priv;
	struct drm_connector *connector = amdgpu_get_connector_for_encoder(encoder);
	struct amdgpu_connector *amdgpu_connector = NULL;
	struct amdgpu_connector_atom_dig *amdgpu_dig_connector = NULL;

	if (connector) {
		amdgpu_connector = to_amdgpu_connector(connector);
		amdgpu_dig_connector = amdgpu_connector->con_priv;
	}

	if (action == ATOM_ENABLE) {
		if (!connector)
			dig->panel_mode = DP_PANEL_MODE_EXTERNAL_DP_MODE;
		else
			dig->panel_mode = amdgpu_atombios_dp_get_panel_mode(encoder, connector);

		/* setup and enable the encoder */
		amdgpu_atombios_encoder_setup_dig_encoder(encoder, ATOM_ENCODER_CMD_SETUP, 0);
		amdgpu_atombios_encoder_setup_dig_encoder(encoder,
						   ATOM_ENCODER_CMD_SETUP_PANEL_MODE,
						   dig->panel_mode);
		if (ext_encoder)
			amdgpu_atombios_encoder_setup_external_encoder(encoder, ext_encoder,
								EXTERNAL_ENCODER_ACTION_V3_ENCODER_SETUP);
		if (ENCODER_MODE_IS_DP(amdgpu_atombios_encoder_get_encoder_mode(encoder)) &&
		    connector) {
			if (connector->connector_type == DRM_MODE_CONNECTOR_eDP) {
				amdgpu_atombios_encoder_set_edp_panel_power(connector,
								     ATOM_TRANSMITTER_ACTION_POWER_ON);
				amdgpu_dig_connector->edp_on = true;
			}
		}
		/* enable the transmitter */
		amdgpu_atombios_encoder_setup_dig_transmitter(encoder,
						       ATOM_TRANSMITTER_ACTION_ENABLE,
						       0, 0);
		if (ENCODER_MODE_IS_DP(amdgpu_atombios_encoder_get_encoder_mode(encoder)) &&
		    connector) {
			/* DP_SET_POWER_D0 is set in amdgpu_atombios_dp_link_train */
			amdgpu_atombios_dp_link_train(encoder, connector);
			amdgpu_atombios_encoder_setup_dig_encoder(encoder, ATOM_ENCODER_CMD_DP_VIDEO_ON, 0);
		}
		if (amdgpu_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT))
			amdgpu_atombios_encoder_set_backlight_level(amdgpu_encoder, dig->backlight_level);
		if (ext_encoder)
			amdgpu_atombios_encoder_setup_external_encoder(encoder, ext_encoder, ATOM_ENABLE);
	} else {
		if (ENCODER_MODE_IS_DP(amdgpu_atombios_encoder_get_encoder_mode(encoder)) &&
		    connector)
			amdgpu_atombios_encoder_setup_dig_encoder(encoder,
							   ATOM_ENCODER_CMD_DP_VIDEO_OFF, 0);
		if (ext_encoder)
			amdgpu_atombios_encoder_setup_external_encoder(encoder, ext_encoder, ATOM_DISABLE);
		if (amdgpu_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT))
			amdgpu_atombios_encoder_setup_dig_transmitter(encoder,
							       ATOM_TRANSMITTER_ACTION_LCD_BLOFF, 0, 0);

		if (ENCODER_MODE_IS_DP(amdgpu_atombios_encoder_get_encoder_mode(encoder)) &&
		    connector)
			amdgpu_atombios_dp_set_rx_power_state(connector, DP_SET_POWER_D3);
		/* disable the transmitter */
		amdgpu_atombios_encoder_setup_dig_transmitter(encoder,
						       ATOM_TRANSMITTER_ACTION_DISABLE, 0, 0);
		if (ENCODER_MODE_IS_DP(amdgpu_atombios_encoder_get_encoder_mode(encoder)) &&
		    connector) {
			if (connector->connector_type == DRM_MODE_CONNECTOR_eDP) {
				amdgpu_atombios_encoder_set_edp_panel_power(connector,
								     ATOM_TRANSMITTER_ACTION_POWER_OFF);
				amdgpu_dig_connector->edp_on = false;
			}
		}
	}
}