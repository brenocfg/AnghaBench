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
struct xge_pdata {int phy_speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_MACMODE ; 
 int /*<<< orphan*/  CFG_SPEED_125 ; 
 int /*<<< orphan*/  CFG_WAITASYNCRD ; 
 int CFG_WAITASYNCRD_EN ; 
 int /*<<< orphan*/  CFG_WFIFOFULLTHR ; 
 int CRC_EN ; 
 int /*<<< orphan*/  ECM_CONFIG0_REG_0 ; 
 int FULL_DUPLEX ; 
 int /*<<< orphan*/  HD_MODE ; 
 int /*<<< orphan*/  ICM_CONFIG0_REG_0 ; 
 int /*<<< orphan*/  ICM_CONFIG2_REG_0 ; 
 int /*<<< orphan*/  INTERFACE_CONTROL ; 
 int /*<<< orphan*/  INTF_MODE ; 
 int /*<<< orphan*/  MAC_CONFIG_2 ; 
 int PAD_CRC ; 
 int /*<<< orphan*/  RGMII_REG_0 ; 
 int /*<<< orphan*/  SET_REG_BIT (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SET_REG_BITS (int*,int /*<<< orphan*/ ,int) ; 
#define  SPEED_10 129 
#define  SPEED_100 128 
 int xge_rd_csr (struct xge_pdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xge_wr_csr (struct xge_pdata*,int /*<<< orphan*/ ,int) ; 

void xge_mac_set_speed(struct xge_pdata *pdata)
{
	u32 icm0, icm2, ecm0, mc2;
	u32 intf_ctrl, rgmii;

	icm0 = xge_rd_csr(pdata, ICM_CONFIG0_REG_0);
	icm2 = xge_rd_csr(pdata, ICM_CONFIG2_REG_0);
	ecm0 = xge_rd_csr(pdata, ECM_CONFIG0_REG_0);
	rgmii = xge_rd_csr(pdata, RGMII_REG_0);
	mc2 = xge_rd_csr(pdata, MAC_CONFIG_2);
	intf_ctrl = xge_rd_csr(pdata, INTERFACE_CONTROL);
	icm2 |= CFG_WAITASYNCRD_EN;

	switch (pdata->phy_speed) {
	case SPEED_10:
		SET_REG_BITS(&mc2, INTF_MODE, 1);
		SET_REG_BITS(&intf_ctrl, HD_MODE, 0);
		SET_REG_BITS(&icm0, CFG_MACMODE, 0);
		SET_REG_BITS(&icm2, CFG_WAITASYNCRD, 500);
		SET_REG_BIT(&rgmii, CFG_SPEED_125, 0);
		break;
	case SPEED_100:
		SET_REG_BITS(&mc2, INTF_MODE, 1);
		SET_REG_BITS(&intf_ctrl, HD_MODE, 1);
		SET_REG_BITS(&icm0, CFG_MACMODE, 1);
		SET_REG_BITS(&icm2, CFG_WAITASYNCRD, 80);
		SET_REG_BIT(&rgmii, CFG_SPEED_125, 0);
		break;
	default:
		SET_REG_BITS(&mc2, INTF_MODE, 2);
		SET_REG_BITS(&intf_ctrl, HD_MODE, 2);
		SET_REG_BITS(&icm0, CFG_MACMODE, 2);
		SET_REG_BITS(&icm2, CFG_WAITASYNCRD, 16);
		SET_REG_BIT(&rgmii, CFG_SPEED_125, 1);
		break;
	}

	mc2 |= FULL_DUPLEX | CRC_EN | PAD_CRC;
	SET_REG_BITS(&ecm0, CFG_WFIFOFULLTHR, 0x32);

	xge_wr_csr(pdata, MAC_CONFIG_2, mc2);
	xge_wr_csr(pdata, INTERFACE_CONTROL, intf_ctrl);
	xge_wr_csr(pdata, RGMII_REG_0, rgmii);
	xge_wr_csr(pdata, ICM_CONFIG0_REG_0, icm0);
	xge_wr_csr(pdata, ICM_CONFIG2_REG_0, icm2);
	xge_wr_csr(pdata, ECM_CONFIG0_REG_0, ecm0);
}