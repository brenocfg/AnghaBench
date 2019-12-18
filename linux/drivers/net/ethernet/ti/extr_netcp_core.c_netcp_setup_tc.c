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
struct tc_mqprio_qopt {int num_tc; int /*<<< orphan*/  hw; } ;
struct net_device {int real_num_tx_queues; } ;
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  TC_MQPRIO_HW_OFFLOAD_TCS ; 
 int TC_SETUP_QDISC_MQPRIO ; 
 int /*<<< orphan*/  netdev_reset_tc (struct net_device*) ; 
 int /*<<< orphan*/  netdev_set_num_tc (struct net_device*,int) ; 
 int /*<<< orphan*/  netdev_set_tc_queue (struct net_device*,int,int,int) ; 

__attribute__((used)) static int netcp_setup_tc(struct net_device *dev, enum tc_setup_type type,
			  void *type_data)
{
	struct tc_mqprio_qopt *mqprio = type_data;
	u8 num_tc;
	int i;

	/* setup tc must be called under rtnl lock */
	ASSERT_RTNL();

	if (type != TC_SETUP_QDISC_MQPRIO)
		return -EOPNOTSUPP;

	mqprio->hw = TC_MQPRIO_HW_OFFLOAD_TCS;
	num_tc = mqprio->num_tc;

	/* Sanity-check the number of traffic classes requested */
	if ((dev->real_num_tx_queues <= 1) ||
	    (dev->real_num_tx_queues < num_tc))
		return -EINVAL;

	/* Configure traffic class to queue mappings */
	if (num_tc) {
		netdev_set_num_tc(dev, num_tc);
		for (i = 0; i < num_tc; i++)
			netdev_set_tc_queue(dev, i, 1, i);
	} else {
		netdev_reset_tc(dev);
	}

	return 0;
}