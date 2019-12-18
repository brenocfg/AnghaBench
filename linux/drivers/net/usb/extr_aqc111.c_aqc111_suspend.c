#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct usbnet {TYPE_1__* net; struct aqc111_data* driver_priv; } ;
struct usb_interface {int dummy; } ;
struct aqc111_wol_cfg {scalar_t__ flags; int /*<<< orphan*/  hw_addr; } ;
struct aqc111_data {int /*<<< orphan*/  phy_cfg; scalar_t__ wol_flags; } ;
typedef  int /*<<< orphan*/  pm_message_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AQ_ACCESS_MAC ; 
 int /*<<< orphan*/  AQ_LOW_POWER ; 
 int /*<<< orphan*/  AQ_PHY_OPS ; 
 int /*<<< orphan*/  AQ_WOL ; 
 int /*<<< orphan*/  AQ_WOL_CFG ; 
 int /*<<< orphan*/  SFR_BMRX_DMA_CONTROL ; 
 int SFR_BMRX_DMA_EN ; 
 int /*<<< orphan*/  SFR_BM_INT_MASK ; 
 int /*<<< orphan*/  SFR_BULK_OUT_CTRL ; 
 int SFR_BULK_OUT_EFF_EN ; 
 int /*<<< orphan*/  SFR_ETH_MAC_PATH ; 
 int SFR_MEDIUM_RECEIVE_EN ; 
 int /*<<< orphan*/  SFR_MEDIUM_STATUS_MODE ; 
 int /*<<< orphan*/  SFR_PHYPWR_RSTCTL ; 
 int SFR_PHYPWR_RSTCTL_BZ ; 
 int /*<<< orphan*/  SFR_RX_BULKIN_QCTRL ; 
 int /*<<< orphan*/  SFR_RX_BULKIN_QIFG ; 
 int /*<<< orphan*/  SFR_RX_BULKIN_QSIZE ; 
 int /*<<< orphan*/  SFR_RX_BULKIN_QTIMR_HIGH ; 
 int /*<<< orphan*/  SFR_RX_BULKIN_QTIMR_LOW ; 
 int /*<<< orphan*/  SFR_RX_CTL ; 
 int SFR_RX_CTL_AB ; 
 int SFR_RX_CTL_AM ; 
 int SFR_RX_CTL_AP ; 
 int SFR_RX_CTL_RF_WAK ; 
 int SFR_RX_CTL_START ; 
 int SFR_RX_PATH_READY ; 
 int /*<<< orphan*/  WOL_CFG_SIZE ; 
 int /*<<< orphan*/  aqc111_read16_cmd_nopm (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  aqc111_write16_cmd_nopm (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  aqc111_write32_cmd (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aqc111_write_cmd (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct aqc111_wol_cfg*) ; 
 int /*<<< orphan*/  aqc111_write_cmd_nopm (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct aqc111_wol_cfg*,int /*<<< orphan*/ ,int) ; 
 struct usbnet* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usbnet_suspend (struct usb_interface*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aqc111_suspend(struct usb_interface *intf, pm_message_t message)
{
	struct usbnet *dev = usb_get_intfdata(intf);
	struct aqc111_data *aqc111_data = dev->driver_priv;
	u16 temp_rx_ctrl = 0x00;
	u16 reg16;
	u8 reg8;

	usbnet_suspend(intf, message);

	aqc111_read16_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_RX_CTL, 2, &reg16);
	temp_rx_ctrl = reg16;
	/* Stop RX operations*/
	reg16 &= ~SFR_RX_CTL_START;
	aqc111_write16_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_RX_CTL, 2, &reg16);
	/* Force bz */
	aqc111_read16_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_PHYPWR_RSTCTL,
			       2, &reg16);
	reg16 |= SFR_PHYPWR_RSTCTL_BZ;
	aqc111_write16_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_PHYPWR_RSTCTL,
				2, &reg16);

	reg8 = SFR_BULK_OUT_EFF_EN;
	aqc111_write_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_BULK_OUT_CTRL,
			      1, 1, &reg8);

	temp_rx_ctrl &= ~(SFR_RX_CTL_START | SFR_RX_CTL_RF_WAK |
			  SFR_RX_CTL_AP | SFR_RX_CTL_AM);
	aqc111_write16_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_RX_CTL,
				2, &temp_rx_ctrl);

	reg8 = 0x00;
	aqc111_write_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_ETH_MAC_PATH,
			      1, 1, &reg8);

	if (aqc111_data->wol_flags) {
		struct aqc111_wol_cfg wol_cfg;

		memset(&wol_cfg, 0, sizeof(struct aqc111_wol_cfg));

		aqc111_data->phy_cfg |= AQ_WOL;
		ether_addr_copy(wol_cfg.hw_addr, dev->net->dev_addr);
		wol_cfg.flags = aqc111_data->wol_flags;

		temp_rx_ctrl |= (SFR_RX_CTL_AB | SFR_RX_CTL_START);
		aqc111_write16_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_RX_CTL,
					2, &temp_rx_ctrl);
		reg8 = 0x00;
		aqc111_write_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_BM_INT_MASK,
				      1, 1, &reg8);
		reg8 = SFR_BMRX_DMA_EN;
		aqc111_write_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_BMRX_DMA_CONTROL,
				      1, 1, &reg8);
		reg8 = SFR_RX_PATH_READY;
		aqc111_write_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_ETH_MAC_PATH,
				      1, 1, &reg8);
		reg8 = 0x07;
		aqc111_write_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_RX_BULKIN_QCTRL,
				      1, 1, &reg8);
		reg8 = 0x00;
		aqc111_write_cmd_nopm(dev, AQ_ACCESS_MAC,
				      SFR_RX_BULKIN_QTIMR_LOW, 1, 1, &reg8);
		aqc111_write_cmd_nopm(dev, AQ_ACCESS_MAC,
				      SFR_RX_BULKIN_QTIMR_HIGH, 1, 1, &reg8);
		reg8 = 0xFF;
		aqc111_write_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_RX_BULKIN_QSIZE,
				      1, 1, &reg8);
		aqc111_write_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_RX_BULKIN_QIFG,
				      1, 1, &reg8);

		aqc111_read16_cmd_nopm(dev, AQ_ACCESS_MAC,
				       SFR_MEDIUM_STATUS_MODE, 2, &reg16);
		reg16 |= SFR_MEDIUM_RECEIVE_EN;
		aqc111_write16_cmd_nopm(dev, AQ_ACCESS_MAC,
					SFR_MEDIUM_STATUS_MODE, 2, &reg16);

		aqc111_write_cmd(dev, AQ_WOL_CFG, 0, 0,
				 WOL_CFG_SIZE, &wol_cfg);
		aqc111_write32_cmd(dev, AQ_PHY_OPS, 0, 0,
				   &aqc111_data->phy_cfg);
	} else {
		aqc111_data->phy_cfg |= AQ_LOW_POWER;
		aqc111_write32_cmd(dev, AQ_PHY_OPS, 0, 0,
				   &aqc111_data->phy_cfg);

		/* Disable RX path */
		aqc111_read16_cmd_nopm(dev, AQ_ACCESS_MAC,
				       SFR_MEDIUM_STATUS_MODE, 2, &reg16);
		reg16 &= ~SFR_MEDIUM_RECEIVE_EN;
		aqc111_write16_cmd_nopm(dev, AQ_ACCESS_MAC,
					SFR_MEDIUM_STATUS_MODE, 2, &reg16);
	}

	return 0;
}