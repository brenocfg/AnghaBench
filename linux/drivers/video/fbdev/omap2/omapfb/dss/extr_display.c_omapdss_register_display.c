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
struct omap_dss_driver {int /*<<< orphan*/ * get_timings; int /*<<< orphan*/ * get_recommended_bpp; int /*<<< orphan*/ * get_resolution; } ;
struct omap_dss_device {int /*<<< orphan*/  panel_list; int /*<<< orphan*/ * alias; int /*<<< orphan*/ * name; TYPE_1__* dev; struct omap_dss_driver* driver; } ;
struct TYPE_2__ {scalar_t__ of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  disp_num_counter ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int of_alias_get_id (scalar_t__,char*) ; 
 int /*<<< orphan*/  of_property_read_string (scalar_t__,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * omapdss_default_get_recommended_bpp ; 
 int /*<<< orphan*/ * omapdss_default_get_resolution ; 
 int /*<<< orphan*/ * omapdss_default_get_timings ; 
 int /*<<< orphan*/  panel_list ; 
 int /*<<< orphan*/  panel_list_mutex ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,int,char*,int) ; 

int omapdss_register_display(struct omap_dss_device *dssdev)
{
	struct omap_dss_driver *drv = dssdev->driver;
	int id;

	/*
	 * Note: this presumes all the displays are either using DT or non-DT,
	 * which normally should be the case. This also presumes that all
	 * displays either have an DT alias, or none has.
	 */

	if (dssdev->dev->of_node) {
		id = of_alias_get_id(dssdev->dev->of_node, "display");

		if (id < 0)
			id = disp_num_counter++;
	} else {
		id = disp_num_counter++;
	}

	snprintf(dssdev->alias, sizeof(dssdev->alias), "display%d", id);

	/* Use 'label' property for name, if it exists */
	if (dssdev->dev->of_node)
		of_property_read_string(dssdev->dev->of_node, "label",
			&dssdev->name);

	if (dssdev->name == NULL)
		dssdev->name = dssdev->alias;

	if (drv && drv->get_resolution == NULL)
		drv->get_resolution = omapdss_default_get_resolution;
	if (drv && drv->get_recommended_bpp == NULL)
		drv->get_recommended_bpp = omapdss_default_get_recommended_bpp;
	if (drv && drv->get_timings == NULL)
		drv->get_timings = omapdss_default_get_timings;

	mutex_lock(&panel_list_mutex);
	list_add_tail(&dssdev->panel_list, &panel_list);
	mutex_unlock(&panel_list_mutex);
	return 0;
}