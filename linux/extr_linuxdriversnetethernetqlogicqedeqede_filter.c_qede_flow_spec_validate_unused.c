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
struct qede_dev {int dummy; } ;
struct TYPE_2__ {scalar_t__* data; scalar_t__ vlan_tci; scalar_t__ vlan_etype; } ;
struct ethtool_rx_flow_spec {int flow_type; TYPE_1__ h_ext; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (struct qede_dev*,char*) ; 
 int EOPNOTSUPP ; 
 int FLOW_EXT ; 
 int FLOW_MAC_EXT ; 

__attribute__((used)) static int qede_flow_spec_validate_unused(struct qede_dev *edev,
					  struct ethtool_rx_flow_spec *fs)
{
	if (fs->flow_type & FLOW_MAC_EXT) {
		DP_INFO(edev, "Don't support MAC extensions\n");
		return -EOPNOTSUPP;
	}

	if ((fs->flow_type & FLOW_EXT) &&
	    (fs->h_ext.vlan_etype || fs->h_ext.vlan_tci)) {
		DP_INFO(edev, "Don't support vlan-based classification\n");
		return -EOPNOTSUPP;
	}

	if ((fs->flow_type & FLOW_EXT) &&
	    (fs->h_ext.data[0] || fs->h_ext.data[1])) {
		DP_INFO(edev, "Don't support user defined data\n");
		return -EOPNOTSUPP;
	}

	return 0;
}