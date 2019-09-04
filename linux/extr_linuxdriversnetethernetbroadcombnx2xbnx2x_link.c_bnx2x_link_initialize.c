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
struct link_vars {scalar_t__ line_speed; int /*<<< orphan*/  link_status; } ;
struct link_params {scalar_t__ loopback_mode; int num_phys; int port; struct bnx2x_phy* phy; struct bnx2x* bp; } ;
struct bnx2x_phy {scalar_t__ req_line_speed; int flags; int supported; int /*<<< orphan*/  (* config_init ) (struct bnx2x_phy*,struct link_params*,struct link_vars*) ;} ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E1x (struct bnx2x*) ; 
 scalar_t__ CHIP_IS_E2 (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 size_t EXT_PHY1 ; 
 int EXT_PHY2 ; 
 int FLAGS_INIT_XGXS_FIRST ; 
 size_t INT_PHY ; 
 int /*<<< orphan*/  LINK_STATUS_SERDES_LINK ; 
 scalar_t__ LOOPBACK_EXT_PHY ; 
 scalar_t__ LOOPBACK_XGXS ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 int NIG_MASK_MI_INT ; 
 scalar_t__ NIG_REG_STATUS_INTERRUPT_PORT0 ; 
 int NIG_STATUS_SERDES0_LINK_STATUS ; 
 int NIG_STATUS_XGXS0_LINK10G ; 
 int NIG_STATUS_XGXS0_LINK_STATUS ; 
 scalar_t__ PORT_HW_CFG_PHY_SELECTION_FIRST_PHY ; 
 scalar_t__ SINGLE_MEDIA_DIRECT (struct link_params*) ; 
 scalar_t__ SPEED_AUTO_NEG ; 
 int SUPPORTED_FIBRE ; 
 int /*<<< orphan*/  USES_WARPCORE (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_bits_dis (struct bnx2x*,scalar_t__,int) ; 
 scalar_t__ bnx2x_phy_selection (struct link_params*) ; 
 int /*<<< orphan*/  bnx2x_prepare_xgxs (struct bnx2x_phy*,struct link_params*,struct link_vars*) ; 
 int /*<<< orphan*/  bnx2x_set_parallel_detection (struct bnx2x_phy*,struct link_params*) ; 
 int /*<<< orphan*/  stub1 (struct bnx2x_phy*,struct link_params*,struct link_vars*) ; 
 int /*<<< orphan*/  stub2 (struct bnx2x_phy*,struct link_params*,struct link_vars*) ; 

__attribute__((used)) static int bnx2x_link_initialize(struct link_params *params,
				 struct link_vars *vars)
{
	u8 phy_index, non_ext_phy;
	struct bnx2x *bp = params->bp;
	/* In case of external phy existence, the line speed would be the
	 * line speed linked up by the external phy. In case it is direct
	 * only, then the line_speed during initialization will be
	 * equal to the req_line_speed
	 */
	vars->line_speed = params->phy[INT_PHY].req_line_speed;

	/* Initialize the internal phy in case this is a direct board
	 * (no external phys), or this board has external phy which requires
	 * to first.
	 */
	if (!USES_WARPCORE(bp))
		bnx2x_prepare_xgxs(&params->phy[INT_PHY], params, vars);
	/* init ext phy and enable link state int */
	non_ext_phy = (SINGLE_MEDIA_DIRECT(params) ||
		       (params->loopback_mode == LOOPBACK_XGXS));

	if (non_ext_phy ||
	    (params->phy[EXT_PHY1].flags & FLAGS_INIT_XGXS_FIRST) ||
	    (params->loopback_mode == LOOPBACK_EXT_PHY)) {
		struct bnx2x_phy *phy = &params->phy[INT_PHY];
		if (vars->line_speed == SPEED_AUTO_NEG &&
		    (CHIP_IS_E1x(bp) ||
		     CHIP_IS_E2(bp)))
			bnx2x_set_parallel_detection(phy, params);
		if (params->phy[INT_PHY].config_init)
			params->phy[INT_PHY].config_init(phy, params, vars);
	}

	/* Re-read this value in case it was changed inside config_init due to
	 * limitations of optic module
	 */
	vars->line_speed = params->phy[INT_PHY].req_line_speed;

	/* Init external phy*/
	if (non_ext_phy) {
		if (params->phy[INT_PHY].supported &
		    SUPPORTED_FIBRE)
			vars->link_status |= LINK_STATUS_SERDES_LINK;
	} else {
		for (phy_index = EXT_PHY1; phy_index < params->num_phys;
		      phy_index++) {
			/* No need to initialize second phy in case of first
			 * phy only selection. In case of second phy, we do
			 * need to initialize the first phy, since they are
			 * connected.
			 */
			if (params->phy[phy_index].supported &
			    SUPPORTED_FIBRE)
				vars->link_status |= LINK_STATUS_SERDES_LINK;

			if (phy_index == EXT_PHY2 &&
			    (bnx2x_phy_selection(params) ==
			     PORT_HW_CFG_PHY_SELECTION_FIRST_PHY)) {
				DP(NETIF_MSG_LINK,
				   "Not initializing second phy\n");
				continue;
			}
			params->phy[phy_index].config_init(
				&params->phy[phy_index],
				params, vars);
		}
	}
	/* Reset the interrupt indication after phy was initialized */
	bnx2x_bits_dis(bp, NIG_REG_STATUS_INTERRUPT_PORT0 +
		       params->port*4,
		       (NIG_STATUS_XGXS0_LINK10G |
			NIG_STATUS_XGXS0_LINK_STATUS |
			NIG_STATUS_SERDES0_LINK_STATUS |
			NIG_MASK_MI_INT));
	return 0;
}