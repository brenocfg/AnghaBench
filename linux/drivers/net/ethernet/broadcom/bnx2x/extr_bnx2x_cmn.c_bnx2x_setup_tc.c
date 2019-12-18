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
struct net_device {int dummy; } ;
struct bnx2x {int max_cos; int /*<<< orphan*/ * prio_to_cos; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  BNX2X_ERR (char*,int,...) ; 
 int BNX2X_MAX_PRIORITY ; 
 int BNX2X_MSG_SP ; 
 int BNX2X_NUM_ETH_QUEUES (struct bnx2x*) ; 
 int BNX2X_NUM_NON_CNIC_QUEUES (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int,char*,int,int,...) ; 
 int EINVAL ; 
 int NETIF_MSG_IFUP ; 
 int /*<<< orphan*/  bnx2x_get_c2s_mapping (struct bnx2x*,int*,int*) ; 
 struct bnx2x* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_reset_tc (struct net_device*) ; 
 scalar_t__ netdev_set_num_tc (struct net_device*,int) ; 
 int /*<<< orphan*/  netdev_set_prio_tc_map (struct net_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_set_tc_queue (struct net_device*,int,int,int) ; 

int bnx2x_setup_tc(struct net_device *dev, u8 num_tc)
{
	struct bnx2x *bp = netdev_priv(dev);
	u8 c2s_map[BNX2X_MAX_PRIORITY], c2s_def;
	int cos, prio, count, offset;

	/* setup tc must be called under rtnl lock */
	ASSERT_RTNL();

	/* no traffic classes requested. Aborting */
	if (!num_tc) {
		netdev_reset_tc(dev);
		return 0;
	}

	/* requested to support too many traffic classes */
	if (num_tc > bp->max_cos) {
		BNX2X_ERR("support for too many traffic classes requested: %d. Max supported is %d\n",
			  num_tc, bp->max_cos);
		return -EINVAL;
	}

	/* declare amount of supported traffic classes */
	if (netdev_set_num_tc(dev, num_tc)) {
		BNX2X_ERR("failed to declare %d traffic classes\n", num_tc);
		return -EINVAL;
	}

	bnx2x_get_c2s_mapping(bp, c2s_map, &c2s_def);

	/* configure priority to traffic class mapping */
	for (prio = 0; prio < BNX2X_MAX_PRIORITY; prio++) {
		int outer_prio = c2s_map[prio];

		netdev_set_prio_tc_map(dev, prio, bp->prio_to_cos[outer_prio]);
		DP(BNX2X_MSG_SP | NETIF_MSG_IFUP,
		   "mapping priority %d to tc %d\n",
		   outer_prio, bp->prio_to_cos[outer_prio]);
	}

	/* Use this configuration to differentiate tc0 from other COSes
	   This can be used for ets or pfc, and save the effort of setting
	   up a multio class queue disc or negotiating DCBX with a switch
	netdev_set_prio_tc_map(dev, 0, 0);
	DP(BNX2X_MSG_SP, "mapping priority %d to tc %d\n", 0, 0);
	for (prio = 1; prio < 16; prio++) {
		netdev_set_prio_tc_map(dev, prio, 1);
		DP(BNX2X_MSG_SP, "mapping priority %d to tc %d\n", prio, 1);
	} */

	/* configure traffic class to transmission queue mapping */
	for (cos = 0; cos < bp->max_cos; cos++) {
		count = BNX2X_NUM_ETH_QUEUES(bp);
		offset = cos * BNX2X_NUM_NON_CNIC_QUEUES(bp);
		netdev_set_tc_queue(dev, cos, count, offset);
		DP(BNX2X_MSG_SP | NETIF_MSG_IFUP,
		   "mapping tc %d to offset %d count %d\n",
		   cos, offset, count);
	}

	return 0;
}