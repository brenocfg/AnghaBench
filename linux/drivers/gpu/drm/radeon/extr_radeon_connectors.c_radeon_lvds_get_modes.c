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
struct drm_encoder {int dummy; } ;
struct drm_display_mode {int /*<<< orphan*/  height_mm; int /*<<< orphan*/  width_mm; } ;
struct TYPE_2__ {int /*<<< orphan*/  height_mm; int /*<<< orphan*/  width_mm; } ;
struct drm_connector {TYPE_1__ display_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  radeon_add_common_modes (struct drm_encoder*,struct drm_connector*) ; 
 struct drm_encoder* radeon_best_single_encoder (struct drm_connector*) ; 
 int /*<<< orphan*/  radeon_connector_get_edid (struct drm_connector*) ; 
 int radeon_ddc_get_modes (struct drm_connector*) ; 
 int /*<<< orphan*/  radeon_fixup_lvds_native_mode (struct drm_encoder*,struct drm_connector*) ; 
 struct drm_display_mode* radeon_fp_native_mode (struct drm_encoder*) ; 

__attribute__((used)) static int radeon_lvds_get_modes(struct drm_connector *connector)
{
	struct drm_encoder *encoder;
	int ret = 0;
	struct drm_display_mode *mode;

	radeon_connector_get_edid(connector);
	ret = radeon_ddc_get_modes(connector);
	if (ret > 0) {
		encoder = radeon_best_single_encoder(connector);
		if (encoder) {
			radeon_fixup_lvds_native_mode(encoder, connector);
			/* add scaled modes */
			radeon_add_common_modes(encoder, connector);
		}
		return ret;
	}

	encoder = radeon_best_single_encoder(connector);
	if (!encoder)
		return 0;

	/* we have no EDID modes */
	mode = radeon_fp_native_mode(encoder);
	if (mode) {
		ret = 1;
		drm_mode_probed_add(connector, mode);
		/* add the width/height from vbios tables if available */
		connector->display_info.width_mm = mode->width_mm;
		connector->display_info.height_mm = mode->height_mm;
		/* add scaled modes */
		radeon_add_common_modes(encoder, connector);
	}

	return ret;
}