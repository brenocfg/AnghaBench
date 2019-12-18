#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct link_vars {int /*<<< orphan*/  link_up; } ;
struct link_params {size_t port; int hw_led_mode; int num_phys; TYPE_1__* phy; struct bnx2x* bp; } ;
struct bnx2x {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; int /*<<< orphan*/  (* set_link_led ) (TYPE_1__*,struct link_params*,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CHIP_IS_E1 (struct bnx2x*) ; 
 int /*<<< orphan*/  CHIP_IS_E1x (struct bnx2x*) ; 
 int /*<<< orphan*/  CHIP_IS_E2 (struct bnx2x*) ; 
 int /*<<< orphan*/  CHIP_IS_E3 (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,size_t,...) ; 
 int EINVAL ; 
 int EMAC_LED_1000MB_OVERRIDE ; 
 int EMAC_LED_100MB_OVERRIDE ; 
 int EMAC_LED_10MB_OVERRIDE ; 
 int EMAC_LED_OVERRIDE ; 
 int EMAC_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMAC_REG_EMAC_LED ; 
 int /*<<< orphan*/  EMAC_WR (struct bnx2x*,int /*<<< orphan*/ ,int) ; 
 size_t EXT_PHY1 ; 
 int GRCBASE_EMAC0 ; 
 int GRCBASE_EMAC1 ; 
 int LED_BLINK_RATE_VAL_E1X_E2 ; 
 int LED_BLINK_RATE_VAL_E3 ; 
#define  LED_MODE_FRONT_PANEL_OFF 131 
#define  LED_MODE_OFF 130 
#define  LED_MODE_ON 129 
#define  LED_MODE_OPER 128 
 size_t MAX_PHYS ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 size_t NIG_REG_LED_10G_P0 ; 
 size_t NIG_REG_LED_CONTROL_BLINK_RATE_ENA_P0 ; 
 size_t NIG_REG_LED_CONTROL_BLINK_RATE_P0 ; 
 size_t NIG_REG_LED_CONTROL_BLINK_TRAFFIC_P0 ; 
 size_t NIG_REG_LED_CONTROL_OVERRIDE_TRAFFIC_P0 ; 
 size_t NIG_REG_LED_CONTROL_TRAFFIC_P0 ; 
 size_t NIG_REG_LED_MODE_P0 ; 
 int /*<<< orphan*/  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM54618SE ; 
 int /*<<< orphan*/  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8722 ; 
 int /*<<< orphan*/  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8727 ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,size_t,int) ; 
 int SHARED_HW_CFG_LED_EXTPHY2 ; 
 int SHARED_HW_CFG_LED_MAC1 ; 
 int SHARED_HW_CFG_LED_MODE_SHIFT ; 
 int SHARED_HW_CFG_LED_PHY1 ; 
 int /*<<< orphan*/  SINGLE_MEDIA_DIRECT (struct link_params*) ; 
 int SPEED_10 ; 
 int SPEED_100 ; 
 int SPEED_1000 ; 
 int SPEED_10000 ; 
 int SPEED_2500 ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,struct link_params*,size_t) ; 

int bnx2x_set_led(struct link_params *params,
		  struct link_vars *vars, u8 mode, u32 speed)
{
	u8 port = params->port;
	u16 hw_led_mode = params->hw_led_mode;
	int rc = 0;
	u8 phy_idx;
	u32 tmp;
	u32 emac_base = port ? GRCBASE_EMAC1 : GRCBASE_EMAC0;
	struct bnx2x *bp = params->bp;
	DP(NETIF_MSG_LINK, "bnx2x_set_led: port %x, mode %d\n", port, mode);
	DP(NETIF_MSG_LINK, "speed 0x%x, hw_led_mode 0x%x\n",
		 speed, hw_led_mode);
	/* In case */
	for (phy_idx = EXT_PHY1; phy_idx < MAX_PHYS; phy_idx++) {
		if (params->phy[phy_idx].set_link_led) {
			params->phy[phy_idx].set_link_led(
				&params->phy[phy_idx], params, mode);
		}
	}

