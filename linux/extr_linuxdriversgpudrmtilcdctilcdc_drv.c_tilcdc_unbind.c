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
struct drm_device {int /*<<< orphan*/  dev_private; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct drm_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  tilcdc_fini (struct drm_device*) ; 

__attribute__((used)) static void tilcdc_unbind(struct device *dev)
{
	struct drm_device *ddev = dev_get_drvdata(dev);

	/* Check if a subcomponent has already triggered the unloading. */
	if (!ddev->dev_private)
		return;

	tilcdc_fini(dev_get_drvdata(dev));
}