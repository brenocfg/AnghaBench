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
struct rockchip_crtc_state {int /*<<< orphan*/  output_type; int /*<<< orphan*/  output_mode; } ;
struct drm_encoder {int dummy; } ;
struct drm_display_info {int* bus_formats; scalar_t__ num_bus_formats; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_connector_state {struct drm_connector* connector; } ;
struct drm_connector {struct drm_display_info display_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_LVDS ; 
#define  MEDIA_BUS_FMT_RGB565_1X16 131 
#define  MEDIA_BUS_FMT_RGB666_1X18 130 
#define  MEDIA_BUS_FMT_RGB666_1X24_CPADHI 129 
#define  MEDIA_BUS_FMT_RGB888_1X24 128 
 int /*<<< orphan*/  ROCKCHIP_OUT_MODE_P565 ; 
 int /*<<< orphan*/  ROCKCHIP_OUT_MODE_P666 ; 
 int /*<<< orphan*/  ROCKCHIP_OUT_MODE_P888 ; 
 struct rockchip_crtc_state* to_rockchip_crtc_state (struct drm_crtc_state*) ; 

__attribute__((used)) static int
rockchip_rgb_encoder_atomic_check(struct drm_encoder *encoder,
				   struct drm_crtc_state *crtc_state,
				   struct drm_connector_state *conn_state)
{
	struct rockchip_crtc_state *s = to_rockchip_crtc_state(crtc_state);
	struct drm_connector *connector = conn_state->connector;
	struct drm_display_info *info = &connector->display_info;
	u32 bus_format;

	if (info->num_bus_formats)
		bus_format = info->bus_formats[0];
	else
		bus_format = MEDIA_BUS_FMT_RGB888_1X24;

	switch (bus_format) {
	case MEDIA_BUS_FMT_RGB666_1X18:
		s->output_mode = ROCKCHIP_OUT_MODE_P666;
		break;
	case MEDIA_BUS_FMT_RGB565_1X16:
		s->output_mode = ROCKCHIP_OUT_MODE_P565;
		break;
	case MEDIA_BUS_FMT_RGB888_1X24:
	case MEDIA_BUS_FMT_RGB666_1X24_CPADHI:
	default:
		s->output_mode = ROCKCHIP_OUT_MODE_P888;
		break;
	}

	s->output_type = DRM_MODE_CONNECTOR_LVDS;

	return 0;
}