	switch (mode) {
	case LED_MODE_FRONT_PANEL_OFF:
	case LED_MODE_OFF:
		REG_WR(bp, NIG_REG_LED_10G_P0 + port*4, 0);
		REG_WR(bp, NIG_REG_LED_MODE_P0 + port*4,
		       SHARED_HW_CFG_LED_MAC1);

		tmp = EMAC_RD(bp, EMAC_REG_EMAC_LED);
		if (params->phy[EXT_PHY1].type ==
			PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM54618SE)
			tmp &= ~(EMAC_LED_1000MB_OVERRIDE |
				EMAC_LED_100MB_OVERRIDE |
				EMAC_LED_10MB_OVERRIDE);
		else
			tmp |= EMAC_LED_OVERRIDE;

		EMAC_WR(bp, EMAC_REG_EMAC_LED, tmp);
		break;

	case LED_MODE_OPER:
		/* For all other phys, OPER mode is same as ON, so in case
		 * link is down, do nothing
		 */
		if (!vars->link_up)
			break;
		/* fall through */
	case LED_MODE_ON:
		if (((params->phy[EXT_PHY1].type ==
			  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8727) ||
			 (params->phy[EXT_PHY1].type ==
			  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8722)) &&
		    CHIP_IS_E2(bp) && params->num_phys == 2) {
			/* This is a work-around for E2+8727 Configurations */
			if (mode == LED_MODE_ON ||
				speed == SPEED_10000){
				REG_WR(bp, NIG_REG_LED_MODE_P0 + port*4, 0);
				REG_WR(bp, NIG_REG_LED_10G_P0 + port*4, 1);

				tmp = EMAC_RD(bp, EMAC_REG_EMAC_LED);
				EMAC_WR(bp, EMAC_REG_EMAC_LED,
					(tmp | EMAC_LED_OVERRIDE));
				/* Return here without enabling traffic
				 * LED blink and setting rate in ON mode.
				 * In oper mode, enabling LED blink
				 * and setting rate is needed.
				 */
				if (mode == LED_MODE_ON)
					return rc;
			}
		} else if (SINGLE_MEDIA_DIRECT(params)) {
			/* This is a work-around for HW issue found when link
			 * is up in CL73
			 */
			if ((!CHIP_IS_E3(bp)) ||
			    (CHIP_IS_E3(bp) &&
			     mode == LED_MODE_ON))
				REG_WR(bp, NIG_REG_LED_10G_P0 + port*4, 1);

			if (CHIP_IS_E1x(bp) ||
			    CHIP_IS_E2(bp) ||
			    (mode == LED_MODE_ON))
				REG_WR(bp, NIG_REG_LED_MODE_P0 + port*4, 0);
			else
				REG_WR(bp, NIG_REG_LED_MODE_P0 + port*4,
				       hw_led_mode);
		} else if ((params->phy[EXT_PHY1].type ==
			    PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM54618SE) &&
			   (mode == LED_MODE_ON)) {
			REG_WR(bp, NIG_REG_LED_MODE_P0 + port*4, 0);
			tmp = EMAC_RD(bp, EMAC_REG_EMAC_LED);
			EMAC_WR(bp, EMAC_REG_EMAC_LED, tmp |
				EMAC_LED_OVERRIDE | EMAC_LED_1000MB_OVERRIDE);
			/* Break here; otherwise, it'll disable the
			 * intended override.
			 */
			break;
		} else {
			u32 nig_led_mode = ((params->hw_led_mode <<
					     SHARED_HW_CFG_LED_MODE_SHIFT) ==
					    SHARED_HW_CFG_LED_EXTPHY2) ?
				(SHARED_HW_CFG_LED_PHY1 >>
				 SHARED_HW_CFG_LED_MODE_SHIFT) : hw_led_mode;
			REG_WR(bp, NIG_REG_LED_MODE_P0 + port*4,
			       nig_led_mode);
		}

		REG_WR(bp, NIG_REG_LED_CONTROL_OVERRIDE_TRAFFIC_P0 + port*4, 0);
		/* Set blinking rate to ~15.9Hz */
		if (CHIP_IS_E3(bp))
			REG_WR(bp, NIG_REG_LED_CONTROL_BLINK_RATE_P0 + port*4,
			       LED_BLINK_RATE_VAL_E3);
		else
			REG_WR(bp, NIG_REG_LED_CONTROL_BLINK_RATE_P0 + port*4,
			       LED_BLINK_RATE_VAL_E1X_E2);
		REG_WR(bp, NIG_REG_LED_CONTROL_BLINK_RATE_ENA_P0 +
		       port*4, 1);
		tmp = EMAC_RD(bp, EMAC_REG_EMAC_LED);
		EMAC_WR(bp, EMAC_REG_EMAC_LED,
			(tmp & (~EMAC_LED_OVERRIDE)));

		if (CHIP_IS_E1(bp) &&
		    ((speed == SPEED_2500) ||
		     (speed == SPEED_1000) ||
		     (speed == SPEED_100) ||
		     (speed == SPEED_10))) {
			/* For speeds less than 10G LED scheme is different */
			REG_WR(bp, NIG_REG_LED_CONTROL_OVERRIDE_TRAFFIC_P0
			       + port*4, 1);
			REG_WR(bp, NIG_REG_LED_CONTROL_TRAFFIC_P0 +
			       port*4, 0);
			REG_WR(bp, NIG_REG_LED_CONTROL_BLINK_TRAFFIC_P0 +
			       port*4, 1);
		}
		break;

	default:
		rc = -EINVAL;
		DP(NETIF_MSG_LINK, "bnx2x_set_led: Invalid led mode %d\n",
			 mode);
		break;
	}
	return rc;

}