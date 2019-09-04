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
struct radeon_encoder_atom_dig {scalar_t__ active_mst_links; } ;
struct radeon_encoder {scalar_t__ encoder_id; scalar_t__ offset; scalar_t__ is_mst_encoder; struct radeon_encoder_atom_dig* enc_priv; } ;
struct radeon_device {int dummy; } ;
struct radeon_connector_atom_dig {int /*<<< orphan*/  dp_sink_type; } ;
struct radeon_connector {int /*<<< orphan*/  audio; struct radeon_connector_atom_dig* con_priv; int /*<<< orphan*/  use_digital; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct drm_connector {int connector_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_IS_DCE4 (struct radeon_device*) ; 
 int /*<<< orphan*/  ASIC_IS_DCE5 (struct radeon_device*) ; 
 int ATOM_ENCODER_MODE_CRT ; 
 int ATOM_ENCODER_MODE_DP ; 
 int ATOM_ENCODER_MODE_DP_AUDIO ; 
 int ATOM_ENCODER_MODE_DP_MST ; 
 int ATOM_ENCODER_MODE_DVI ; 
 int ATOM_ENCODER_MODE_DVO ; 
 int ATOM_ENCODER_MODE_HDMI ; 
 int ATOM_ENCODER_MODE_LVDS ; 
 int ATOM_ENCODER_MODE_TV ; 
 int /*<<< orphan*/  CONNECTOR_OBJECT_ID_DISPLAYPORT ; 
 int /*<<< orphan*/  CONNECTOR_OBJECT_ID_eDP ; 
#define  DRM_MODE_CONNECTOR_9PinDIN 139 
#define  DRM_MODE_CONNECTOR_Composite 138 
#define  DRM_MODE_CONNECTOR_DVIA 137 
#define  DRM_MODE_CONNECTOR_DVID 136 
#define  DRM_MODE_CONNECTOR_DVII 135 
#define  DRM_MODE_CONNECTOR_DisplayPort 134 
#define  DRM_MODE_CONNECTOR_HDMIA 133 
#define  DRM_MODE_CONNECTOR_HDMIB 132 
#define  DRM_MODE_CONNECTOR_LVDS 131 
#define  DRM_MODE_CONNECTOR_SVIDEO 130 
#define  DRM_MODE_CONNECTOR_VGA 129 
#define  DRM_MODE_CONNECTOR_eDP 128 
 scalar_t__ ENCODER_OBJECT_ID_INTERNAL_DVO1 ; 
 scalar_t__ ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1 ; 
 scalar_t__ ENCODER_OBJECT_ID_NONE ; 
 int /*<<< orphan*/  RADEON_AUDIO_AUTO ; 
 int /*<<< orphan*/  RADEON_AUDIO_ENABLE ; 
 int /*<<< orphan*/  drm_detect_hdmi_monitor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_detect_monitor_audio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_audio ; 
 int /*<<< orphan*/  radeon_connector_edid (struct drm_connector*) ; 
 scalar_t__ radeon_encoder_get_dp_bridge_encoder_id (struct drm_encoder*) ; 
 scalar_t__ radeon_encoder_is_digital (struct drm_encoder*) ; 
 struct drm_connector* radeon_get_connector_for_encoder (struct drm_encoder*) ; 
 struct drm_connector* radeon_get_connector_for_encoder_init (struct drm_encoder*) ; 
 struct radeon_connector* to_radeon_connector (struct drm_connector*) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

int
atombios_get_encoder_mode(struct drm_encoder *encoder)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	struct drm_connector *connector;
	struct radeon_connector *radeon_connector;
	struct radeon_connector_atom_dig *dig_connector;
	struct radeon_encoder_atom_dig *dig_enc;

	if (radeon_encoder_is_digital(encoder)) {
		dig_enc = radeon_encoder->enc_priv;
		if (dig_enc->active_mst_links)
			return ATOM_ENCODER_MODE_DP_MST;
	}
	if (radeon_encoder->is_mst_encoder || radeon_encoder->offset)
		return ATOM_ENCODER_MODE_DP_MST;
	/* dp bridges are always DP */
	if (radeon_encoder_get_dp_bridge_encoder_id(encoder) != ENCODER_OBJECT_ID_NONE)
		return ATOM_ENCODER_MODE_DP;

