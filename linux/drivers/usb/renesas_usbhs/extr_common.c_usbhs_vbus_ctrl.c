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
struct usbhs_priv {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_vbus ; 
 int usbhs_platform_call (struct usbhs_priv*,int /*<<< orphan*/ ,struct platform_device*,int) ; 
 struct platform_device* usbhs_priv_to_pdev (struct usbhs_priv*) ; 

int usbhs_vbus_ctrl(struct usbhs_priv *priv, int enable)
{
	struct platform_device *pdev = usbhs_priv_to_pdev(priv);

	return usbhs_platform_call(priv, set_vbus, pdev, enable);
}