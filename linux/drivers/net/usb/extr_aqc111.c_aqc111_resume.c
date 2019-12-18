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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct usbnet {int /*<<< orphan*/  net; struct aqc111_data* driver_priv; } ;
struct usb_interface {int dummy; } ;
struct aqc111_data {int /*<<< orphan*/  advertised_speed; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  rxctl; int /*<<< orphan*/  phy_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  AQ_ACCESS_MAC ; 
 int /*<<< orphan*/  AQ_LOW_POWER ; 
 int /*<<< orphan*/  AQ_PHY_POWER_EN ; 
 int /*<<< orphan*/  AQ_WOL ; 
 int /*<<< orphan*/  SFR_BMRX_DMA_CONTROL ; 
 int /*<<< orphan*/  SFR_BM_INT_MASK ; 
 int /*<<< orphan*/  SFR_ETH_MAC_PATH ; 
 int /*<<< orphan*/  SFR_MEDIUM_RECEIVE_EN ; 
 int /*<<< orphan*/  SFR_MEDIUM_STATUS_MODE ; 
 int /*<<< orphan*/  SFR_RX_CTL ; 
 int /*<<< orphan*/  SFR_RX_CTL_START ; 
 int SFR_RX_PATH_READY ; 
 int /*<<< orphan*/  aqc111_read16_cmd_nopm (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aqc111_set_phy_speed (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aqc111_write16_cmd_nopm (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aqc111_write_cmd (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int*) ; 
 int /*<<< orphan*/  aqc111_write_cmd_nopm (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int*) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 struct usbnet* usb_get_intfdata (struct usb_interface*) ; 
 int usbnet_resume (struct usb_interface*) ; 

__attribute__((used)) static int aqc111_resume(struct usb_interface *intf)
{
	struct usbnet *dev = usb_get_intfdata(intf);
	struct aqc111_data *aqc111_data = dev->driver_priv;
	u16 reg16;
	u8 reg8;

	netif_carrier_off(dev->net);

	/* Power up ethernet PHY */
	aqc111_data->phy_cfg |= AQ_PHY_POWER_EN;
	aqc111_data->phy_cfg &= ~AQ_LOW_POWER;
	aqc111_data->phy_cfg &= ~AQ_WOL;

	reg8 = 0xFF;
	aqc111_write_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_BM_INT_MASK,
			      1, 1, &reg8);
	/* Configure RX control register => start operation */
	reg16 = aqc111_data->rxctl;
	reg16 &= ~SFR_RX_CTL_START;
	aqc111_write16_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_RX_CTL, 2, &reg16);

	reg16 |= SFR_RX_CTL_START;
	aqc111_write16_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_RX_CTL, 2, &reg16);

	aqc111_set_phy_speed(dev, aqc111_data->autoneg,
			     aqc111_data->advertised_speed);

	aqc111_read16_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_MEDIUM_STATUS_MODE,
			       2, &reg16);
	reg16 |= SFR_MEDIUM_RECEIVE_EN;
	aqc111_write16_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_MEDIUM_STATUS_MODE,
				2, &reg16);
	reg8 = SFR_RX_PATH_READY;
	aqc111_write_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_ETH_MAC_PATH,
			      1, 1, &reg8);
	reg8 = 0x0;
	aqc111_write_cmd(dev, AQ_ACCESS_MAC, SFR_BMRX_DMA_CONTROL, 1, 1, &reg8);

	return usbnet_resume(intf);
}