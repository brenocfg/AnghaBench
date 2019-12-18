#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct usbnet {TYPE_1__* net; struct aqc111_data* driver_priv; } ;
struct aqc111_data {int link; int rxctl; } ;
struct TYPE_4__ {int features; int mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  AQ_ACCESS_MAC ; 
 int NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int /*<<< orphan*/  SFR_ARC_CTRL ; 
 int /*<<< orphan*/  SFR_BMRX_DMA_CONTROL ; 
 int /*<<< orphan*/  SFR_BMTX_DMA_CONTROL ; 
 int /*<<< orphan*/  SFR_BULK_OUT_CTRL ; 
 int SFR_BULK_OUT_EFF_EN ; 
 int SFR_BULK_OUT_FLUSH_EN ; 
 int /*<<< orphan*/  SFR_ETH_MAC_PATH ; 
 int SFR_MEDIUM_FULL_DUPLEX ; 
 int SFR_MEDIUM_JUMBO_EN ; 
 int SFR_MEDIUM_RECEIVE_EN ; 
 int SFR_MEDIUM_RXFLOW_CTRLEN ; 
 int /*<<< orphan*/  SFR_MEDIUM_STATUS_MODE ; 
 int SFR_MEDIUM_TXFLOW_CTRLEN ; 
 int SFR_MEDIUM_XGMIIMODE ; 
 int /*<<< orphan*/  SFR_RX_CTL ; 
 int SFR_RX_CTL_AB ; 
 int SFR_RX_CTL_IPE ; 
 int SFR_RX_CTL_START ; 
 int SFR_RX_PATH_READY ; 
 int SFR_VLAN_CONTROL_VFE ; 
 int SFR_VLAN_CONTROL_VSO ; 
 int /*<<< orphan*/  SFR_VLAN_ID_CONTROL ; 
 int /*<<< orphan*/  aqc111_configure_csum_offload (struct usbnet*) ; 
 int /*<<< orphan*/  aqc111_configure_rx (struct usbnet*,struct aqc111_data*) ; 
 int /*<<< orphan*/  aqc111_read16_cmd (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  aqc111_set_rx_mode (TYPE_1__*) ; 
 int /*<<< orphan*/  aqc111_write16_cmd (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  aqc111_write_cmd (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int*) ; 
 int /*<<< orphan*/  netif_carrier_off (TYPE_1__*) ; 
 int /*<<< orphan*/  netif_carrier_on (TYPE_1__*) ; 

__attribute__((used)) static int aqc111_link_reset(struct usbnet *dev)
{
	struct aqc111_data *aqc111_data = dev->driver_priv;
	u16 reg16 = 0;
	u8 reg8 = 0;

	if (aqc111_data->link == 1) { /* Link up */
		aqc111_configure_rx(dev, aqc111_data);

		/* Vlan Tag Filter */
		reg8 = SFR_VLAN_CONTROL_VSO;
		if (dev->net->features & NETIF_F_HW_VLAN_CTAG_FILTER)
			reg8 |= SFR_VLAN_CONTROL_VFE;

		aqc111_write_cmd(dev, AQ_ACCESS_MAC, SFR_VLAN_ID_CONTROL,
				 1, 1, &reg8);

		reg8 = 0x0;
		aqc111_write_cmd(dev, AQ_ACCESS_MAC, SFR_BMRX_DMA_CONTROL,
				 1, 1, &reg8);

		aqc111_write_cmd(dev, AQ_ACCESS_MAC, SFR_BMTX_DMA_CONTROL,
				 1, 1, &reg8);

		aqc111_write_cmd(dev, AQ_ACCESS_MAC, SFR_ARC_CTRL, 1, 1, &reg8);

		reg16 = SFR_RX_CTL_IPE | SFR_RX_CTL_AB;
		aqc111_data->rxctl = reg16;
		aqc111_write16_cmd(dev, AQ_ACCESS_MAC, SFR_RX_CTL, 2, &reg16);

		reg8 = SFR_RX_PATH_READY;
		aqc111_write_cmd(dev, AQ_ACCESS_MAC, SFR_ETH_MAC_PATH,
				 1, 1, &reg8);

		reg8 = SFR_BULK_OUT_EFF_EN;
		aqc111_write_cmd(dev, AQ_ACCESS_MAC, SFR_BULK_OUT_CTRL,
				 1, 1, &reg8);

		reg16 = 0;
		aqc111_write16_cmd(dev, AQ_ACCESS_MAC, SFR_MEDIUM_STATUS_MODE,
				   2, &reg16);

		reg16 = SFR_MEDIUM_XGMIIMODE | SFR_MEDIUM_FULL_DUPLEX;
		aqc111_write16_cmd(dev, AQ_ACCESS_MAC, SFR_MEDIUM_STATUS_MODE,
				   2, &reg16);

		aqc111_configure_csum_offload(dev);

		aqc111_set_rx_mode(dev->net);

		aqc111_read16_cmd(dev, AQ_ACCESS_MAC, SFR_MEDIUM_STATUS_MODE,
				  2, &reg16);

		if (dev->net->mtu > 1500)
			reg16 |= SFR_MEDIUM_JUMBO_EN;

		reg16 |= SFR_MEDIUM_RECEIVE_EN | SFR_MEDIUM_RXFLOW_CTRLEN |
			 SFR_MEDIUM_TXFLOW_CTRLEN;
		aqc111_write16_cmd(dev, AQ_ACCESS_MAC, SFR_MEDIUM_STATUS_MODE,
				   2, &reg16);

		aqc111_data->rxctl |= SFR_RX_CTL_START;
		aqc111_write16_cmd(dev, AQ_ACCESS_MAC, SFR_RX_CTL,
				   2, &aqc111_data->rxctl);

		netif_carrier_on(dev->net);
	} else {
		aqc111_read16_cmd(dev, AQ_ACCESS_MAC, SFR_MEDIUM_STATUS_MODE,
				  2, &reg16);
		reg16 &= ~SFR_MEDIUM_RECEIVE_EN;
		aqc111_write16_cmd(dev, AQ_ACCESS_MAC, SFR_MEDIUM_STATUS_MODE,
				   2, &reg16);

		aqc111_data->rxctl &= ~SFR_RX_CTL_START;
		aqc111_write16_cmd(dev, AQ_ACCESS_MAC, SFR_RX_CTL,
				   2, &aqc111_data->rxctl);

		reg8 = SFR_BULK_OUT_FLUSH_EN | SFR_BULK_OUT_EFF_EN;
		aqc111_write_cmd(dev, AQ_ACCESS_MAC, SFR_BULK_OUT_CTRL,
				 1, 1, &reg8);
		reg8 = SFR_BULK_OUT_EFF_EN;
		aqc111_write_cmd(dev, AQ_ACCESS_MAC, SFR_BULK_OUT_CTRL,
				 1, 1, &reg8);

		netif_carrier_off(dev->net);
	}
	return 0;
}