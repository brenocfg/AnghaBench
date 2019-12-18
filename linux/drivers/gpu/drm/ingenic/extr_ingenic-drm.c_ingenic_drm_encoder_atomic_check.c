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
struct drm_display_info {int num_bus_formats; int* bus_formats; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_connector_state {TYPE_1__* connector; } ;
struct TYPE_2__ {scalar_t__ connector_type; struct drm_display_info display_info; } ;

/* Variables and functions */
 scalar_t__ DRM_MODE_CONNECTOR_TV ; 
 int EINVAL ; 
#define  MEDIA_BUS_FMT_RGB565_1X16 131 
#define  MEDIA_BUS_FMT_RGB666_1X18 130 
#define  MEDIA_BUS_FMT_RGB888_1X24 129 
#define  MEDIA_BUS_FMT_RGB888_3X8 128 

__attribute__((used)) static int ingenic_drm_encoder_atomic_check(struct drm_encoder *encoder,
					    struct drm_crtc_state *crtc_state,
					    struct drm_connector_state *conn_state)
{
	struct drm_display_info *info = &conn_state->connector->display_info;

	if (info->num_bus_formats != 1)
		return -EINVAL;

	if (conn_state->connector->connector_type == DRM_MODE_CONNECTOR_TV)
		return 0;

	switch (*info->bus_formats) {
	case MEDIA_BUS_FMT_RGB565_1X16:
	case MEDIA_BUS_FMT_RGB666_1X18:
	case MEDIA_BUS_FMT_RGB888_1X24:
	case MEDIA_BUS_FMT_RGB888_3X8:
		return 0;
	default:
		return -EINVAL;
	}
}