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
struct wm831x {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int PTR_ERR_OR_ZERO (struct device*) ; 
 struct wm831x* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct device* devm_hwmon_device_register_with_groups (TYPE_1__*,char*,struct wm831x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm831x_groups ; 

__attribute__((used)) static int wm831x_hwmon_probe(struct platform_device *pdev)
{
	struct wm831x *wm831x = dev_get_drvdata(pdev->dev.parent);
	struct device *hwmon_dev;

	hwmon_dev = devm_hwmon_device_register_with_groups(&pdev->dev, "wm831x",
							   wm831x,
							   wm831x_groups);
	return PTR_ERR_OR_ZERO(hwmon_dev);
}