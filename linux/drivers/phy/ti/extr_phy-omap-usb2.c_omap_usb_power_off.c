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
struct omap_usb {int dummy; } ;

/* Variables and functions */
 int omap_usb_phy_power (struct omap_usb*,int) ; 
 struct omap_usb* phy_get_drvdata (struct phy*) ; 

__attribute__((used)) static int omap_usb_power_off(struct phy *x)
{
	struct omap_usb *phy = phy_get_drvdata(x);

	return omap_usb_phy_power(phy, false);
}