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
struct link_params {struct bnx2x* bp; scalar_t__ port; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int GRCBASE_XMAC0 ; 
 int GRCBASE_XMAC1 ; 
 int MISC_REGISTERS_RESET_REG_2_XMAC ; 
 int MISC_REG_RESET_REG_2 ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 int REG_RD (struct bnx2x*,int) ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int,int) ; 
 int XMAC_CTRL_REG_RX_EN ; 
 int XMAC_CTRL_REG_TX_EN ; 
 int XMAC_REG_CTRL ; 
 int XMAC_REG_PFC_CTRL_HI ; 

__attribute__((used)) static void bnx2x_set_xmac_rxtx(struct link_params *params, u8 en)
{
	u8 port = params->port;
	struct bnx2x *bp = params->bp;
	u32 pfc_ctrl, xmac_base = (port) ? GRCBASE_XMAC1 : GRCBASE_XMAC0;
	u32 val;

	if (REG_RD(bp, MISC_REG_RESET_REG_2) &
	    MISC_REGISTERS_RESET_REG_2_XMAC) {
		/* Send an indication to change the state in the NIG back to XON
		 * Clearing this bit enables the next set of this bit to get
		 * rising edge
		 */
		pfc_ctrl = REG_RD(bp, xmac_base + XMAC_REG_PFC_CTRL_HI);
		REG_WR(bp, xmac_base + XMAC_REG_PFC_CTRL_HI,
		       (pfc_ctrl & ~(1<<1)));
		REG_WR(bp, xmac_base + XMAC_REG_PFC_CTRL_HI,
		       (pfc_ctrl | (1<<1)));
		DP(NETIF_MSG_LINK, "Disable XMAC on port %x\n", port);
		val = REG_RD(bp, xmac_base + XMAC_REG_CTRL);
		if (en)
			val |= (XMAC_CTRL_REG_TX_EN | XMAC_CTRL_REG_RX_EN);
		else
			val &= ~(XMAC_CTRL_REG_TX_EN | XMAC_CTRL_REG_RX_EN);
		REG_WR(bp, xmac_base + XMAC_REG_CTRL, val);
	}
}