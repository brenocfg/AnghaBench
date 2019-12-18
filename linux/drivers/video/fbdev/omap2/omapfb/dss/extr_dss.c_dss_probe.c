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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct component_match {int dummy; } ;

/* Variables and functions */
 int component_master_add_with_match (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct component_match*) ; 
 int /*<<< orphan*/  device_for_each_child (int /*<<< orphan*/ *,struct component_match**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dss_add_child_component ; 
 int /*<<< orphan*/  dss_component_ops ; 

__attribute__((used)) static int dss_probe(struct platform_device *pdev)
{
	struct component_match *match = NULL;
	int r;

	/* add all the child devices as components */
	device_for_each_child(&pdev->dev, &match, dss_add_child_component);

	r = component_master_add_with_match(&pdev->dev, &dss_component_ops, match);
	if (r)
		return r;

	return 0;
}