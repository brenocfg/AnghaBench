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
struct xgene_enet_pdata {int phy_speed; int /*<<< orphan*/  rx_delay; int /*<<< orphan*/  tx_delay; } ;

/* Variables and functions */
 int CFG_BYPASS_UNISEC_RX ; 
 int CFG_BYPASS_UNISEC_TX ; 
 int /*<<< orphan*/  CFG_MACMODE_SET (int*,int) ; 
 int /*<<< orphan*/  CFG_RXCLK_MUXSEL0_SET (int*,int /*<<< orphan*/ ) ; 
 int CFG_SPEED_1250 ; 
 int /*<<< orphan*/  CFG_TXCLK_MUXSEL0_SET (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFG_WAITASYNCRD_SET (int*,int) ; 
 int /*<<< orphan*/  DEBUG_REG_ADDR ; 
 int ENET_GHD_MODE ; 
 int /*<<< orphan*/  ENET_INTERFACE_MODE2_SET (int*,int) ; 
 int ENET_LHD_MODE ; 
 int FULL_DUPLEX2 ; 
 int /*<<< orphan*/  ICM_CONFIG0_REG_0_ADDR ; 
 int /*<<< orphan*/  ICM_CONFIG2_REG_0_ADDR ; 
 int /*<<< orphan*/  INTERFACE_CONTROL_ADDR ; 
 int LENGTH_CHK ; 
 int /*<<< orphan*/  MAC_CONFIG_2_ADDR ; 
 int PAD_CRC ; 
 int /*<<< orphan*/  RGMII_REG_0_ADDR ; 
#define  SPEED_10 129 
#define  SPEED_100 128 
 int /*<<< orphan*/  xgene_enet_configure_clock (struct xgene_enet_pdata*) ; 
 int /*<<< orphan*/  xgene_enet_rd_csr (struct xgene_enet_pdata*,int /*<<< orphan*/ ,int*) ; 
 int xgene_enet_rd_mac (struct xgene_enet_pdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgene_enet_rd_mcx_csr (struct xgene_enet_pdata*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  xgene_enet_wr_csr (struct xgene_enet_pdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgene_enet_wr_mac (struct xgene_enet_pdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgene_enet_wr_mcx_csr (struct xgene_enet_pdata*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xgene_gmac_set_speed(struct xgene_enet_pdata *pdata)
{
	u32 icm0, icm2, mc2;
	u32 intf_ctl, rgmii, value;

	xgene_enet_rd_mcx_csr(pdata, ICM_CONFIG0_REG_0_ADDR, &icm0);
	xgene_enet_rd_mcx_csr(pdata, ICM_CONFIG2_REG_0_ADDR, &icm2);
	mc2 = xgene_enet_rd_mac(pdata, MAC_CONFIG_2_ADDR);
	intf_ctl = xgene_enet_rd_mac(pdata, INTERFACE_CONTROL_ADDR);
	xgene_enet_rd_csr(pdata, RGMII_REG_0_ADDR, &rgmii);

	switch (pdata->phy_speed) {
	case SPEED_10:
		ENET_INTERFACE_MODE2_SET(&mc2, 1);
		intf_ctl &= ~(ENET_LHD_MODE | ENET_GHD_MODE);
		CFG_MACMODE_SET(&icm0, 0);
		CFG_WAITASYNCRD_SET(&icm2, 500);
		rgmii &= ~CFG_SPEED_1250;
		break;
	case SPEED_100:
		ENET_INTERFACE_MODE2_SET(&mc2, 1);
		intf_ctl &= ~ENET_GHD_MODE;
		intf_ctl |= ENET_LHD_MODE;
		CFG_MACMODE_SET(&icm0, 1);
		CFG_WAITASYNCRD_SET(&icm2, 80);
		rgmii &= ~CFG_SPEED_1250;
		break;
	default:
		ENET_INTERFACE_MODE2_SET(&mc2, 2);
		intf_ctl &= ~ENET_LHD_MODE;
		intf_ctl |= ENET_GHD_MODE;
		CFG_MACMODE_SET(&icm0, 2);
		CFG_WAITASYNCRD_SET(&icm2, 0);
		CFG_TXCLK_MUXSEL0_SET(&rgmii, pdata->tx_delay);
		CFG_RXCLK_MUXSEL0_SET(&rgmii, pdata->rx_delay);
		rgmii |= CFG_SPEED_1250;

		xgene_enet_rd_csr(pdata, DEBUG_REG_ADDR, &value);
		value |= CFG_BYPASS_UNISEC_TX | CFG_BYPASS_UNISEC_RX;
		xgene_enet_wr_csr(pdata, DEBUG_REG_ADDR, value);
		break;
	}

	mc2 |= FULL_DUPLEX2 | PAD_CRC | LENGTH_CHK;
	xgene_enet_wr_mac(pdata, MAC_CONFIG_2_ADDR, mc2);
	xgene_enet_wr_mac(pdata, INTERFACE_CONTROL_ADDR, intf_ctl);
	xgene_enet_wr_csr(pdata, RGMII_REG_0_ADDR, rgmii);
	xgene_enet_configure_clock(pdata);

	xgene_enet_wr_mcx_csr(pdata, ICM_CONFIG0_REG_0_ADDR, icm0);
	xgene_enet_wr_mcx_csr(pdata, ICM_CONFIG2_REG_0_ADDR, icm2);
}