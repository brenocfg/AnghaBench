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
struct phy {int dummy; } ;
struct bcm_usb_phy_cfg {scalar_t__ type; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ USB_HS_PHY ; 
 scalar_t__ USB_SS_PHY ; 
 int bcm_usb_hs_phy_init (struct bcm_usb_phy_cfg*) ; 
 int bcm_usb_ss_phy_init (struct bcm_usb_phy_cfg*) ; 
 struct bcm_usb_phy_cfg* phy_get_drvdata (struct phy*) ; 

__attribute__((used)) static int bcm_usb_phy_init(struct phy *phy)
{
	struct bcm_usb_phy_cfg *phy_cfg = phy_get_drvdata(phy);
	int ret = -EINVAL;

	if (phy_cfg->type == USB_SS_PHY)
		ret = bcm_usb_ss_phy_init(phy_cfg);
	else if (phy_cfg->type == USB_HS_PHY)
		ret = bcm_usb_hs_phy_init(phy_cfg);

	return ret;
}