#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;
struct component_match {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int component_master_add_with_match (TYPE_1__*,int /*<<< orphan*/ *,struct component_match*) ; 
 int /*<<< orphan*/  drm_of_component_match_add (TYPE_1__*,struct component_match**,int /*<<< orphan*/ ,struct device_node*) ; 
 int /*<<< orphan*/  malidp_compare_dev ; 
 int /*<<< orphan*/  malidp_master_ops ; 
 struct device_node* of_graph_get_remote_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static int malidp_platform_probe(struct platform_device *pdev)
{
	struct device_node *port;
	struct component_match *match = NULL;

	if (!pdev->dev.of_node)
		return -ENODEV;

	/* there is only one output port inside each device, find it */
	port = of_graph_get_remote_node(pdev->dev.of_node, 0, 0);
	if (!port)
		return -ENODEV;

	drm_of_component_match_add(&pdev->dev, &match, malidp_compare_dev,
				   port);
	of_node_put(port);
	return component_master_add_with_match(&pdev->dev, &malidp_master_ops,
					       match);
}