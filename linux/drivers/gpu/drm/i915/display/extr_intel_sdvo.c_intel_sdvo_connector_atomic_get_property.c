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
typedef  int u64 ;
struct TYPE_4__ {int overscan_v; int overscan_h; int hpos; int vpos; int sharpness; int flicker_filter; int flicker_filter_2d; int flicker_filter_adaptive; int chroma_filter; int luma_filter; int dot_crawl; } ;
struct intel_sdvo_connector_state {TYPE_2__ tv; } ;
struct intel_sdvo_connector {int format_supported_num; scalar_t__* tv_format_supported; int max_vscan; int max_hscan; struct drm_property* dot_crawl; struct drm_property* tv_luma_filter; struct drm_property* tv_chroma_filter; struct drm_property* flicker_filter_adaptive; struct drm_property* flicker_filter_2d; struct drm_property* flicker_filter; struct drm_property* sharpness; struct drm_property* brightness; struct drm_property* hue; struct drm_property* contrast; struct drm_property* saturation; struct drm_property* vpos; struct drm_property* hpos; struct drm_property* right; struct drm_property* left; struct drm_property* bottom; struct drm_property* top; struct drm_property* tv_format; } ;
struct drm_property {int dummy; } ;
struct TYPE_3__ {scalar_t__ mode; int saturation; int contrast; int hue; int brightness; } ;
struct drm_connector_state {TYPE_1__ tv; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int intel_digital_connector_atomic_get_property (struct drm_connector*,struct drm_connector_state const*,struct drm_property*,int*) ; 
 struct intel_sdvo_connector* to_intel_sdvo_connector (struct drm_connector*) ; 
 struct intel_sdvo_connector_state* to_intel_sdvo_connector_state (void*) ; 

__attribute__((used)) static int
intel_sdvo_connector_atomic_get_property(struct drm_connector *connector,
					 const struct drm_connector_state *state,
					 struct drm_property *property,
					 u64 *val)
{
	struct intel_sdvo_connector *intel_sdvo_connector = to_intel_sdvo_connector(connector);
	const struct intel_sdvo_connector_state *sdvo_state = to_intel_sdvo_connector_state((void *)state);

	if (property == intel_sdvo_connector->tv_format) {
		int i;

		for (i = 0; i < intel_sdvo_connector->format_supported_num; i++)
			if (state->tv.mode == intel_sdvo_connector->tv_format_supported[i]) {
				*val = i;

				return 0;
			}

		WARN_ON(1);
		*val = 0;
	} else if (property == intel_sdvo_connector->top ||
		   property == intel_sdvo_connector->bottom)
		*val = intel_sdvo_connector->max_vscan - sdvo_state->tv.overscan_v;
	else if (property == intel_sdvo_connector->left ||
		 property == intel_sdvo_connector->right)
		*val = intel_sdvo_connector->max_hscan - sdvo_state->tv.overscan_h;
	else if (property == intel_sdvo_connector->hpos)
		*val = sdvo_state->tv.hpos;
	else if (property == intel_sdvo_connector->vpos)
		*val = sdvo_state->tv.vpos;
	else if (property == intel_sdvo_connector->saturation)
		*val = state->tv.saturation;
	else if (property == intel_sdvo_connector->contrast)
		*val = state->tv.contrast;
	else if (property == intel_sdvo_connector->hue)
		*val = state->tv.hue;
	else if (property == intel_sdvo_connector->brightness)
		*val = state->tv.brightness;
	else if (property == intel_sdvo_connector->sharpness)
		*val = sdvo_state->tv.sharpness;
	else if (property == intel_sdvo_connector->flicker_filter)
		*val = sdvo_state->tv.flicker_filter;
	else if (property == intel_sdvo_connector->flicker_filter_2d)
		*val = sdvo_state->tv.flicker_filter_2d;
	else if (property == intel_sdvo_connector->flicker_filter_adaptive)
		*val = sdvo_state->tv.flicker_filter_adaptive;
	else if (property == intel_sdvo_connector->tv_chroma_filter)
		*val = sdvo_state->tv.chroma_filter;
	else if (property == intel_sdvo_connector->tv_luma_filter)
		*val = sdvo_state->tv.luma_filter;
	else if (property == intel_sdvo_connector->dot_crawl)
		*val = sdvo_state->tv.dot_crawl;
	else
		return intel_digital_connector_atomic_get_property(connector, state, property, val);

	return 0;
}