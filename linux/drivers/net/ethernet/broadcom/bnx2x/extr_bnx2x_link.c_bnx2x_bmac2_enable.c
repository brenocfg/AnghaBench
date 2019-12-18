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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct link_vars {int dummy; } ;
struct link_params {int* mac_addr; scalar_t__ port; struct bnx2x* bp; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int BIGMAC2_REGISTER_BMAC_CONTROL ; 
 int BIGMAC2_REGISTER_BMAC_XGXS_CONTROL ; 
 int BIGMAC2_REGISTER_CNT_MAX_SIZE ; 
 int BIGMAC2_REGISTER_RX_LLFC_MSG_FLDS ; 
 int BIGMAC2_REGISTER_RX_MAX_SIZE ; 
 int BIGMAC2_REGISTER_TX_MAX_SIZE ; 
 int BIGMAC2_REGISTER_TX_SOURCE_ADDR ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int ETH_MAX_JUMBO_PACKET_SIZE ; 
 int ETH_OVERHEAD ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 int NIG_REG_INGRESS_BMAC0_MEM ; 
 int NIG_REG_INGRESS_BMAC1_MEM ; 
 int /*<<< orphan*/  REG_WR_DMAE (struct bnx2x*,int,int*,int) ; 
 int /*<<< orphan*/  bnx2x_update_pfc_bmac2 (struct link_params*,struct link_vars*,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int bnx2x_bmac2_enable(struct link_params *params,
			      struct link_vars *vars,
			      u8 is_lb)
{
	struct bnx2x *bp = params->bp;
	u8 port = params->port;
	u32 bmac_addr = port ? NIG_REG_INGRESS_BMAC1_MEM :
			       NIG_REG_INGRESS_BMAC0_MEM;
	u32 wb_data[2];

	DP(NETIF_MSG_LINK, "Enabling BigMAC2\n");

	wb_data[0] = 0;
	wb_data[1] = 0;
	REG_WR_DMAE(bp, bmac_addr + BIGMAC2_REGISTER_BMAC_CONTROL, wb_data, 2);
	udelay(30);

	/* XGXS control: Reset phy HW, MDIO registers, PHY PLL and BMAC */
	wb_data[0] = 0x3c;
	wb_data[1] = 0;
	REG_WR_DMAE(bp, bmac_addr + BIGMAC2_REGISTER_BMAC_XGXS_CONTROL,
		    wb_data, 2);

	udelay(30);

	/* TX MAC SA */
	wb_data[0] = ((params->mac_addr[2] << 24) |
		       (params->mac_addr[3] << 16) |
		       (params->mac_addr[4] << 8) |
			params->mac_addr[5]);
	wb_data[1] = ((params->mac_addr[0] << 8) |
			params->mac_addr[1]);
	REG_WR_DMAE(bp, bmac_addr + BIGMAC2_REGISTER_TX_SOURCE_ADDR,
		    wb_data, 2);

	udelay(30);

	/* Configure SAFC */
	wb_data[0] = 0x1000200;
	wb_data[1] = 0;
	REG_WR_DMAE(bp, bmac_addr + BIGMAC2_REGISTER_RX_LLFC_MSG_FLDS,
		    wb_data, 2);
	udelay(30);

	/* Set RX MTU */
	wb_data[0] = ETH_MAX_JUMBO_PACKET_SIZE + ETH_OVERHEAD;
	wb_data[1] = 0;
	REG_WR_DMAE(bp, bmac_addr + BIGMAC2_REGISTER_RX_MAX_SIZE, wb_data, 2);
	udelay(30);

	/* Set TX MTU */
	wb_data[0] = ETH_MAX_JUMBO_PACKET_SIZE + ETH_OVERHEAD;
	wb_data[1] = 0;
	REG_WR_DMAE(bp, bmac_addr + BIGMAC2_REGISTER_TX_MAX_SIZE, wb_data, 2);
	udelay(30);
	/* Set cnt max size */
	wb_data[0] = ETH_MAX_JUMBO_PACKET_SIZE + ETH_OVERHEAD - 2;
	wb_data[1] = 0;
	REG_WR_DMAE(bp, bmac_addr + BIGMAC2_REGISTER_CNT_MAX_SIZE, wb_data, 2);
	udelay(30);
	bnx2x_update_pfc_bmac2(params, vars, is_lb);

	return 0;
}