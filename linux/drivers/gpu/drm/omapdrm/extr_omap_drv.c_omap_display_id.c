#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct omap_dss_device {TYPE_2__* panel; struct drm_bridge* bridge; TYPE_3__* dev; scalar_t__ next; } ;
struct drm_bridge {struct device_node* of_node; struct drm_bridge* next; } ;
struct device_node {int dummy; } ;
struct TYPE_6__ {struct device_node* of_node; } ;
struct TYPE_5__ {TYPE_1__* dev; } ;
struct TYPE_4__ {struct device_node* of_node; } ;

/* Variables and functions */
 int ENODEV ; 
 int of_alias_get_id (struct device_node*,char*) ; 
 int /*<<< orphan*/  omapdss_device_put (struct omap_dss_device*) ; 
 struct omap_dss_device* omapdss_display_get (struct omap_dss_device*) ; 

__attribute__((used)) static int omap_display_id(struct omap_dss_device *output)
{
	struct device_node *node = NULL;

	if (output->next) {
		struct omap_dss_device *display;

		display = omapdss_display_get(output);
		node = display->dev->of_node;
		omapdss_device_put(display);
	} else if (output->bridge) {
		struct drm_bridge *bridge = output->bridge;

		while (bridge->next)
			bridge = bridge->next;

		node = bridge->of_node;
	} else if (output->panel) {
		node = output->panel->dev->of_node;
	}

	return node ? of_alias_get_id(node, "display") : -ENODEV;
}