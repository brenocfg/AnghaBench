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
struct omap_dss_device {TYPE_1__* dev; int /*<<< orphan*/ * name; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * devm_kasprintf (TYPE_1__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  disp_num_counter ; 
 int of_alias_get_id (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  of_property_read_string (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ **) ; 

void omapdss_display_init(struct omap_dss_device *dssdev)
{
	int id;

	/*
	 * Note: this presumes that all displays either have an DT alias, or
	 * none has.
	 */
	id = of_alias_get_id(dssdev->dev->of_node, "display");
	if (id < 0)
		id = disp_num_counter++;

	/* Use 'label' property for name, if it exists */
	of_property_read_string(dssdev->dev->of_node, "label", &dssdev->name);

	if (dssdev->name == NULL)
		dssdev->name = devm_kasprintf(dssdev->dev, GFP_KERNEL,
					      "display%u", id);
}