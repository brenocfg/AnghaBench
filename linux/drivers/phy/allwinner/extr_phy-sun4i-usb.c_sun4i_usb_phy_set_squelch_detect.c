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
struct sun4i_usb_phy {int dummy; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_SQUELCH_DETECT ; 
 struct sun4i_usb_phy* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  sun4i_usb_phy_write (struct sun4i_usb_phy*,int /*<<< orphan*/ ,int,int) ; 

void sun4i_usb_phy_set_squelch_detect(struct phy *_phy, bool enabled)
{
	struct sun4i_usb_phy *phy = phy_get_drvdata(_phy);

	sun4i_usb_phy_write(phy, PHY_SQUELCH_DETECT, enabled ? 0 : 2, 2);
}