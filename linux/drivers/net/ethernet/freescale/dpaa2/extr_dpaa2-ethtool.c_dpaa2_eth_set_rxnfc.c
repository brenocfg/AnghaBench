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
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  location; } ;
struct ethtool_rxnfc {int cmd; int data; TYPE_1__ fs; } ;

/* Variables and functions */
 int DPAA2_RXH_SUPPORTED ; 
 int EOPNOTSUPP ; 
#define  ETHTOOL_SRXCLSRLDEL 130 
#define  ETHTOOL_SRXCLSRLINS 129 
#define  ETHTOOL_SRXFH 128 
 int dpaa2_eth_set_hash (struct net_device*,int) ; 
 int update_cls_rule (struct net_device*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dpaa2_eth_set_rxnfc(struct net_device *net_dev,
			       struct ethtool_rxnfc *rxnfc)
{
	int err = 0;

	switch (rxnfc->cmd) {
	case ETHTOOL_SRXFH:
		if ((rxnfc->data & DPAA2_RXH_SUPPORTED) != rxnfc->data)
			return -EOPNOTSUPP;
		err = dpaa2_eth_set_hash(net_dev, rxnfc->data);
		break;
	case ETHTOOL_SRXCLSRLINS:
		err = update_cls_rule(net_dev, &rxnfc->fs, rxnfc->fs.location);
		break;
	case ETHTOOL_SRXCLSRLDEL:
		err = update_cls_rule(net_dev, NULL, rxnfc->fs.location);
		break;
	default:
		err = -EOPNOTSUPP;
	}

	return err;
}