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
typedef  int /*<<< orphan*/  u16 ;
struct usbnet {int /*<<< orphan*/  net; struct aqc111_data* driver_priv; } ;
struct aqc111_data {int /*<<< orphan*/  phy_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  AQ_ACCESS_MAC ; 
 int /*<<< orphan*/  AQ_LOW_POWER ; 
 int /*<<< orphan*/  AQ_PHY_OPS ; 
 int /*<<< orphan*/  SFR_MEDIUM_RECEIVE_EN ; 
 int /*<<< orphan*/  SFR_MEDIUM_STATUS_MODE ; 
 int /*<<< orphan*/  SFR_RX_CTL ; 
 int /*<<< orphan*/  aqc111_read16_cmd (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aqc111_write16_cmd (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aqc111_write32_cmd (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aqc111_stop(struct usbnet *dev)
{
	struct aqc111_data *aqc111_data = dev->driver_priv;
	u16 reg16 = 0;

	aqc111_read16_cmd(dev, AQ_ACCESS_MAC, SFR_MEDIUM_STATUS_MODE,
			  2, &reg16);
	reg16 &= ~SFR_MEDIUM_RECEIVE_EN;
	aqc111_write16_cmd(dev, AQ_ACCESS_MAC, SFR_MEDIUM_STATUS_MODE,
			   2, &reg16);
	reg16 = 0;
	aqc111_write16_cmd(dev, AQ_ACCESS_MAC, SFR_RX_CTL, 2, &reg16);

	/* Put PHY to low power*/
	aqc111_data->phy_cfg |= AQ_LOW_POWER;
	aqc111_write32_cmd(dev, AQ_PHY_OPS, 0, 0,
			   &aqc111_data->phy_cfg);

	netif_carrier_off(dev->net);

	return 0;
}