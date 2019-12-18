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
struct usbhs_priv {int /*<<< orphan*/  rsts; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hardware_exit ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  runtime_pwctrl ; 
 int /*<<< orphan*/  usbhs_fifo_remove (struct usbhs_priv*) ; 
 int /*<<< orphan*/  usbhs_get_dparam (struct usbhs_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhs_mod_remove (struct usbhs_priv*) ; 
 struct usbhs_priv* usbhs_pdev_to_priv (struct platform_device*) ; 
 int /*<<< orphan*/  usbhs_pipe_remove (struct usbhs_priv*) ; 
 int /*<<< orphan*/  usbhs_platform_call (struct usbhs_priv*,int /*<<< orphan*/ ,struct platform_device*) ; 
 int /*<<< orphan*/  usbhsc_clk_put (struct usbhs_priv*) ; 
 int /*<<< orphan*/  usbhsc_power_ctrl (struct usbhs_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbhs_remove(struct platform_device *pdev)
{
	struct usbhs_priv *priv = usbhs_pdev_to_priv(pdev);

	dev_dbg(&pdev->dev, "usb remove\n");

	/* power off */
	if (!usbhs_get_dparam(priv, runtime_pwctrl))
		usbhsc_power_ctrl(priv, 0);

	pm_runtime_disable(&pdev->dev);

	usbhs_platform_call(priv, hardware_exit, pdev);
	usbhsc_clk_put(priv);
	reset_control_assert(priv->rsts);
	usbhs_mod_remove(priv);
	usbhs_fifo_remove(priv);
	usbhs_pipe_remove(priv);

	return 0;
}