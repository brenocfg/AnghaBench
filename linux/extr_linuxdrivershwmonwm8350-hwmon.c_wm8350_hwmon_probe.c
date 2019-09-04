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
struct wm8350 {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int PTR_ERR_OR_ZERO (struct device*) ; 
 struct device* devm_hwmon_device_register_with_groups (int /*<<< orphan*/ *,char*,struct wm8350*,int /*<<< orphan*/ ) ; 
 struct wm8350* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  wm8350_groups ; 

__attribute__((used)) static int wm8350_hwmon_probe(struct platform_device *pdev)
{
	struct wm8350 *wm8350 = platform_get_drvdata(pdev);
	struct device *hwmon_dev;

	hwmon_dev = devm_hwmon_device_register_with_groups(&pdev->dev, "wm8350",
							   wm8350,
							   wm8350_groups);
	return PTR_ERR_OR_ZERO(hwmon_dev);
}