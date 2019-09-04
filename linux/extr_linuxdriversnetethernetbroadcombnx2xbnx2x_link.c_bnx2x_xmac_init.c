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
typedef  scalar_t__ u32 ;
struct link_params {struct bnx2x* bp; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHIP_NUM (struct bnx2x*) ; 
 scalar_t__ CHIP_NUM_57840_2_20 ; 
 scalar_t__ CHIP_NUM_57840_4_10 ; 
 scalar_t__ CHIP_NUM_57840_OBSOLETE ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ GRCBASE_MISC ; 
 scalar_t__ MISC_REGISTERS_RESET_REG_2_CLEAR ; 
 scalar_t__ MISC_REGISTERS_RESET_REG_2_SET ; 
 int MISC_REGISTERS_RESET_REG_2_XMAC ; 
 int MISC_REGISTERS_RESET_REG_2_XMAC_SOFT ; 
 int /*<<< orphan*/  MISC_REG_RESET_REG_2 ; 
 scalar_t__ MISC_REG_XMAC_CORE_PORT_MODE ; 
 scalar_t__ MISC_REG_XMAC_PHY_PORT_MODE ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 int REG_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,scalar_t__,int) ; 
 scalar_t__ SPEED_10000 ; 
 scalar_t__ bnx2x_is_4_port_mode (struct bnx2x*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void bnx2x_xmac_init(struct link_params *params, u32 max_speed)
{
	struct bnx2x *bp = params->bp;
	u32 is_port4mode = bnx2x_is_4_port_mode(bp);

	/* In 4-port mode, need to set the mode only once, so if XMAC is
	 * already out of reset, it means the mode has already been set,
	 * and it must not* reset the XMAC again, since it controls both
	 * ports of the path
	 */

	if (((CHIP_NUM(bp) == CHIP_NUM_57840_4_10) ||
	     (CHIP_NUM(bp) == CHIP_NUM_57840_2_20) ||
	     (CHIP_NUM(bp) == CHIP_NUM_57840_OBSOLETE)) &&
	    is_port4mode &&
	    (REG_RD(bp, MISC_REG_RESET_REG_2) &
	     MISC_REGISTERS_RESET_REG_2_XMAC)) {
		DP(NETIF_MSG_LINK,
		   "XMAC already out of reset in 4-port mode\n");
		return;
	}

	/* Hard reset */
	REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_2_CLEAR,
	       MISC_REGISTERS_RESET_REG_2_XMAC);
	usleep_range(1000, 2000);

	REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_2_SET,
	       MISC_REGISTERS_RESET_REG_2_XMAC);
	if (is_port4mode) {
		DP(NETIF_MSG_LINK, "Init XMAC to 2 ports x 10G per path\n");

		/* Set the number of ports on the system side to up to 2 */
		REG_WR(bp, MISC_REG_XMAC_CORE_PORT_MODE, 1);

		/* Set the number of ports on the Warp Core to 10G */
		REG_WR(bp, MISC_REG_XMAC_PHY_PORT_MODE, 3);
	} else {
		/* Set the number of ports on the system side to 1 */
		REG_WR(bp, MISC_REG_XMAC_CORE_PORT_MODE, 0);
		if (max_speed == SPEED_10000) {
			DP(NETIF_MSG_LINK,
			   "Init XMAC to 10G x 1 port per path\n");
			/* Set the number of ports on the Warp Core to 10G */
			REG_WR(bp, MISC_REG_XMAC_PHY_PORT_MODE, 3);
		} else {
			DP(NETIF_MSG_LINK,
			   "Init XMAC to 20G x 2 ports per path\n");
			/* Set the number of ports on the Warp Core to 20G */
			REG_WR(bp, MISC_REG_XMAC_PHY_PORT_MODE, 1);
		}
	}
	/* Soft reset */
	REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_2_CLEAR,
	       MISC_REGISTERS_RESET_REG_2_XMAC_SOFT);
	usleep_range(1000, 2000);

	REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_2_SET,
	       MISC_REGISTERS_RESET_REG_2_XMAC_SOFT);

}