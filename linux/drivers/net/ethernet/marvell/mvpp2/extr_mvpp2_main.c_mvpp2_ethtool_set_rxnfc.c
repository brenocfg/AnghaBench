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
struct mvpp2_port {int dummy; } ;
struct ethtool_rxnfc {int cmd; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETHTOOL_SRXCLSRLDEL 130 
#define  ETHTOOL_SRXCLSRLINS 129 
#define  ETHTOOL_SRXFH 128 
 int /*<<< orphan*/  mvpp22_rss_is_supported () ; 
 int mvpp2_ethtool_cls_rule_del (struct mvpp2_port*,struct ethtool_rxnfc*) ; 
 int mvpp2_ethtool_cls_rule_ins (struct mvpp2_port*,struct ethtool_rxnfc*) ; 
 int mvpp2_ethtool_rxfh_set (struct mvpp2_port*,struct ethtool_rxnfc*) ; 
 struct mvpp2_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mvpp2_ethtool_set_rxnfc(struct net_device *dev,
				   struct ethtool_rxnfc *info)
{
	struct mvpp2_port *port = netdev_priv(dev);
	int ret = 0;

	if (!mvpp22_rss_is_supported())
		return -EOPNOTSUPP;

	switch (info->cmd) {
	case ETHTOOL_SRXFH:
		ret = mvpp2_ethtool_rxfh_set(port, info);
		break;
	case ETHTOOL_SRXCLSRLINS:
		ret = mvpp2_ethtool_cls_rule_ins(port, info);
		break;
	case ETHTOOL_SRXCLSRLDEL:
		ret = mvpp2_ethtool_cls_rule_del(port, info);
		break;
	default:
		return -EOPNOTSUPP;
	}
	return ret;
}