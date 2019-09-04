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
struct net_device {int dummy; } ;
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  TC_MQPRIO_HW_OFFLOAD_TCS ; 
#define  TC_SETUP_BLOCK 129 
#define  TC_SETUP_QDISC_MQPRIO 128 
 int bnxt_setup_mq_tc (struct net_device*,int /*<<< orphan*/ ) ; 
 int bnxt_setup_tc_block (struct net_device*,void*) ; 

__attribute__((used)) static int bnxt_setup_tc(struct net_device *dev, enum tc_setup_type type,
			 void *type_data)
{
	switch (type) {
	case TC_SETUP_BLOCK:
		return bnxt_setup_tc_block(dev, type_data);
	case TC_SETUP_QDISC_MQPRIO: {
		struct tc_mqprio_qopt *mqprio = type_data;

		mqprio->hw = TC_MQPRIO_HW_OFFLOAD_TCS;

		return bnxt_setup_mq_tc(dev, mqprio->num_tc);
	}
	default:
		return -EOPNOTSUPP;
	}
}