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
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;
struct component_match {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  compare_of ; 
 int component_master_add_with_match (struct device*,int /*<<< orphan*/ *,struct component_match*) ; 
 int /*<<< orphan*/  drm_of_component_match_add (struct device*,struct component_match**,int /*<<< orphan*/ ,struct device_node*) ; 
 int /*<<< orphan*/  kirin_drm_ops ; 
 struct device_node* of_graph_get_remote_node (struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static int kirin_drm_platform_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct component_match *match = NULL;
	struct device_node *remote;

	remote = of_graph_get_remote_node(np, 0, 0);
	if (!remote)
		return -ENODEV;

	drm_of_component_match_add(dev, &match, compare_of, remote);
	of_node_put(remote);

	return component_master_add_with_match(dev, &kirin_drm_ops, match);
}