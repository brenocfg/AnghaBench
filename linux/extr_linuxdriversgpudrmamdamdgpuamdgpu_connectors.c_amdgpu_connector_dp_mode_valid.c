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
struct drm_display_mode {int hdisplay; int vdisplay; int clock; } ;
struct drm_connector {scalar_t__ connector_type; } ;
struct amdgpu_encoder {scalar_t__ rmx_type; struct drm_display_mode native_mode; } ;
struct amdgpu_connector_atom_dig {scalar_t__ dp_sink_type; } ;
struct amdgpu_connector {struct amdgpu_connector_atom_dig* con_priv; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;

/* Variables and functions */
 scalar_t__ CONNECTOR_OBJECT_ID_DISPLAYPORT ; 
 scalar_t__ CONNECTOR_OBJECT_ID_eDP ; 
 scalar_t__ DRM_MODE_CONNECTOR_LVDS ; 
 scalar_t__ DRM_MODE_CONNECTOR_eDP ; 
 int MODE_CLOCK_HIGH ; 
 int MODE_OK ; 
 int MODE_PANEL ; 
 scalar_t__ RMX_OFF ; 
 int amdgpu_atombios_dp_mode_valid_helper (struct drm_connector*,struct drm_display_mode*) ; 
 struct drm_encoder* amdgpu_connector_best_single_encoder (struct drm_connector*) ; 
 int /*<<< orphan*/  amdgpu_connector_edid (struct drm_connector*) ; 
 scalar_t__ drm_detect_hdmi_monitor (int /*<<< orphan*/ ) ; 
 struct amdgpu_connector* to_amdgpu_connector (struct drm_connector*) ; 
 struct amdgpu_encoder* to_amdgpu_encoder (struct drm_encoder*) ; 

__attribute__((used)) static enum drm_mode_status amdgpu_connector_dp_mode_valid(struct drm_connector *connector,
					   struct drm_display_mode *mode)
{
	struct amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);
	struct amdgpu_connector_atom_dig *amdgpu_dig_connector = amdgpu_connector->con_priv;

	/* XXX check mode bandwidth */

	if ((connector->connector_type == DRM_MODE_CONNECTOR_eDP) ||
	    (connector->connector_type == DRM_MODE_CONNECTOR_LVDS)) {
		struct drm_encoder *encoder = amdgpu_connector_best_single_encoder(connector);

		if ((mode->hdisplay < 320) || (mode->vdisplay < 240))
			return MODE_PANEL;

		if (encoder) {
			struct amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
			struct drm_display_mode *native_mode = &amdgpu_encoder->native_mode;

			/* AVIVO hardware supports downscaling modes larger than the panel
			 * to the panel size, but I'm not sure this is desirable.
			 */
			if ((mode->hdisplay > native_mode->hdisplay) ||
			    (mode->vdisplay > native_mode->vdisplay))
				return MODE_PANEL;

			/* if scaling is disabled, block non-native modes */
			if (amdgpu_encoder->rmx_type == RMX_OFF) {
				if ((mode->hdisplay != native_mode->hdisplay) ||
				    (mode->vdisplay != native_mode->vdisplay))
					return MODE_PANEL;
			}
		}
		return MODE_OK;
	} else {
		if ((amdgpu_dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_DISPLAYPORT) ||
		    (amdgpu_dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_eDP)) {
			return amdgpu_atombios_dp_mode_valid_helper(connector, mode);
		} else {
			if (drm_detect_hdmi_monitor(amdgpu_connector_edid(connector))) {
				/* HDMI 1.3+ supports max clock of 340 Mhz */
				if (mode->clock > 340000)
					return MODE_CLOCK_HIGH;
			} else {
				if (mode->clock > 165000)
					return MODE_CLOCK_HIGH;
			}
		}
	}

	return MODE_OK;
}