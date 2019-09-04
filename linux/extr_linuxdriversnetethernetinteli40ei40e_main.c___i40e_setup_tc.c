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
struct net_device {int dummy; } ;
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  TC_SETUP_BLOCK 129 
#define  TC_SETUP_QDISC_MQPRIO 128 
 int i40e_setup_tc (struct net_device*,void*) ; 
 int i40e_setup_tc_block (struct net_device*,void*) ; 

__attribute__((used)) static int __i40e_setup_tc(struct net_device *netdev, enum tc_setup_type type,
			   void *type_data)
{
	switch (type) {
	case TC_SETUP_QDISC_MQPRIO:
		return i40e_setup_tc(netdev, type_data);
	case TC_SETUP_BLOCK:
		return i40e_setup_tc_block(netdev, type_data);
	default:
		return -EOPNOTSUPP;
	}
}