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
struct usbhs_priv {int /*<<< orphan*/ * phy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  phy_put (int /*<<< orphan*/ *) ; 
 struct usbhs_priv* usbhs_pdev_to_priv (struct platform_device*) ; 

__attribute__((used)) static int usbhs_rza2_hardware_exit(struct platform_device *pdev)
{
	struct usbhs_priv *priv = usbhs_pdev_to_priv(pdev);

	phy_put(priv->phy);
	priv->phy = NULL;

	return 0;
}