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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct link_vars {int flow_ctrl; } ;
struct link_params {int feature_config_flags; int* mac_addr; scalar_t__ port; struct bnx2x* bp; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int BNX2X_FLOW_CTRL_RX ; 
 int BNX2X_FLOW_CTRL_TX ; 
 int FEATURE_CONFIG_PFC_ENABLED ; 
 int GRCBASE_XMAC0 ; 
 int GRCBASE_XMAC1 ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int,int) ; 
 int XMAC_PAUSE_CTRL_REG_RX_PAUSE_EN ; 
 int XMAC_PAUSE_CTRL_REG_TX_PAUSE_EN ; 
 int XMAC_PFC_CTRL_HI_REG_FORCE_PFC_XON ; 
 int XMAC_PFC_CTRL_HI_REG_PFC_REFRESH_EN ; 
 int XMAC_PFC_CTRL_HI_REG_PFC_STATS_EN ; 
 int XMAC_PFC_CTRL_HI_REG_RX_PFC_EN ; 
 int XMAC_PFC_CTRL_HI_REG_TX_PFC_EN ; 
 int XMAC_REG_CTRL_SA_HI ; 
 int XMAC_REG_CTRL_SA_LO ; 
 int XMAC_REG_PAUSE_CTRL ; 
 int XMAC_REG_PFC_CTRL ; 
 int XMAC_REG_PFC_CTRL_HI ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void bnx2x_update_pfc_xmac(struct link_params *params,
				  struct link_vars *vars,
				  u8 is_lb)
{
	struct bnx2x *bp = params->bp;
	u32 xmac_base;
	u32 pause_val, pfc0_val, pfc1_val;

	/* XMAC base adrr */
	xmac_base = (params->port) ? GRCBASE_XMAC1 : GRCBASE_XMAC0;

	/* Initialize pause and pfc registers */
	pause_val = 0x18000;
	pfc0_val = 0xFFFF8000;
	pfc1_val = 0x2;

	/* No PFC support */
	if (!(params->feature_config_flags &
	      FEATURE_CONFIG_PFC_ENABLED)) {

		/* RX flow control - Process pause frame in receive direction
		 */
		if (vars->flow_ctrl & BNX2X_FLOW_CTRL_RX)
			pause_val |= XMAC_PAUSE_CTRL_REG_RX_PAUSE_EN;

		/* TX flow control - Send pause packet when buffer is full */
		if (vars->flow_ctrl & BNX2X_FLOW_CTRL_TX)
			pause_val |= XMAC_PAUSE_CTRL_REG_TX_PAUSE_EN;
	} else {/* PFC support */
		pfc1_val |= XMAC_PFC_CTRL_HI_REG_PFC_REFRESH_EN |
			XMAC_PFC_CTRL_HI_REG_PFC_STATS_EN |
			XMAC_PFC_CTRL_HI_REG_RX_PFC_EN |
			XMAC_PFC_CTRL_HI_REG_TX_PFC_EN |
			XMAC_PFC_CTRL_HI_REG_FORCE_PFC_XON;
		/* Write pause and PFC registers */
		REG_WR(bp, xmac_base + XMAC_REG_PAUSE_CTRL, pause_val);
		REG_WR(bp, xmac_base + XMAC_REG_PFC_CTRL, pfc0_val);
		REG_WR(bp, xmac_base + XMAC_REG_PFC_CTRL_HI, pfc1_val);
		pfc1_val &= ~XMAC_PFC_CTRL_HI_REG_FORCE_PFC_XON;

	}

	/* Write pause and PFC registers */
	REG_WR(bp, xmac_base + XMAC_REG_PAUSE_CTRL, pause_val);
	REG_WR(bp, xmac_base + XMAC_REG_PFC_CTRL, pfc0_val);
	REG_WR(bp, xmac_base + XMAC_REG_PFC_CTRL_HI, pfc1_val);


	/* Set MAC address for source TX Pause/PFC frames */
	REG_WR(bp, xmac_base + XMAC_REG_CTRL_SA_LO,
	       ((params->mac_addr[2] << 24) |
		(params->mac_addr[3] << 16) |
		(params->mac_addr[4] << 8) |
		(params->mac_addr[5])));
	REG_WR(bp, xmac_base + XMAC_REG_CTRL_SA_HI,
	       ((params->mac_addr[0] << 8) |
		(params->mac_addr[1])));

	udelay(30);
}