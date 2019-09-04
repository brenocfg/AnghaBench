#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int const uint64_t ;
struct TYPE_8__ {scalar_t__ hdisplay; scalar_t__ vdisplay; } ;
struct gma_crtc {int /*<<< orphan*/  saved_adjusted_mode; TYPE_3__ saved_mode; } ;
struct drm_property {int /*<<< orphan*/  name; } ;
struct drm_encoder_helper_funcs {int /*<<< orphan*/  (* mode_set ) (struct drm_encoder*,TYPE_3__*,int /*<<< orphan*/ *) ;} ;
struct drm_encoder {int /*<<< orphan*/  dev; struct drm_encoder_helper_funcs* helper_private; TYPE_2__* crtc; } ;
struct drm_connector {int /*<<< orphan*/  base; struct drm_encoder* encoder; } ;
struct TYPE_7__ {TYPE_1__* primary; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_6__ {int /*<<< orphan*/  fb; } ;

/* Variables and functions */
#define  DRM_MODE_SCALE_ASPECT 130 
#define  DRM_MODE_SCALE_FULLSCREEN 129 
#define  DRM_MODE_SCALE_NO_SCALE 128 
 int /*<<< orphan*/  drm_crtc_helper_set_mode (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ drm_object_property_get_value (int /*<<< orphan*/ *,struct drm_property*,int const*) ; 
 scalar_t__ drm_object_property_set_value (int /*<<< orphan*/ *,struct drm_property*,int const) ; 
 int /*<<< orphan*/  gma_backlight_set (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (struct drm_encoder*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 struct gma_crtc* to_gma_crtc (TYPE_2__*) ; 

__attribute__((used)) static int mdfld_dsi_connector_set_property(struct drm_connector *connector,
				struct drm_property *property,
				uint64_t value)
{
	struct drm_encoder *encoder = connector->encoder;

	if (!strcmp(property->name, "scaling mode") && encoder) {
		struct gma_crtc *gma_crtc = to_gma_crtc(encoder->crtc);
		bool centerechange;
		uint64_t val;

		if (!gma_crtc)
			goto set_prop_error;

		switch (value) {
		case DRM_MODE_SCALE_FULLSCREEN:
			break;
		case DRM_MODE_SCALE_NO_SCALE:
			break;
		case DRM_MODE_SCALE_ASPECT:
			break;
		default:
			goto set_prop_error;
		}

		if (drm_object_property_get_value(&connector->base, property, &val))
			goto set_prop_error;

		if (val == value)
			goto set_prop_done;

		if (drm_object_property_set_value(&connector->base,
							property, value))
			goto set_prop_error;

		centerechange = (val == DRM_MODE_SCALE_NO_SCALE) ||
			(value == DRM_MODE_SCALE_NO_SCALE);

		if (gma_crtc->saved_mode.hdisplay != 0 &&
		    gma_crtc->saved_mode.vdisplay != 0) {
			if (centerechange) {
				if (!drm_crtc_helper_set_mode(encoder->crtc,
						&gma_crtc->saved_mode,
						encoder->crtc->x,
						encoder->crtc->y,
						encoder->crtc->primary->fb))
					goto set_prop_error;
			} else {
				const struct drm_encoder_helper_funcs *funcs =
						encoder->helper_private;
				funcs->mode_set(encoder,
					&gma_crtc->saved_mode,
					&gma_crtc->saved_adjusted_mode);
			}
		}
	} else if (!strcmp(property->name, "backlight") && encoder) {
		if (drm_object_property_set_value(&connector->base, property,
									value))
			goto set_prop_error;
		else
			gma_backlight_set(encoder->dev, value);
	}
set_prop_done:
	return 0;
set_prop_error:
	return -1;
}