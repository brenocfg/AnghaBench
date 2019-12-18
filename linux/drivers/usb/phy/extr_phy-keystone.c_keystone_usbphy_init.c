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
typedef  int u32 ;
struct usb_phy {int /*<<< orphan*/  dev; } ;
struct keystone_usbphy {int /*<<< orphan*/  phy_ctrl; } ;

/* Variables and functions */
 int PHY_REF_SSP_EN ; 
 int /*<<< orphan*/  USB_PHY_CTL_CLOCK ; 
 struct keystone_usbphy* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int keystone_usbphy_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keystone_usbphy_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int keystone_usbphy_init(struct usb_phy *phy)
{
	struct keystone_usbphy *k_phy = dev_get_drvdata(phy->dev);
	u32 val;

	val  = keystone_usbphy_readl(k_phy->phy_ctrl, USB_PHY_CTL_CLOCK);
	keystone_usbphy_writel(k_phy->phy_ctrl, USB_PHY_CTL_CLOCK,
				val | PHY_REF_SSP_EN);
	return 0;
}