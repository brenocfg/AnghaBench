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
struct link_vars {int eee_status; int /*<<< orphan*/  link_status; scalar_t__ line_speed; int /*<<< orphan*/  mac_type; int /*<<< orphan*/  phy_flags; } ;
struct link_params {int port; int /*<<< orphan*/  chip_id; struct bnx2x* bp; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E1x (struct bnx2x*) ; 
 scalar_t__ CHIP_IS_E2 (struct bnx2x*) ; 
 scalar_t__ CHIP_IS_E3 (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  LED_MODE_OFF ; 
 int /*<<< orphan*/  LINK_UPDATE_MASK ; 
 int /*<<< orphan*/  MAC_TYPE_NONE ; 
 scalar_t__ MISC_REG_CPMU_LP_FW_ENABLE_P0 ; 
 scalar_t__ MISC_REG_CPMU_LP_MASK_ENT_P0 ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 scalar_t__ NIG_REG_EGRESS_DRAIN0_MODE ; 
 scalar_t__ NIG_REG_NIG_EMAC0_EN ; 
 int /*<<< orphan*/  PHY_PHYSICAL_LINK_FLAG ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,scalar_t__,int) ; 
 int SHMEM_EEE_ACTIVE_BIT ; 
 int SHMEM_EEE_LP_ADV_STATUS_MASK ; 
 int /*<<< orphan*/  bnx2x_set_bmac_rx (struct bnx2x*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_set_led (struct link_params*,struct link_vars*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_set_umac_rxtx (struct link_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_set_xmac_rxtx (struct link_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_update_mng (struct link_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_update_mng_eee (struct link_params*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int bnx2x_update_link_down(struct link_params *params,
				  struct link_vars *vars)
{
	struct bnx2x *bp = params->bp;
	u8 port = params->port;

	DP(NETIF_MSG_LINK, "Port %x: Link is down\n", port);
	bnx2x_set_led(params, vars, LED_MODE_OFF, 0);
	vars->phy_flags &= ~PHY_PHYSICAL_LINK_FLAG;
	/* Indicate no mac active */
	vars->mac_type = MAC_TYPE_NONE;

	/* Update shared memory */
	vars->link_status &= ~LINK_UPDATE_MASK;
	vars->line_speed = 0;
	bnx2x_update_mng(params, vars->link_status);

	/* Activate nig drain */
	REG_WR(bp, NIG_REG_EGRESS_DRAIN0_MODE + port*4, 1);

	/* Disable emac */
	if (!CHIP_IS_E3(bp))
		REG_WR(bp, NIG_REG_NIG_EMAC0_EN + port*4, 0);

	usleep_range(10000, 20000);
	/* Reset BigMac/Xmac */
	if (CHIP_IS_E1x(bp) ||
	    CHIP_IS_E2(bp))
		bnx2x_set_bmac_rx(bp, params->chip_id, params->port, 0);

	if (CHIP_IS_E3(bp)) {
		/* Prevent LPI Generation by chip */
		REG_WR(bp, MISC_REG_CPMU_LP_FW_ENABLE_P0 + (params->port << 2),
		       0);
		REG_WR(bp, MISC_REG_CPMU_LP_MASK_ENT_P0 + (params->port << 2),
		       0);
		vars->eee_status &= ~(SHMEM_EEE_LP_ADV_STATUS_MASK |
				      SHMEM_EEE_ACTIVE_BIT);

		bnx2x_update_mng_eee(params, vars->eee_status);
		bnx2x_set_xmac_rxtx(params, 0);
		bnx2x_set_umac_rxtx(params, 0);
	}

	return 0;
}