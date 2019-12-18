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
struct platform_device {int dummy; } ;
struct dss_device {struct platform_device* drm_pdev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct platform_device*) ; 
 int PTR_ERR (struct platform_device*) ; 
 int component_bind_all (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  component_unbind_all (struct device*,int /*<<< orphan*/ *) ; 
 struct dss_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  omapdss_set_dss (struct dss_device*) ; 
 struct platform_device* platform_device_register_simple (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_set_vt_switch (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dss_bind(struct device *dev)
{
	struct dss_device *dss = dev_get_drvdata(dev);
	struct platform_device *drm_pdev;
	int r;

	r = component_bind_all(dev, NULL);
	if (r)
		return r;

	pm_set_vt_switch(0);

	omapdss_set_dss(dss);

	drm_pdev = platform_device_register_simple("omapdrm", 0, NULL, 0);
	if (IS_ERR(drm_pdev)) {
		component_unbind_all(dev, NULL);
		return PTR_ERR(drm_pdev);
	}

	dss->drm_pdev = drm_pdev;

	return 0;
}