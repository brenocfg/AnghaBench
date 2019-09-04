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
typedef  int u32 ;
typedef  int u16 ;
struct link_vars {int dummy; } ;
struct link_params {int port; int* mac_addr; struct bnx2x* bp; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,...) ; 
 int EMAC_MODE_RESET ; 
 int EMAC_REG_EMAC_MAC_MATCH ; 
 int EMAC_REG_EMAC_MODE ; 
 int /*<<< orphan*/  EMAC_WR (struct bnx2x*,int,int) ; 
 int GRCBASE_EMAC0 ; 
 int GRCBASE_EMAC1 ; 
 scalar_t__ GRCBASE_MISC ; 
 scalar_t__ MISC_REGISTERS_RESET_REG_2_CLEAR ; 
 int MISC_REGISTERS_RESET_REG_2_RST_EMAC0_HARD_CORE ; 
 scalar_t__ MISC_REGISTERS_RESET_REG_2_SET ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 int REG_RD (struct bnx2x*,int) ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,scalar_t__,int) ; 
 int /*<<< orphan*/  bnx2x_set_mdio_emac_per_phy (struct bnx2x*,struct link_params*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void bnx2x_emac_init(struct link_params *params,
			    struct link_vars *vars)
{
	/* reset and unreset the emac core */
	struct bnx2x *bp = params->bp;
	u8 port = params->port;
	u32 emac_base = port ? GRCBASE_EMAC1 : GRCBASE_EMAC0;
	u32 val;
	u16 timeout;

	REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_2_CLEAR,
	       (MISC_REGISTERS_RESET_REG_2_RST_EMAC0_HARD_CORE << port));
	udelay(5);
	REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_2_SET,
	       (MISC_REGISTERS_RESET_REG_2_RST_EMAC0_HARD_CORE << port));

	/* init emac - use read-modify-write */
	/* self clear reset */
	val = REG_RD(bp, emac_base + EMAC_REG_EMAC_MODE);
	EMAC_WR(bp, EMAC_REG_EMAC_MODE, (val | EMAC_MODE_RESET));

	timeout = 200;
	do {
		val = REG_RD(bp, emac_base + EMAC_REG_EMAC_MODE);
		DP(NETIF_MSG_LINK, "EMAC reset reg is %u\n", val);
		if (!timeout) {
			DP(NETIF_MSG_LINK, "EMAC timeout!\n");
			return;
		}
		timeout--;
	} while (val & EMAC_MODE_RESET);

	bnx2x_set_mdio_emac_per_phy(bp, params);
	/* Set mac address */
	val = ((params->mac_addr[0] << 8) |
		params->mac_addr[1]);
	EMAC_WR(bp, EMAC_REG_EMAC_MAC_MATCH, val);

	val = ((params->mac_addr[2] << 24) |
	       (params->mac_addr[3] << 16) |
	       (params->mac_addr[4] << 8) |
		params->mac_addr[5]);
	EMAC_WR(bp, EMAC_REG_EMAC_MAC_MATCH + 4, val);
}