#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int platform_get_irq (struct platform_device*,int) ; 
 int platform_get_irq_byname (struct platform_device*,char const*) ; 

__attribute__((used)) static int dwc3_qcom_get_irq(struct platform_device *pdev,
			     const char *name, int num)
{
	struct device_node *np = pdev->dev.of_node;
	int ret;

	if (np)
		ret = platform_get_irq_byname(pdev, name);
	else
		ret = platform_get_irq(pdev, num);

	return ret;
}