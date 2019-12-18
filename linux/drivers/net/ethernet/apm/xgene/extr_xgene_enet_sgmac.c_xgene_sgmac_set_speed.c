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
struct xgene_enet_pdata {scalar_t__ enet_id; int port_id; int phy_speed; } ;

/* Variables and functions */
 int CFG_BYPASS_UNISEC_RX ; 
 int CFG_BYPASS_UNISEC_TX ; 
 int /*<<< orphan*/  CFG_MACMODE_SET (int*,int) ; 
 int /*<<< orphan*/  CFG_WAITASYNCRD_SET (int*,int) ; 
 int DEBUG_REG_ADDR ; 
 int ENET_GHD_MODE ; 
 int /*<<< orphan*/  ENET_INTERFACE_MODE2_SET (int*,int) ; 
 int ENET_LHD_MODE ; 
 int FULL_DUPLEX2 ; 
 int ICM_CONFIG0_REG_0_ADDR ; 
 int ICM_CONFIG2_REG_0_ADDR ; 
 int /*<<< orphan*/  INTERFACE_CONTROL_ADDR ; 
 int /*<<< orphan*/  MAC_CONFIG_2_ADDR ; 
 int OFFSET_4 ; 
 int OFFSET_8 ; 
 int PAD_CRC ; 
#define  SPEED_10 129 
#define  SPEED_100 128 
 scalar_t__ XGENE_ENET1 ; 
 int XG_DEBUG_REG_ADDR ; 
 int XG_MCX_ICM_CONFIG0_REG_0_ADDR ; 
 int XG_MCX_ICM_CONFIG2_REG_0_ADDR ; 
 int xgene_enet_rd_csr (struct xgene_enet_pdata*,int) ; 
 int xgene_enet_rd_mac (struct xgene_enet_pdata*,int /*<<< orphan*/ ) ; 
 int xgene_enet_rd_mcx_csr (struct xgene_enet_pdata*,int) ; 
 int /*<<< orphan*/  xgene_enet_wr_csr (struct xgene_enet_pdata*,int,int) ; 
 int /*<<< orphan*/  xgene_enet_wr_mac (struct xgene_enet_pdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgene_enet_wr_mcx_csr (struct xgene_enet_pdata*,int,int) ; 
 int /*<<< orphan*/  xgene_sgmii_reset (struct xgene_enet_pdata*) ; 

__attribute__((used)) static void xgene_sgmac_set_speed(struct xgene_enet_pdata *p)
{
	u32 icm0_addr, icm2_addr, debug_addr;
	u32 icm0, icm2, intf_ctl;
	u32 mc2, value;

	xgene_sgmii_reset(p);

	if (p->enet_id == XGENE_ENET1) {
		icm0_addr = ICM_CONFIG0_REG_0_ADDR + p->port_id * OFFSET_8;
		icm2_addr = ICM_CONFIG2_REG_0_ADDR + p->port_id * OFFSET_4;
		debug_addr = DEBUG_REG_ADDR;
	} else {
		icm0_addr = XG_MCX_ICM_CONFIG0_REG_0_ADDR;
		icm2_addr = XG_MCX_ICM_CONFIG2_REG_0_ADDR;
		debug_addr = XG_DEBUG_REG_ADDR;
	}

	icm0 = xgene_enet_rd_mcx_csr(p, icm0_addr);
	icm2 = xgene_enet_rd_mcx_csr(p, icm2_addr);
	mc2 = xgene_enet_rd_mac(p, MAC_CONFIG_2_ADDR);
	intf_ctl = xgene_enet_rd_mac(p, INTERFACE_CONTROL_ADDR);

	switch (p->phy_speed) {
	case SPEED_10:
		ENET_INTERFACE_MODE2_SET(&mc2, 1);
		intf_ctl &= ~(ENET_LHD_MODE | ENET_GHD_MODE);
		CFG_MACMODE_SET(&icm0, 0);
		CFG_WAITASYNCRD_SET(&icm2, 500);
		break;
	case SPEED_100:
		ENET_INTERFACE_MODE2_SET(&mc2, 1);
		intf_ctl &= ~ENET_GHD_MODE;
		intf_ctl |= ENET_LHD_MODE;
		CFG_MACMODE_SET(&icm0, 1);
		CFG_WAITASYNCRD_SET(&icm2, 80);
		break;
	default:
		ENET_INTERFACE_MODE2_SET(&mc2, 2);
		intf_ctl &= ~ENET_LHD_MODE;
		intf_ctl |= ENET_GHD_MODE;
		CFG_MACMODE_SET(&icm0, 2);
		CFG_WAITASYNCRD_SET(&icm2, 16);
		value = xgene_enet_rd_csr(p, debug_addr);
		value |= CFG_BYPASS_UNISEC_TX | CFG_BYPASS_UNISEC_RX;
		xgene_enet_wr_csr(p, debug_addr, value);
		break;
	}

	mc2 |= FULL_DUPLEX2 | PAD_CRC;
	xgene_enet_wr_mac(p, MAC_CONFIG_2_ADDR, mc2);
	xgene_enet_wr_mac(p, INTERFACE_CONTROL_ADDR, intf_ctl);
	xgene_enet_wr_mcx_csr(p, icm0_addr, icm0);
	xgene_enet_wr_mcx_csr(p, icm2_addr, icm2);
}