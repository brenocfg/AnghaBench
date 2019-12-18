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
struct iavf_adapter {int dummy; } ;
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  TC_SETUP_BLOCK 129 
#define  TC_SETUP_QDISC_MQPRIO 128 
 int __iavf_setup_tc (struct net_device*,void*) ; 
 int flow_block_cb_setup_simple (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct iavf_adapter*,struct iavf_adapter*,int) ; 
 int /*<<< orphan*/  iavf_block_cb_list ; 
 int /*<<< orphan*/  iavf_setup_tc_block_cb ; 
 struct iavf_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int iavf_setup_tc(struct net_device *netdev, enum tc_setup_type type,
			 void *type_data)
{
	struct iavf_adapter *adapter = netdev_priv(netdev);

	switch (type) {
	case TC_SETUP_QDISC_MQPRIO:
		return __iavf_setup_tc(netdev, type_data);
	case TC_SETUP_BLOCK:
		return flow_block_cb_setup_simple(type_data,
						  &iavf_block_cb_list,
						  iavf_setup_tc_block_cb,
						  adapter, adapter, true);
	default:
		return -EOPNOTSUPP;
	}
}