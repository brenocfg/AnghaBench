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
struct arche_apb_ctrl_drvdata {int init_disabled; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHE_PLATFORM_STATE_OFF ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int apb_ctrl_get_devtree_data (struct platform_device*,struct arche_apb_ctrl_drvdata*) ; 
 int /*<<< orphan*/  dev_attr_state ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int device_create_file (struct device*,int /*<<< orphan*/ *) ; 
 struct arche_apb_ctrl_drvdata* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct arche_apb_ctrl_drvdata*) ; 

__attribute__((used)) static int arche_apb_ctrl_probe(struct platform_device *pdev)
{
	int ret;
	struct arche_apb_ctrl_drvdata *apb;
	struct device *dev = &pdev->dev;

	apb = devm_kzalloc(&pdev->dev, sizeof(*apb), GFP_KERNEL);
	if (!apb)
		return -ENOMEM;

	ret = apb_ctrl_get_devtree_data(pdev, apb);
	if (ret) {
		dev_err(dev, "failed to get apb devicetree data %d\n", ret);
		return ret;
	}

	/* Initially set APB to OFF state */
	apb->state = ARCHE_PLATFORM_STATE_OFF;
	/* Check whether device needs to be enabled on boot */
	if (of_property_read_bool(pdev->dev.of_node, "arche,init-disable"))
		apb->init_disabled = true;

	platform_set_drvdata(pdev, apb);

	/* Create sysfs interface to allow user to change state dynamically */
	ret = device_create_file(dev, &dev_attr_state);
	if (ret) {
		dev_err(dev, "failed to create state file in sysfs\n");
		return ret;
	}

	dev_info(&pdev->dev, "Device registered successfully\n");
	return 0;
}