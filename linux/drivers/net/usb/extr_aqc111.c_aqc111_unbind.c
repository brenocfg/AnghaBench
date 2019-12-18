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
typedef  scalar_t__ u16 ;
struct usbnet {struct aqc111_data* driver_priv; } ;
struct usb_interface {int dummy; } ;
struct aqc111_data {int /*<<< orphan*/  phy_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  AQ_ACCESS_MAC ; 
 int /*<<< orphan*/  AQ_ADV_MASK ; 
 int /*<<< orphan*/  AQ_LOW_POWER ; 
 int /*<<< orphan*/  AQ_PHY_OPS ; 
 int /*<<< orphan*/  AQ_PHY_POWER_EN ; 
 int /*<<< orphan*/  SFR_PHYPWR_RSTCTL ; 
 scalar_t__ SFR_PHYPWR_RSTCTL_BZ ; 
 int /*<<< orphan*/  aqc111_write16_cmd_nopm (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  aqc111_write32_cmd_nopm (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct aqc111_data*) ; 

__attribute__((used)) static void aqc111_unbind(struct usbnet *dev, struct usb_interface *intf)
{
	struct aqc111_data *aqc111_data = dev->driver_priv;
	u16 reg16;

	/* Force bz */
	reg16 = SFR_PHYPWR_RSTCTL_BZ;
	aqc111_write16_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_PHYPWR_RSTCTL,
				2, &reg16);
	reg16 = 0;
	aqc111_write16_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_PHYPWR_RSTCTL,
				2, &reg16);

	/* Power down ethernet PHY */
	aqc111_data->phy_cfg &= ~AQ_ADV_MASK;
	aqc111_data->phy_cfg |= AQ_LOW_POWER;
	aqc111_data->phy_cfg &= ~AQ_PHY_POWER_EN;
	aqc111_write32_cmd_nopm(dev, AQ_PHY_OPS, 0, 0,
				&aqc111_data->phy_cfg);

	kfree(aqc111_data);
}