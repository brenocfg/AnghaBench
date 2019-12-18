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
struct dss_device {int /*<<< orphan*/  drm_pdev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  component_unbind_all (struct device*,int /*<<< orphan*/ *) ; 
 struct dss_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  omapdss_set_dss (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dss_unbind(struct device *dev)
{
	struct dss_device *dss = dev_get_drvdata(dev);

	platform_device_unregister(dss->drm_pdev);

	omapdss_set_dss(NULL);

	component_unbind_all(dev, NULL);
}