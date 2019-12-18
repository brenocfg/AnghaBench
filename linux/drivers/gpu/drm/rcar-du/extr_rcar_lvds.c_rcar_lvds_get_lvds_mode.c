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
struct drm_display_info {int* bus_formats; int bus_flags; int /*<<< orphan*/  num_bus_formats; } ;
struct TYPE_2__ {struct drm_display_info display_info; } ;
struct rcar_lvds {int mode; int /*<<< orphan*/  dev; int /*<<< orphan*/  panel; TYPE_1__ connector; } ;
typedef  enum rcar_lvds_mode { ____Placeholder_rcar_lvds_mode } rcar_lvds_mode ;

/* Variables and functions */
 int DRM_BUS_FLAG_DATA_LSB_TO_MSB ; 
#define  MEDIA_BUS_FMT_RGB666_1X7X3_SPWG 130 
#define  MEDIA_BUS_FMT_RGB888_1X7X4_JEIDA 129 
#define  MEDIA_BUS_FMT_RGB888_1X7X4_SPWG 128 
 int RCAR_LVDS_MODE_JEIDA ; 
 int RCAR_LVDS_MODE_MIRROR ; 
 int RCAR_LVDS_MODE_VESA ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void rcar_lvds_get_lvds_mode(struct rcar_lvds *lvds)
{
	struct drm_display_info *info = &lvds->connector.display_info;
	enum rcar_lvds_mode mode;

	/*
	 * There is no API yet to retrieve LVDS mode from a bridge, only panels
	 * are supported.
	 */
	if (!lvds->panel)
		return;

	if (!info->num_bus_formats || !info->bus_formats) {
		dev_err(lvds->dev, "no LVDS bus format reported\n");
		return;
	}

	switch (info->bus_formats[0]) {
	case MEDIA_BUS_FMT_RGB666_1X7X3_SPWG:
	case MEDIA_BUS_FMT_RGB888_1X7X4_JEIDA:
		mode = RCAR_LVDS_MODE_JEIDA;
		break;
	case MEDIA_BUS_FMT_RGB888_1X7X4_SPWG:
		mode = RCAR_LVDS_MODE_VESA;
		break;
	default:
		dev_err(lvds->dev, "unsupported LVDS bus format 0x%04x\n",
			info->bus_formats[0]);
		return;
	}

	if (info->bus_flags & DRM_BUS_FLAG_DATA_LSB_TO_MSB)
		mode |= RCAR_LVDS_MODE_MIRROR;

	lvds->mode = mode;
}