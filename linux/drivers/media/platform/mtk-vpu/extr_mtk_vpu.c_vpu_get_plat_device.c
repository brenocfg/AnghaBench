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
struct device_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

struct platform_device *vpu_get_plat_device(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *vpu_node;
	struct platform_device *vpu_pdev;

	vpu_node = of_parse_phandle(dev->of_node, "mediatek,vpu", 0);
	if (!vpu_node) {
		dev_err(dev, "can't get vpu node\n");
		return NULL;
	}

	vpu_pdev = of_find_device_by_node(vpu_node);
	of_node_put(vpu_node);
	if (WARN_ON(!vpu_pdev)) {
		dev_err(dev, "vpu pdev failed\n");
		return NULL;
	}

	return vpu_pdev;
}