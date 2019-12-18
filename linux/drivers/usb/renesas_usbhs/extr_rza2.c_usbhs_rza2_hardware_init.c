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
struct usbhs_priv {struct phy* phy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct phy*) ; 
 int PTR_ERR (struct phy*) ; 
 struct phy* phy_get (int /*<<< orphan*/ *,char*) ; 
 struct usbhs_priv* usbhs_pdev_to_priv (struct platform_device*) ; 

__attribute__((used)) static int usbhs_rza2_hardware_init(struct platform_device *pdev)
{
	struct usbhs_priv *priv = usbhs_pdev_to_priv(pdev);
	struct phy *phy = phy_get(&pdev->dev, "usb");

	if (IS_ERR(phy))
		return PTR_ERR(phy);

	priv->phy = phy;
	return 0;
}