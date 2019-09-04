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
struct vpbe_device {int /*<<< orphan*/  venc_device; int /*<<< orphan*/  osd_device; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_get_drvdata (struct platform_device*) ; 
 scalar_t__ strstr (int /*<<< orphan*/ ,char*) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int platform_device_get(struct device *dev, void *data)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct vpbe_device *vpbe_dev = data;

	if (strstr(pdev->name, "vpbe-osd"))
		vpbe_dev->osd_device = platform_get_drvdata(pdev);
	if (strstr(pdev->name, "vpbe-venc"))
		vpbe_dev->venc_device = dev_get_platdata(&pdev->dev);

	return 0;
}