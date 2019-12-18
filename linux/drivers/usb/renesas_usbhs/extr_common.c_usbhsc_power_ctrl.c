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
struct usbhs_priv {int /*<<< orphan*/  base; } ;
struct platform_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 int /*<<< orphan*/  power_ctrl ; 
 int /*<<< orphan*/  usbhs_platform_call (struct usbhs_priv*,int /*<<< orphan*/ ,struct platform_device*,int /*<<< orphan*/ ,int) ; 
 struct device* usbhs_priv_to_dev (struct usbhs_priv*) ; 
 struct platform_device* usbhs_priv_to_pdev (struct usbhs_priv*) ; 
 int /*<<< orphan*/  usbhs_sys_clock_ctrl (struct usbhs_priv*,int) ; 
 int /*<<< orphan*/  usbhsc_clk_disable_unprepare (struct usbhs_priv*) ; 
 scalar_t__ usbhsc_clk_prepare_enable (struct usbhs_priv*) ; 

__attribute__((used)) static void usbhsc_power_ctrl(struct usbhs_priv *priv, int enable)
{
	struct platform_device *pdev = usbhs_priv_to_pdev(priv);
	struct device *dev = usbhs_priv_to_dev(priv);

	if (enable) {
		/* enable PM */
		pm_runtime_get_sync(dev);

		/* enable clks */
		if (usbhsc_clk_prepare_enable(priv))
			return;

		/* enable platform power */
		usbhs_platform_call(priv, power_ctrl, pdev, priv->base, enable);

		/* USB on */
		usbhs_sys_clock_ctrl(priv, enable);
	} else {
		/* USB off */
		usbhs_sys_clock_ctrl(priv, enable);

		/* disable platform power */
		usbhs_platform_call(priv, power_ctrl, pdev, priv->base, enable);

		/* disable clks */
		usbhsc_clk_disable_unprepare(priv);

		/* disable PM */
		pm_runtime_put_sync(dev);
	}
}