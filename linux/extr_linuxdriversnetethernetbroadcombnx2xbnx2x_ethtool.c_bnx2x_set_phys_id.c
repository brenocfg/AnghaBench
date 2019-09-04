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
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  line_speed; } ;
struct bnx2x {TYPE_1__ link_vars; int /*<<< orphan*/  link_params; } ;
typedef  enum ethtool_phys_id_state { ____Placeholder_ethtool_phys_id_state } ethtool_phys_id_state ;

/* Variables and functions */
 int BNX2X_MSG_ETHTOOL ; 
 int BNX2X_MSG_NVM ; 
 int /*<<< orphan*/  DP (int,char*) ; 
 int EAGAIN ; 
#define  ETHTOOL_ID_ACTIVE 131 
#define  ETHTOOL_ID_INACTIVE 130 
#define  ETHTOOL_ID_OFF 129 
#define  ETHTOOL_ID_ON 128 
 int /*<<< orphan*/  LED_MODE_FRONT_PANEL_OFF ; 
 int /*<<< orphan*/  LED_MODE_ON ; 
 int /*<<< orphan*/  LED_MODE_OPER ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int /*<<< orphan*/  bnx2x_acquire_phy_lock (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_is_nvm_accessible (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_release_phy_lock (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_set_led (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bnx2x* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bnx2x_set_phys_id(struct net_device *dev,
			     enum ethtool_phys_id_state state)
{
	struct bnx2x *bp = netdev_priv(dev);

	if (!bnx2x_is_nvm_accessible(bp)) {
		DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM,
		   "cannot access eeprom when the interface is down\n");
		return -EAGAIN;
	}

	switch (state) {
	case ETHTOOL_ID_ACTIVE:
		return 1;	/* cycle on/off once per second */

	case ETHTOOL_ID_ON:
		bnx2x_acquire_phy_lock(bp);
		bnx2x_set_led(&bp->link_params, &bp->link_vars,
			      LED_MODE_ON, SPEED_1000);
		bnx2x_release_phy_lock(bp);
		break;

	case ETHTOOL_ID_OFF:
		bnx2x_acquire_phy_lock(bp);
		bnx2x_set_led(&bp->link_params, &bp->link_vars,
			      LED_MODE_FRONT_PANEL_OFF, 0);
		bnx2x_release_phy_lock(bp);
		break;

	case ETHTOOL_ID_INACTIVE:
		bnx2x_acquire_phy_lock(bp);
		bnx2x_set_led(&bp->link_params, &bp->link_vars,
			      LED_MODE_OPER,
			      bp->link_vars.line_speed);
		bnx2x_release_phy_lock(bp);
	}

	return 0;
}