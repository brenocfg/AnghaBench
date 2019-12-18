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
typedef  int u8 ;
struct TYPE_2__ {int link_status; } ;
struct bnx2x {int /*<<< orphan*/  dev; TYPE_1__ link_vars; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_EXT_LOOPBACK ; 
 int BNX2X_EXT_LOOPBACK_FAILED ; 
 int /*<<< orphan*/  BNX2X_MSG_ETHTOOL ; 
 scalar_t__ BP_NOMCP (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,...) ; 
 int ENODEV ; 
 int LINK_STATUS_SERDES_LINK ; 
 int /*<<< orphan*/  LOAD_LOOPBACK_EXT ; 
 int /*<<< orphan*/  UNLOAD_NORMAL ; 
 int /*<<< orphan*/  bnx2x_netif_start (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_netif_stop (struct bnx2x*,int) ; 
 int bnx2x_nic_load (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_nic_unload (struct bnx2x*,int /*<<< orphan*/ ,int) ; 
 int bnx2x_run_loopback (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_wait_for_link (struct bnx2x*,int,int) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnx2x_test_ext_loopback(struct bnx2x *bp)
{
	int rc;
	u8 is_serdes =
		(bp->link_vars.link_status & LINK_STATUS_SERDES_LINK) > 0;

	if (BP_NOMCP(bp))
		return -ENODEV;

	if (!netif_running(bp->dev))
		return BNX2X_EXT_LOOPBACK_FAILED;

	bnx2x_nic_unload(bp, UNLOAD_NORMAL, false);
	rc = bnx2x_nic_load(bp, LOAD_LOOPBACK_EXT);
	if (rc) {
		DP(BNX2X_MSG_ETHTOOL,
		   "Can't perform self-test, nic_load (for external lb) failed\n");
		return -ENODEV;
	}
	bnx2x_wait_for_link(bp, 1, is_serdes);

	bnx2x_netif_stop(bp, 1);

	rc = bnx2x_run_loopback(bp, BNX2X_EXT_LOOPBACK);
	if (rc)
		DP(BNX2X_MSG_ETHTOOL, "EXT loopback failed  (res %d)\n", rc);

	bnx2x_netif_start(bp);

	return rc;
}