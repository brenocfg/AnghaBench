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
struct link_vars {scalar_t__ phy_flags; scalar_t__ link_up; } ;
struct link_params {int port; int /*<<< orphan*/  chip_id; int /*<<< orphan*/  lfa_base; int /*<<< orphan*/  link_flags; struct bnx2x* bp; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E3 (struct bnx2x*) ; 
 scalar_t__ NIG_REG_EGRESS_DRAIN0_MODE ; 
 int /*<<< orphan*/  PHY_INITIALIZED ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,scalar_t__,int) ; 
 int bnx2x_link_reset (struct link_params*,struct link_vars*,int) ; 
 int /*<<< orphan*/  bnx2x_set_bmac_rx (struct bnx2x*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bnx2x_set_rx_filter (struct link_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_set_umac_rxtx (struct link_params*,int) ; 
 int /*<<< orphan*/  bnx2x_set_xmac_rxtx (struct link_params*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int bnx2x_lfa_reset(struct link_params *params,
			       struct link_vars *vars)
{
	struct bnx2x *bp = params->bp;
	vars->link_up = 0;
	vars->phy_flags = 0;
	params->link_flags &= ~PHY_INITIALIZED;
	if (!params->lfa_base)
		return bnx2x_link_reset(params, vars, 1);
	/*
	 * Activate NIG drain so that during this time the device won't send
	 * anything while it is unable to response.
	 */
	REG_WR(bp, NIG_REG_EGRESS_DRAIN0_MODE + params->port*4, 1);

	/*
	 * Close gracefully the gate from BMAC to NIG such that no half packets
	 * are passed.
	 */
	if (!CHIP_IS_E3(bp))
		bnx2x_set_bmac_rx(bp, params->chip_id, params->port, 0);

	if (CHIP_IS_E3(bp)) {
		bnx2x_set_xmac_rxtx(params, 0);
		bnx2x_set_umac_rxtx(params, 0);
	}
	/* Wait 10ms for the pipe to clean up*/
	usleep_range(10000, 20000);

	/* Clean the NIG-BRB using the network filters in a way that will
	 * not cut a packet in the middle.
	 */
	bnx2x_set_rx_filter(params, 0);

	/*
	 * Re-open the gate between the BMAC and the NIG, after verifying the
	 * gate to the BRB is closed, otherwise packets may arrive to the
	 * firmware before driver had initialized it. The target is to achieve
	 * minimum management protocol down time.
	 */
	if (!CHIP_IS_E3(bp))
		bnx2x_set_bmac_rx(bp, params->chip_id, params->port, 1);

	if (CHIP_IS_E3(bp)) {
		bnx2x_set_xmac_rxtx(params, 1);
		bnx2x_set_umac_rxtx(params, 1);
	}
	/* Disable NIG drain */
	REG_WR(bp, NIG_REG_EGRESS_DRAIN0_MODE + params->port*4, 0);
	return 0;
}