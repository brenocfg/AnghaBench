#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u64 ;
struct TYPE_4__ {size_t hpos; size_t vpos; size_t sharpness; size_t flicker_filter; size_t flicker_filter_2d; size_t flicker_filter_adaptive; size_t chroma_filter; size_t luma_filter; size_t dot_crawl; scalar_t__ overscan_h; scalar_t__ overscan_v; } ;
struct intel_sdvo_connector_state {TYPE_2__ tv; } ;
struct intel_sdvo_connector {struct drm_property* dot_crawl; struct drm_property* tv_luma_filter; struct drm_property* tv_chroma_filter; struct drm_property* flicker_filter_adaptive; struct drm_property* flicker_filter_2d; struct drm_property* flicker_filter; struct drm_property* sharpness; struct drm_property* brightness; struct drm_property* hue; struct drm_property* contrast; struct drm_property* saturation; struct drm_property* vpos; struct drm_property* hpos; scalar_t__ max_hscan; struct drm_property* right; struct drm_property* left; scalar_t__ max_vscan; struct drm_property* bottom; struct drm_property* top; int /*<<< orphan*/ * tv_format_supported; struct drm_property* tv_format; } ;
struct drm_property {int dummy; } ;
struct drm_crtc_state {int connectors_changed; } ;
struct TYPE_3__ {size_t saturation; size_t contrast; size_t hue; size_t brightness; int /*<<< orphan*/  mode; } ;
struct drm_connector_state {TYPE_1__ tv; scalar_t__ crtc; int /*<<< orphan*/  state; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 struct drm_crtc_state* drm_atomic_get_new_crtc_state (int /*<<< orphan*/ ,scalar_t__) ; 
 int intel_digital_connector_atomic_set_property (struct drm_connector*,struct drm_connector_state*,struct drm_property*,size_t) ; 
 struct intel_sdvo_connector* to_intel_sdvo_connector (struct drm_connector*) ; 
 struct intel_sdvo_connector_state* to_intel_sdvo_connector_state (struct drm_connector_state*) ; 

__attribute__((used)) static int
intel_sdvo_connector_atomic_set_property(struct drm_connector *connector,
					 struct drm_connector_state *state,
					 struct drm_property *property,
					 u64 val)
{
	struct intel_sdvo_connector *intel_sdvo_connector = to_intel_sdvo_connector(connector);
	struct intel_sdvo_connector_state *sdvo_state = to_intel_sdvo_connector_state(state);

	if (property == intel_sdvo_connector->tv_format) {
		state->tv.mode = intel_sdvo_connector->tv_format_supported[val];

		if (state->crtc) {
			struct drm_crtc_state *crtc_state =
				drm_atomic_get_new_crtc_state(state->state, state->crtc);

			crtc_state->connectors_changed = true;
		}
	} else if (property == intel_sdvo_connector->top ||
		   property == intel_sdvo_connector->bottom)
		/* Cannot set these independent from each other */
		sdvo_state->tv.overscan_v = intel_sdvo_connector->max_vscan - val;
	else if (property == intel_sdvo_connector->left ||
		 property == intel_sdvo_connector->right)
		/* Cannot set these independent from each other */
		sdvo_state->tv.overscan_h = intel_sdvo_connector->max_hscan - val;
	else if (property == intel_sdvo_connector->hpos)
		sdvo_state->tv.hpos = val;
	else if (property == intel_sdvo_connector->vpos)
		sdvo_state->tv.vpos = val;
	else if (property == intel_sdvo_connector->saturation)
		state->tv.saturation = val;
	else if (property == intel_sdvo_connector->contrast)
		state->tv.contrast = val;
	else if (property == intel_sdvo_connector->hue)
		state->tv.hue = val;
	else if (property == intel_sdvo_connector->brightness)
		state->tv.brightness = val;
	else if (property == intel_sdvo_connector->sharpness)
		sdvo_state->tv.sharpness = val;
	else if (property == intel_sdvo_connector->flicker_filter)
		sdvo_state->tv.flicker_filter = val;
	else if (property == intel_sdvo_connector->flicker_filter_2d)
		sdvo_state->tv.flicker_filter_2d = val;
	else if (property == intel_sdvo_connector->flicker_filter_adaptive)
		sdvo_state->tv.flicker_filter_adaptive = val;
	else if (property == intel_sdvo_connector->tv_chroma_filter)
		sdvo_state->tv.chroma_filter = val;
	else if (property == intel_sdvo_connector->tv_luma_filter)
		sdvo_state->tv.luma_filter = val;
	else if (property == intel_sdvo_connector->dot_crawl)
		sdvo_state->tv.dot_crawl = val;
	else
		return intel_digital_connector_atomic_set_property(connector, state, property, val);

	return 0;
}