	/* DVO is always DVO */
	if ((radeon_encoder->encoder_id == ENCODER_OBJECT_ID_INTERNAL_DVO1) ||
	    (radeon_encoder->encoder_id == ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1))
		return ATOM_ENCODER_MODE_DVO;

	connector = radeon_get_connector_for_encoder(encoder);
	/* if we don't have an active device yet, just use one of
	 * the connectors tied to the encoder.
	 */
	if (!connector)
		connector = radeon_get_connector_for_encoder_init(encoder);
	radeon_connector = to_radeon_connector(connector);

	switch (connector->connector_type) {
	case DRM_MODE_CONNECTOR_DVII:
	case DRM_MODE_CONNECTOR_HDMIB: /* HDMI-B is basically DL-DVI; analog works fine */
		if (radeon_audio != 0) {
			if (radeon_connector->use_digital &&
			    (radeon_connector->audio == RADEON_AUDIO_ENABLE))
				return ATOM_ENCODER_MODE_HDMI;
			else if (drm_detect_hdmi_monitor(radeon_connector_edid(connector)) &&
				 (radeon_connector->audio == RADEON_AUDIO_AUTO))
				return ATOM_ENCODER_MODE_HDMI;
			else if (radeon_connector->use_digital)
				return ATOM_ENCODER_MODE_DVI;
			else
				return ATOM_ENCODER_MODE_CRT;
		} else if (radeon_connector->use_digital) {
			return ATOM_ENCODER_MODE_DVI;
		} else {
			return ATOM_ENCODER_MODE_CRT;
		}
		break;
	case DRM_MODE_CONNECTOR_DVID:
	case DRM_MODE_CONNECTOR_HDMIA:
	default:
		if (radeon_audio != 0) {
			if (radeon_connector->audio == RADEON_AUDIO_ENABLE)
				return ATOM_ENCODER_MODE_HDMI;
			else if (drm_detect_hdmi_monitor(radeon_connector_edid(connector)) &&
				 (radeon_connector->audio == RADEON_AUDIO_AUTO))
				return ATOM_ENCODER_MODE_HDMI;
			else
				return ATOM_ENCODER_MODE_DVI;
		} else {
			return ATOM_ENCODER_MODE_DVI;
		}
		break;
	case DRM_MODE_CONNECTOR_LVDS:
		return ATOM_ENCODER_MODE_LVDS;
		break;
	case DRM_MODE_CONNECTOR_DisplayPort:
		dig_connector = radeon_connector->con_priv;
		if ((dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_DISPLAYPORT) ||
		    (dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_eDP)) {
			if (radeon_audio != 0 &&
			    drm_detect_monitor_audio(radeon_connector_edid(connector)) &&
			    ASIC_IS_DCE4(rdev) && !ASIC_IS_DCE5(rdev))
				return ATOM_ENCODER_MODE_DP_AUDIO;
			return ATOM_ENCODER_MODE_DP;
		} else if (radeon_audio != 0) {
			if (radeon_connector->audio == RADEON_AUDIO_ENABLE)
				return ATOM_ENCODER_MODE_HDMI;
			else if (drm_detect_hdmi_monitor(radeon_connector_edid(connector)) &&
				 (radeon_connector->audio == RADEON_AUDIO_AUTO))
				return ATOM_ENCODER_MODE_HDMI;
			else
				return ATOM_ENCODER_MODE_DVI;
		} else {
			return ATOM_ENCODER_MODE_DVI;
		}
		break;
	case DRM_MODE_CONNECTOR_eDP:
		if (radeon_audio != 0 &&
		    drm_detect_monitor_audio(radeon_connector_edid(connector)) &&
		    ASIC_IS_DCE4(rdev) && !ASIC_IS_DCE5(rdev))
			return ATOM_ENCODER_MODE_DP_AUDIO;
		return ATOM_ENCODER_MODE_DP;
	case DRM_MODE_CONNECTOR_DVIA:
	case DRM_MODE_CONNECTOR_VGA:
		return ATOM_ENCODER_MODE_CRT;
		break;
	case DRM_MODE_CONNECTOR_Composite:
	case DRM_MODE_CONNECTOR_SVIDEO:
	case DRM_MODE_CONNECTOR_9PinDIN:
		/* fix me */
		return ATOM_ENCODER_MODE_TV;
		/*return ATOM_ENCODER_MODE_CV;*/
		break;
	}
}