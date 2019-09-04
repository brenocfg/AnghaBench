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
struct panel_drv_data {int pd_gpio; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 scalar_t__ gpio_is_valid (int) ; 
 int of_get_named_gpio (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 struct panel_drv_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int tfp410_probe_of(struct platform_device *pdev)
{
	struct panel_drv_data *ddata = platform_get_drvdata(pdev);
	struct device_node *node = pdev->dev.of_node;
	int gpio;

	gpio = of_get_named_gpio(node, "powerdown-gpios", 0);

	if (gpio_is_valid(gpio) || gpio == -ENOENT) {
		ddata->pd_gpio = gpio;
	} else {
		if (gpio != -EPROBE_DEFER)
			dev_err(&pdev->dev, "failed to parse PD gpio\n");
		return gpio;
	}

	return 0;
}