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
struct ethtool_rxnfc {int cmd; TYPE_1__ fs; } ;
struct bcm_sysport_priv {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETHTOOL_SRXCLSRLDEL 129 
#define  ETHTOOL_SRXCLSRLINS 128 
 int bcm_sysport_rule_del (struct bcm_sysport_priv*,int /*<<< orphan*/ ) ; 
 int bcm_sysport_rule_set (struct bcm_sysport_priv*,struct ethtool_rxnfc*) ; 
 struct bcm_sysport_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bcm_sysport_set_rxnfc(struct net_device *dev,
				 struct ethtool_rxnfc *nfc)
{
	struct bcm_sysport_priv *priv = netdev_priv(dev);
	int ret = -EOPNOTSUPP;

	switch (nfc->cmd) {
	case ETHTOOL_SRXCLSRLINS:
		ret = bcm_sysport_rule_set(priv, nfc);
		break;
	case ETHTOOL_SRXCLSRLDEL:
		ret = bcm_sysport_rule_del(priv, nfc->fs.location);
		break;
	default:
		break;
	}

	return ret;
}