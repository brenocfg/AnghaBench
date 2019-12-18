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
struct igc_adapter {int dummy; } ;
struct ethtool_rxnfc {int cmd; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETHTOOL_SRXCLSRLDEL 130 
#define  ETHTOOL_SRXCLSRLINS 129 
#define  ETHTOOL_SRXFH 128 
 int igc_add_ethtool_nfc_entry (struct igc_adapter*,struct ethtool_rxnfc*) ; 
 int igc_del_ethtool_nfc_entry (struct igc_adapter*,struct ethtool_rxnfc*) ; 
 int igc_set_rss_hash_opt (struct igc_adapter*,struct ethtool_rxnfc*) ; 
 struct igc_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int igc_set_rxnfc(struct net_device *dev, struct ethtool_rxnfc *cmd)
{
	struct igc_adapter *adapter = netdev_priv(dev);
	int ret = -EOPNOTSUPP;

	switch (cmd->cmd) {
	case ETHTOOL_SRXFH:
		ret = igc_set_rss_hash_opt(adapter, cmd);
		break;
	case ETHTOOL_SRXCLSRLINS:
		ret = igc_add_ethtool_nfc_entry(adapter, cmd);
		break;
	case ETHTOOL_SRXCLSRLDEL:
		ret = igc_del_ethtool_nfc_entry(adapter, cmd);
	default:
		break;
	}

	return ret;
}