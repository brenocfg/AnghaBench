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
struct usb_phy {int dummy; } ;
struct isp1301 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISP1301_I2C_OTG_CONTROL_1 ; 
 int /*<<< orphan*/  OTG1_VBUS_DRV ; 
 int /*<<< orphan*/  isp1301_clear (struct isp1301*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp1301_write (struct isp1301*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct isp1301* phy_to_isp (struct usb_phy*) ; 

__attribute__((used)) static int isp1301_phy_set_vbus(struct usb_phy *phy, int on)
{
	struct isp1301 *isp = phy_to_isp(phy);

	if (on)
		isp1301_write(isp, ISP1301_I2C_OTG_CONTROL_1, OTG1_VBUS_DRV);
	else
		isp1301_clear(isp, ISP1301_I2C_OTG_CONTROL_1, OTG1_VBUS_DRV);

	return 0;
}