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
struct igb_adapter {int dummy; } ;
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  TC_SETUP_BLOCK 130 
#define  TC_SETUP_QDISC_CBS 129 
#define  TC_SETUP_QDISC_ETF 128 
 int flow_block_cb_setup_simple (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct igb_adapter*,struct igb_adapter*,int) ; 
 int /*<<< orphan*/  igb_block_cb_list ; 
 int igb_offload_cbs (struct igb_adapter*,void*) ; 
 int igb_offload_txtime (struct igb_adapter*,void*) ; 
 int /*<<< orphan*/  igb_setup_tc_block_cb ; 
 struct igb_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int igb_setup_tc(struct net_device *dev, enum tc_setup_type type,
			void *type_data)
{
	struct igb_adapter *adapter = netdev_priv(dev);

	switch (type) {
	case TC_SETUP_QDISC_CBS:
		return igb_offload_cbs(adapter, type_data);
	case TC_SETUP_BLOCK:
		return flow_block_cb_setup_simple(type_data,
						  &igb_block_cb_list,
						  igb_setup_tc_block_cb,
						  adapter, adapter, true);

	case TC_SETUP_QDISC_ETF:
		return igb_offload_txtime(adapter, type_data);

	default:
		return -EOPNOTSUPP;
	}
}