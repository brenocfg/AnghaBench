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
struct drm_display_info {int num_bus_formats; int* bus_formats; } ;
struct drm_connector {struct drm_display_info display_info; } ;

/* Variables and functions */
 int EINVAL ; 
#define  MEDIA_BUS_FMT_RGB666_1X7X3_SPWG 130 
#define  MEDIA_BUS_FMT_RGB888_1X7X4_JEIDA 129 
#define  MEDIA_BUS_FMT_RGB888_1X7X4_SPWG 128 
 struct drm_connector* sun4i_tcon_get_connector (struct drm_encoder const*) ; 

__attribute__((used)) static int sun4i_tcon_get_pixel_depth(const struct drm_encoder *encoder)
{
	struct drm_connector *connector;
	struct drm_display_info *info;

	connector = sun4i_tcon_get_connector(encoder);
	if (!connector)
		return -EINVAL;

	info = &connector->display_info;
	if (info->num_bus_formats != 1)
		return -EINVAL;

	switch (info->bus_formats[0]) {
	case MEDIA_BUS_FMT_RGB666_1X7X3_SPWG:
		return 18;

	case MEDIA_BUS_FMT_RGB888_1X7X4_JEIDA:
	case MEDIA_BUS_FMT_RGB888_1X7X4_SPWG:
		return 24;
	}

	return -EINVAL;
}