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
struct device_node {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct component_match {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_match_of ; 
 int /*<<< orphan*/  drm_of_component_match_add (struct device*,struct component_match**,int /*<<< orphan*/ ,struct device_node*) ; 
 int /*<<< orphan*/  of_device_is_compatible (struct device_node*,char*) ; 
 struct device_node* of_graph_get_remote_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

int tilcdc_get_external_components(struct device *dev,
				   struct component_match **match)
{
	struct device_node *node;

	node = of_graph_get_remote_node(dev->of_node, 0, 0);

	if (!of_device_is_compatible(node, "nxp,tda998x")) {
		of_node_put(node);
		return 0;
	}

	if (match)
		drm_of_component_match_add(dev, match, dev_match_of, node);
	of_node_put(node);
	return 1;
}