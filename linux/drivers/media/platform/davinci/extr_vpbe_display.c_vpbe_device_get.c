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
struct vpbe_display {void* osd_device; void* vpbe_dev; } ;
struct platform_device {int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 void* platform_get_drvdata (struct platform_device*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strstr (int /*<<< orphan*/ ,char*) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int vpbe_device_get(struct device *dev, void *data)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct vpbe_display *vpbe_disp  = data;

	if (strcmp("vpbe_controller", pdev->name) == 0)
		vpbe_disp->vpbe_dev = platform_get_drvdata(pdev);

	if (strstr(pdev->name, "vpbe-osd"))
		vpbe_disp->osd_device = platform_get_drvdata(pdev);

	return 0;
}