#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct bnx2x {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_1__* port_hw_config; } ;
struct TYPE_3__ {int /*<<< orphan*/  external_phy_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_SP_RTNL_FAN_FAILURE ; 
 int BP_PORT (struct bnx2x*) ; 
 int /*<<< orphan*/  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_FAILURE ; 
 int /*<<< orphan*/  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_MASK ; 
 int /*<<< orphan*/  SHMEM_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHMEM_WR (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_schedule_sp_rtnl (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ dev_info ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void bnx2x_fan_failure(struct bnx2x *bp)
{
	int port = BP_PORT(bp);
	u32 ext_phy_config;
	/* mark the failure */
	ext_phy_config =
		SHMEM_RD(bp,
			 dev_info.port_hw_config[port].external_phy_config);

	ext_phy_config &= ~PORT_HW_CFG_XGXS_EXT_PHY_TYPE_MASK;
	ext_phy_config |= PORT_HW_CFG_XGXS_EXT_PHY_TYPE_FAILURE;
	SHMEM_WR(bp, dev_info.port_hw_config[port].external_phy_config,
		 ext_phy_config);

	/* log the failure */
	netdev_err(bp->dev, "Fan Failure on Network Controller has caused the driver to shutdown the card to prevent permanent damage.\n"
			    "Please contact OEM Support for assistance\n");

	/* Schedule device reset (unload)
	 * This is due to some boards consuming sufficient power when driver is
	 * up to overheat if fan fails.
	 */
	bnx2x_schedule_sp_rtnl(bp, BNX2X_SP_RTNL_FAN_FAILURE, 0);
}