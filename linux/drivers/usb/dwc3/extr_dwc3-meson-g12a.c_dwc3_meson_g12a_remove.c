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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct dwc3_meson_g12a {int /*<<< orphan*/ * phys; int /*<<< orphan*/  role_switch; } ;

/* Variables and functions */
 int PHY_COUNT ; 
 int /*<<< orphan*/  of_platform_depopulate (struct device*) ; 
 int /*<<< orphan*/  phy_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_power_off (int /*<<< orphan*/ ) ; 
 struct dwc3_meson_g12a* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (struct device*) ; 
 int /*<<< orphan*/  usb_role_switch_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dwc3_meson_g12a_remove(struct platform_device *pdev)
{
	struct dwc3_meson_g12a *priv = platform_get_drvdata(pdev);
	struct device *dev = &pdev->dev;
	int i;

	usb_role_switch_unregister(priv->role_switch);

	of_platform_depopulate(dev);

	for (i = 0 ; i < PHY_COUNT ; ++i) {
		phy_power_off(priv->phys[i]);
		phy_exit(priv->phys[i]);
	}

	pm_runtime_disable(dev);
	pm_runtime_put_noidle(dev);
	pm_runtime_set_suspended(dev);

	return 0;
}