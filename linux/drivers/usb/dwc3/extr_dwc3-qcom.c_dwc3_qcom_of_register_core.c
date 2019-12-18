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
struct dwc3_qcom {int /*<<< orphan*/  dwc3; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  of_find_device_by_node (struct device_node*) ; 
 struct device_node* of_get_child_by_name (struct device_node*,char*) ; 
 int of_platform_populate (struct device_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct device*) ; 
 struct dwc3_qcom* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int dwc3_qcom_of_register_core(struct platform_device *pdev)
{
	struct dwc3_qcom 	*qcom = platform_get_drvdata(pdev);
	struct device_node	*np = pdev->dev.of_node, *dwc3_np;
	struct device		*dev = &pdev->dev;
	int			ret;

	dwc3_np = of_get_child_by_name(np, "dwc3");
	if (!dwc3_np) {
		dev_err(dev, "failed to find dwc3 core child\n");
		return -ENODEV;
	}

	ret = of_platform_populate(np, NULL, NULL, dev);
	if (ret) {
		dev_err(dev, "failed to register dwc3 core - %d\n", ret);
		return ret;
	}

	qcom->dwc3 = of_find_device_by_node(dwc3_np);
	if (!qcom->dwc3) {
		dev_err(dev, "failed to get dwc3 platform device\n");
		return -ENODEV;
	}

	return 0;
}