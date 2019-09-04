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
struct tc_mqprio_qopt {int /*<<< orphan*/  num_tc; int /*<<< orphan*/  hw; } ;
struct qede_dev {int dummy; } ;
struct net_device {int dummy; } ;
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  TC_MQPRIO_HW_OFFLOAD_TCS ; 
#define  TC_SETUP_BLOCK 129 
#define  TC_SETUP_QDISC_MQPRIO 128 
 struct qede_dev* netdev_priv (struct net_device*) ; 
 int qede_setup_tc (struct net_device*,int /*<<< orphan*/ ) ; 
 int qede_setup_tc_block (struct qede_dev*,void*) ; 

__attribute__((used)) static int
qede_setup_tc_offload(struct net_device *dev, enum tc_setup_type type,
		      void *type_data)
{
	struct qede_dev *edev = netdev_priv(dev);
	struct tc_mqprio_qopt *mqprio;

	switch (type) {
	case TC_SETUP_BLOCK:
		return qede_setup_tc_block(edev, type_data);
	case TC_SETUP_QDISC_MQPRIO:
		mqprio = type_data;

		mqprio->hw = TC_MQPRIO_HW_OFFLOAD_TCS;
		return qede_setup_tc(dev, mqprio->num_tc);
	default:
		return -EOPNOTSUPP;
	}
}