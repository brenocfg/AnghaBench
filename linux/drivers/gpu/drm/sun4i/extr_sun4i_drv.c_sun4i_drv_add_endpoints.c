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
struct endpoint_list {int dummy; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
struct component_match {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,struct device_node*) ; 
 int /*<<< orphan*/  compare_of ; 
 int /*<<< orphan*/  drm_of_component_match_add (struct device*,struct component_match**,int /*<<< orphan*/ ,struct device_node*) ; 
 scalar_t__ of_device_is_available (struct device_node*) ; 
 scalar_t__ sun4i_drv_node_is_connector (struct device_node*) ; 
 scalar_t__ sun4i_drv_node_is_deu (struct device_node*) ; 
 scalar_t__ sun4i_drv_node_is_frontend (struct device_node*) ; 
 scalar_t__ sun4i_drv_node_is_supported_frontend (struct device_node*) ; 
 scalar_t__ sun4i_drv_node_is_tcon_top (struct device_node*) ; 
 int /*<<< orphan*/  sun4i_drv_traverse_endpoints (struct endpoint_list*,struct device_node*,int) ; 

__attribute__((used)) static int sun4i_drv_add_endpoints(struct device *dev,
				   struct endpoint_list *list,
				   struct component_match **match,
				   struct device_node *node)
{
	int count = 0;

	/*
	 * The frontend has been disabled in some of our old device
	 * trees. If we find a node that is the frontend and is
	 * disabled, we should just follow through and parse its
	 * child, but without adding it to the component list.
	 * Otherwise, we obviously want to add it to the list.
	 */
	if (!sun4i_drv_node_is_frontend(node) &&
	    !of_device_is_available(node))
		return 0;

	/*
	 * The connectors will be the last nodes in our pipeline, we
	 * can just bail out.
	 */
	if (sun4i_drv_node_is_connector(node))
		return 0;

	/*
	 * If the device is either just a regular device, or an
	 * enabled frontend supported by the driver, we add it to our
	 * component list.
	 */
	if (!(sun4i_drv_node_is_frontend(node) ||
	      sun4i_drv_node_is_deu(node)) ||
	    (sun4i_drv_node_is_supported_frontend(node) &&
	     of_device_is_available(node))) {
		/* Add current component */
		DRM_DEBUG_DRIVER("Adding component %pOF\n", node);
		drm_of_component_match_add(dev, match, compare_of, node);
		count++;
	}

	/* each node has at least one output */
	sun4i_drv_traverse_endpoints(list, node, 1);

	/* TCON TOP has second and third output */
	if (sun4i_drv_node_is_tcon_top(node)) {
		sun4i_drv_traverse_endpoints(list, node, 3);
		sun4i_drv_traverse_endpoints(list, node, 5);
	}

	return count;
}