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
struct panel_lvds {char const* label; int /*<<< orphan*/  data_mirror; TYPE_1__* dev; int /*<<< orphan*/  bus_format; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  video_mode; } ;
struct display_timing {int dummy; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {struct device_node* of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  MEDIA_BUS_FMT_RGB666_1X7X3_SPWG ; 
 int /*<<< orphan*/  MEDIA_BUS_FMT_RGB888_1X7X4_JEIDA ; 
 int /*<<< orphan*/  MEDIA_BUS_FMT_RGB888_1X7X4_SPWG ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,struct device_node*,...) ; 
 int of_get_display_timing (struct device_node*,char*,struct display_timing*) ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 
 int of_property_read_string (struct device_node*,char*,char const**) ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  videomode_from_timing (struct display_timing*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int panel_lvds_parse_dt(struct panel_lvds *lvds)
{
	struct device_node *np = lvds->dev->of_node;
	struct display_timing timing;
	const char *mapping;
	int ret;

	ret = of_get_display_timing(np, "panel-timing", &timing);
	if (ret < 0) {
		dev_err(lvds->dev, "%pOF: problems parsing panel-timing (%d)\n",
			np, ret);
		return ret;
	}

	videomode_from_timing(&timing, &lvds->video_mode);

	ret = of_property_read_u32(np, "width-mm", &lvds->width);
	if (ret < 0) {
		dev_err(lvds->dev, "%pOF: invalid or missing %s DT property\n",
			np, "width-mm");
		return -ENODEV;
	}
	ret = of_property_read_u32(np, "height-mm", &lvds->height);
	if (ret < 0) {
		dev_err(lvds->dev, "%pOF: invalid or missing %s DT property\n",
			np, "height-mm");
		return -ENODEV;
	}

	of_property_read_string(np, "label", &lvds->label);

	ret = of_property_read_string(np, "data-mapping", &mapping);
	if (ret < 0) {
		dev_err(lvds->dev, "%pOF: invalid or missing %s DT property\n",
			np, "data-mapping");
		return -ENODEV;
	}

	if (!strcmp(mapping, "jeida-18")) {
		lvds->bus_format = MEDIA_BUS_FMT_RGB666_1X7X3_SPWG;
	} else if (!strcmp(mapping, "jeida-24")) {
		lvds->bus_format = MEDIA_BUS_FMT_RGB888_1X7X4_JEIDA;
	} else if (!strcmp(mapping, "vesa-24")) {
		lvds->bus_format = MEDIA_BUS_FMT_RGB888_1X7X4_SPWG;
	} else {
		dev_err(lvds->dev, "%pOF: invalid or missing %s DT property\n",
			np, "data-mapping");
		return -EINVAL;
	}

	lvds->data_mirror = of_property_read_bool(np, "data-mirror");

	return 0;
}