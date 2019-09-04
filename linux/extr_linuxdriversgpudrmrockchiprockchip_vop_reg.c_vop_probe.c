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
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*) ; 
 int ENODEV ; 
 int component_add (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vop_component_ops ; 

__attribute__((used)) static int vop_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;

	if (!dev->of_node) {
		DRM_DEV_ERROR(dev, "can't find vop devices\n");
		return -ENODEV;
	}

	return component_add(dev, &vop_component_ops);
}