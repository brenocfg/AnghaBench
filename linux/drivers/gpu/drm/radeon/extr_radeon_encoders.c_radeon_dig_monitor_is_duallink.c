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
typedef  int u32 ;
struct radeon_device {int dummy; } ;
struct radeon_connector_atom_dig {int /*<<< orphan*/  dp_sink_type; } ;
struct radeon_connector {struct radeon_connector_atom_dig* con_priv; int /*<<< orphan*/  is_mst_connector; int /*<<< orphan*/  use_digital; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct drm_connector {int connector_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_IS_DCE6 (struct radeon_device*) ; 
 int /*<<< orphan*/  CONNECTOR_OBJECT_ID_DISPLAYPORT ; 
 int /*<<< orphan*/  CONNECTOR_OBJECT_ID_eDP ; 
#define  DRM_MODE_CONNECTOR_DVID 132 
#define  DRM_MODE_CONNECTOR_DVII 131 
#define  DRM_MODE_CONNECTOR_DisplayPort 130 
#define  DRM_MODE_CONNECTOR_HDMIA 129 
#define  DRM_MODE_CONNECTOR_HDMIB 128 
 int /*<<< orphan*/  drm_detect_hdmi_monitor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_connector_edid (struct drm_connector*) ; 
 struct drm_connector* radeon_get_connector_for_encoder (struct drm_encoder*) ; 
 struct drm_connector* radeon_get_connector_for_encoder_init (struct drm_encoder*) ; 
 struct radeon_connector* to_radeon_connector (struct drm_connector*) ; 

bool radeon_dig_monitor_is_duallink(struct drm_encoder *encoder,
				    u32 pixel_clock)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct drm_connector *connector;
	struct radeon_connector *radeon_connector;
	struct radeon_connector_atom_dig *dig_connector;

	connector = radeon_get_connector_for_encoder(encoder);
	/* if we don't have an active device yet, just use one of
	 * the connectors tied to the encoder.
	 */
	if (!connector)
		connector = radeon_get_connector_for_encoder_init(encoder);
	radeon_connector = to_radeon_connector(connector);

	switch (connector->connector_type) {
	case DRM_MODE_CONNECTOR_DVII:
	case DRM_MODE_CONNECTOR_HDMIB:
		if (radeon_connector->use_digital) {
			/* HDMI 1.3 supports up to 340 Mhz over single link */
			if (ASIC_IS_DCE6(rdev) && drm_detect_hdmi_monitor(radeon_connector_edid(connector))) {
				if (pixel_clock > 340000)
					return true;
				else
					return false;
			} else {
				if (pixel_clock > 165000)
					return true;
				else
					return false;
			}
		} else
			return false;
	case DRM_MODE_CONNECTOR_DVID:
	case DRM_MODE_CONNECTOR_HDMIA:
	case DRM_MODE_CONNECTOR_DisplayPort:
		if (radeon_connector->is_mst_connector)
			return false;

		dig_connector = radeon_connector->con_priv;
		if ((dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_DISPLAYPORT) ||
		    (dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_eDP))
			return false;
		else {
			/* HDMI 1.3 supports up to 340 Mhz over single link */
			if (ASIC_IS_DCE6(rdev) && drm_detect_hdmi_monitor(radeon_connector_edid(connector))) {
				if (pixel_clock > 340000)
					return true;
				else
					return false;
			} else {
				if (pixel_clock > 165000)
					return true;
				else
					return false;
			}
		}
	default:
		return false;
	}
}