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
struct port_info {int /*<<< orphan*/  port_id; } ;
struct net_device {int dummy; } ;
struct adapter {int flags; int /*<<< orphan*/  pdev_dev; } ;
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;

/* Variables and functions */
 int CXGB4_FULL_INIT_DONE ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  TC_SETUP_CLSFLOWER 129 
#define  TC_SETUP_CLSU32 128 
 int cxgb_setup_tc_cls_u32 (struct net_device*,void*) ; 
 int cxgb_setup_tc_flower (struct net_device*,void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct adapter* netdev2adap (struct net_device*) ; 
 struct port_info* netdev2pinfo (struct net_device*) ; 
 int /*<<< orphan*/  tc_cls_can_offload_and_chain0 (struct net_device*,void*) ; 

__attribute__((used)) static int cxgb_setup_tc_block_cb(enum tc_setup_type type, void *type_data,
				  void *cb_priv)
{
	struct net_device *dev = cb_priv;
	struct port_info *pi = netdev2pinfo(dev);
	struct adapter *adap = netdev2adap(dev);

	if (!(adap->flags & CXGB4_FULL_INIT_DONE)) {
		dev_err(adap->pdev_dev,
			"Failed to setup tc on port %d. Link Down?\n",
			pi->port_id);
		return -EINVAL;
	}

	if (!tc_cls_can_offload_and_chain0(dev, type_data))
		return -EOPNOTSUPP;

	switch (type) {
	case TC_SETUP_CLSU32:
		return cxgb_setup_tc_cls_u32(dev, type_data);
	case TC_SETUP_CLSFLOWER:
		return cxgb_setup_tc_flower(dev, type_data);
	default:
		return -EOPNOTSUPP;
	}
}