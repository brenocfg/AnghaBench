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
struct ixgbe_adapter {int dummy; } ;
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  TC_SETUP_BLOCK 129 
#define  TC_SETUP_QDISC_MQPRIO 128 
 int flow_block_cb_setup_simple (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ixgbe_adapter*,struct ixgbe_adapter*,int) ; 
 int /*<<< orphan*/  ixgbe_block_cb_list ; 
 int /*<<< orphan*/  ixgbe_setup_tc_block_cb ; 
 int ixgbe_setup_tc_mqprio (struct net_device*,void*) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int __ixgbe_setup_tc(struct net_device *dev, enum tc_setup_type type,
			    void *type_data)
{
	struct ixgbe_adapter *adapter = netdev_priv(dev);

	switch (type) {
	case TC_SETUP_BLOCK:
		return flow_block_cb_setup_simple(type_data,
						  &ixgbe_block_cb_list,
						  ixgbe_setup_tc_block_cb,
						  adapter, adapter, true);
	case TC_SETUP_QDISC_MQPRIO:
		return ixgbe_setup_tc_mqprio(dev, type_data);
	default:
		return -EOPNOTSUPP;
	}
}