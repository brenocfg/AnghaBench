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
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  location; } ;
struct ethtool_rxnfc {int cmd; TYPE_1__ fs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (struct qede_dev*,char*) ; 
 int EOPNOTSUPP ; 
#define  ETHTOOL_SRXCLSRLDEL 130 
#define  ETHTOOL_SRXCLSRLINS 129 
#define  ETHTOOL_SRXFH 128 
 struct qede_dev* netdev_priv (struct net_device*) ; 
 int qede_add_cls_rule (struct qede_dev*,struct ethtool_rxnfc*) ; 
 int qede_delete_flow_filter (struct qede_dev*,int /*<<< orphan*/ ) ; 
 int qede_set_rss_flags (struct qede_dev*,struct ethtool_rxnfc*) ; 

__attribute__((used)) static int qede_set_rxnfc(struct net_device *dev, struct ethtool_rxnfc *info)
{
	struct qede_dev *edev = netdev_priv(dev);
	int rc;

	switch (info->cmd) {
	case ETHTOOL_SRXFH:
		rc = qede_set_rss_flags(edev, info);
		break;
	case ETHTOOL_SRXCLSRLINS:
		rc = qede_add_cls_rule(edev, info);
		break;
	case ETHTOOL_SRXCLSRLDEL:
		rc = qede_delete_flow_filter(edev, info->fs.location);
		break;
	default:
		DP_INFO(edev, "Command parameters not supported\n");
		rc = -EOPNOTSUPP;
	}

	return rc;
}