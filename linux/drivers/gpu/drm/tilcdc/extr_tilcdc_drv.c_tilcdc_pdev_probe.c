#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct component_match {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int component_master_add_with_match (TYPE_1__*,int /*<<< orphan*/ *,struct component_match*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  tilcdc_comp_ops ; 
 int /*<<< orphan*/  tilcdc_driver ; 
 int tilcdc_get_external_components (TYPE_1__*,struct component_match**) ; 
 int tilcdc_init (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int tilcdc_pdev_probe(struct platform_device *pdev)
{
	struct component_match *match = NULL;
	int ret;

	/* bail out early if no DT data: */
	if (!pdev->dev.of_node) {
		dev_err(&pdev->dev, "device-tree data is missing\n");
		return -ENXIO;
	}

	ret = tilcdc_get_external_components(&pdev->dev, &match);
	if (ret < 0)
		return ret;
	else if (ret == 0)
		return tilcdc_init(&tilcdc_driver, &pdev->dev);
	else
		return component_master_add_with_match(&pdev->dev,
						       &tilcdc_comp_ops,
						       match);
}