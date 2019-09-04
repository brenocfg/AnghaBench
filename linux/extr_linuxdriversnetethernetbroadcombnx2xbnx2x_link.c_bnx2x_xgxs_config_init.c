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
struct link_vars {int phy_flags; scalar_t__ line_speed; int /*<<< orphan*/  ieee_fc; } ;
struct link_params {scalar_t__ loopback_mode; int feature_config_flags; struct bnx2x* bp; } ;
struct bnx2x_phy {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int FEATURE_CONFIG_OVERRIDE_PREEMPHASIS_ENABLED ; 
 scalar_t__ LOOPBACK_EXT ; 
 scalar_t__ LOOPBACK_XGXS ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 int PHY_SGMII_FLAG ; 
 scalar_t__ SINGLE_MEDIA_DIRECT (struct link_params*) ; 
 scalar_t__ SPEED_AUTO_NEG ; 
 int /*<<< orphan*/  bnx2x_initialize_sgmii_process (struct bnx2x_phy*,struct link_params*,struct link_vars*) ; 
 int /*<<< orphan*/  bnx2x_program_serdes (struct bnx2x_phy*,struct link_params*,struct link_vars*) ; 
 int /*<<< orphan*/  bnx2x_restart_autoneg (struct bnx2x_phy*,struct link_params*,int) ; 
 int /*<<< orphan*/  bnx2x_set_autoneg (struct bnx2x_phy*,struct link_params*,struct link_vars*,int) ; 
 int /*<<< orphan*/  bnx2x_set_brcm_cl37_advertisement (struct bnx2x_phy*,struct link_params*) ; 
 int /*<<< orphan*/  bnx2x_set_ieee_aneg_advertisement (struct bnx2x_phy*,struct link_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_set_preemphasis (struct bnx2x_phy*,struct link_params*) ; 

__attribute__((used)) static void bnx2x_xgxs_config_init(struct bnx2x_phy *phy,
				   struct link_params *params,
				   struct link_vars *vars)
{
	struct bnx2x *bp = params->bp;
	u8 enable_cl73 = (SINGLE_MEDIA_DIRECT(params) ||
			  (params->loopback_mode == LOOPBACK_XGXS));
	if (!(vars->phy_flags & PHY_SGMII_FLAG)) {
		if (SINGLE_MEDIA_DIRECT(params) &&
		    (params->feature_config_flags &
		     FEATURE_CONFIG_OVERRIDE_PREEMPHASIS_ENABLED))
			bnx2x_set_preemphasis(phy, params);

		/* Forced speed requested? */
		if (vars->line_speed != SPEED_AUTO_NEG ||
		    (SINGLE_MEDIA_DIRECT(params) &&
		     params->loopback_mode == LOOPBACK_EXT)) {
			DP(NETIF_MSG_LINK, "not SGMII, no AN\n");

			/* Disable autoneg */
			bnx2x_set_autoneg(phy, params, vars, 0);

			/* Program speed and duplex */
			bnx2x_program_serdes(phy, params, vars);

		} else { /* AN_mode */
			DP(NETIF_MSG_LINK, "not SGMII, AN\n");

			/* AN enabled */
			bnx2x_set_brcm_cl37_advertisement(phy, params);

			/* Program duplex & pause advertisement (for aneg) */
			bnx2x_set_ieee_aneg_advertisement(phy, params,
							  vars->ieee_fc);

			/* Enable autoneg */
			bnx2x_set_autoneg(phy, params, vars, enable_cl73);

			/* Enable and restart AN */
			bnx2x_restart_autoneg(phy, params, enable_cl73);
		}

	} else { /* SGMII mode */
		DP(NETIF_MSG_LINK, "SGMII\n");

		bnx2x_initialize_sgmii_process(phy, params, vars);
	}
}