#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct ethtool_eeprom {int magic; int /*<<< orphan*/  len; int /*<<< orphan*/  offset; int /*<<< orphan*/  cmd; } ;
struct TYPE_9__ {int /*<<< orphan*/ * phy; } ;
struct TYPE_6__ {int /*<<< orphan*/  pmf; } ;
struct bnx2x {scalar_t__ state; TYPE_4__ link_params; int /*<<< orphan*/  link_vars; TYPE_1__ port; } ;
struct TYPE_8__ {TYPE_2__* port_hw_config; } ;
struct TYPE_7__ {int /*<<< orphan*/  external_phy_config; } ;

/* Variables and functions */
 int BNX2X_MSG_ETHTOOL ; 
 int BNX2X_MSG_NVM ; 
 scalar_t__ BNX2X_STATE_OPEN ; 
 int BP_PORT (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int,char*,...) ; 
 int EAGAIN ; 
 int EINVAL ; 
 size_t EXT_PHY1 ; 
 int /*<<< orphan*/  MISC_REGISTERS_GPIO_0 ; 
 int /*<<< orphan*/  MISC_REGISTERS_GPIO_HIGH ; 
 int /*<<< orphan*/  MISC_REGISTERS_GPIO_LOW ; 
 scalar_t__ PORT_HW_CFG_XGXS_EXT_PHY_TYPE_SFX7101 ; 
 int /*<<< orphan*/  SHMEM_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATS_EVENT_STOP ; 
 scalar_t__ XGXS_EXT_PHY_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_acquire_phy_lock (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_calc_fc_adv (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_ext_phy_hw_reset (struct bnx2x*,int) ; 
 int /*<<< orphan*/  bnx2x_is_nvm_accessible (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_link_report (struct bnx2x*) ; 
 int bnx2x_link_reset (TYPE_4__*,int /*<<< orphan*/ *,int) ; 
 int bnx2x_nvram_write (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bnx2x_phy_init (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnx2x_release_phy_lock (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_set_gpio (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnx2x_sfx7101_sp_sw_reset (struct bnx2x*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnx2x_stats_handle (struct bnx2x*,int /*<<< orphan*/ ) ; 
 TYPE_3__ dev_info ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct bnx2x* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bnx2x_set_eeprom(struct net_device *dev,
			    struct ethtool_eeprom *eeprom, u8 *eebuf)
{
	struct bnx2x *bp = netdev_priv(dev);
	int port = BP_PORT(bp);
	int rc = 0;
	u32 ext_phy_config;

	if (!bnx2x_is_nvm_accessible(bp)) {
		DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM,
		   "cannot access eeprom when the interface is down\n");
		return -EAGAIN;
	}

	DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM, "ethtool_eeprom: cmd %d\n"
	   "  magic 0x%x  offset 0x%x (%d)  len 0x%x (%d)\n",
	   eeprom->cmd, eeprom->magic, eeprom->offset, eeprom->offset,
	   eeprom->len, eeprom->len);

	/* parameters already validated in ethtool_set_eeprom */

	/* PHY eeprom can be accessed only by the PMF */
	if ((eeprom->magic >= 0x50485900) && (eeprom->magic <= 0x504859FF) &&
	    !bp->port.pmf) {
		DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM,
		   "wrong magic or interface is not pmf\n");
		return -EINVAL;
	}

	ext_phy_config =
		SHMEM_RD(bp,
			 dev_info.port_hw_config[port].external_phy_config);

	if (eeprom->magic == 0x50485950) {
		/* 'PHYP' (0x50485950): prepare phy for FW upgrade */
		bnx2x_stats_handle(bp, STATS_EVENT_STOP);

		bnx2x_acquire_phy_lock(bp);
		rc |= bnx2x_link_reset(&bp->link_params,
				       &bp->link_vars, 0);
		if (XGXS_EXT_PHY_TYPE(ext_phy_config) ==
					PORT_HW_CFG_XGXS_EXT_PHY_TYPE_SFX7101)
			bnx2x_set_gpio(bp, MISC_REGISTERS_GPIO_0,
				       MISC_REGISTERS_GPIO_HIGH, port);
		bnx2x_release_phy_lock(bp);
		bnx2x_link_report(bp);

	} else if (eeprom->magic == 0x50485952) {
		/* 'PHYR' (0x50485952): re-init link after FW upgrade */
		if (bp->state == BNX2X_STATE_OPEN) {
			bnx2x_acquire_phy_lock(bp);
			rc |= bnx2x_link_reset(&bp->link_params,
					       &bp->link_vars, 1);

			rc |= bnx2x_phy_init(&bp->link_params,
					     &bp->link_vars);
			bnx2x_release_phy_lock(bp);
			bnx2x_calc_fc_adv(bp);
		}
	} else if (eeprom->magic == 0x53985943) {
		/* 'PHYC' (0x53985943): PHY FW upgrade completed */
		if (XGXS_EXT_PHY_TYPE(ext_phy_config) ==
				       PORT_HW_CFG_XGXS_EXT_PHY_TYPE_SFX7101) {

			/* DSP Remove Download Mode */
			bnx2x_set_gpio(bp, MISC_REGISTERS_GPIO_0,
				       MISC_REGISTERS_GPIO_LOW, port);

			bnx2x_acquire_phy_lock(bp);

			bnx2x_sfx7101_sp_sw_reset(bp,
						&bp->link_params.phy[EXT_PHY1]);

			/* wait 0.5 sec to allow it to run */
			msleep(500);
			bnx2x_ext_phy_hw_reset(bp, port);
			msleep(500);
			bnx2x_release_phy_lock(bp);
		}
	} else
		rc = bnx2x_nvram_write(bp, eeprom->offset, eebuf, eeprom->len);

	return rc;
}