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
struct ethtool_rxnfc {int cmd; } ;
struct aq_nic_s {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETHTOOL_SRXCLSRLDEL 129 
#define  ETHTOOL_SRXCLSRLINS 128 
 int aq_add_rxnfc_rule (struct aq_nic_s*,struct ethtool_rxnfc*) ; 
 int aq_del_rxnfc_rule (struct aq_nic_s*,struct ethtool_rxnfc*) ; 
 struct aq_nic_s* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int aq_ethtool_set_rxnfc(struct net_device *ndev,
				struct ethtool_rxnfc *cmd)
{
	int err = 0;
	struct aq_nic_s *aq_nic = netdev_priv(ndev);

	switch (cmd->cmd) {
	case ETHTOOL_SRXCLSRLINS:
		err = aq_add_rxnfc_rule(aq_nic, cmd);
		break;
	case ETHTOOL_SRXCLSRLDEL:
		err = aq_del_rxnfc_rule(aq_nic, cmd);
		break;
	default:
		err = -EOPNOTSUPP;
		break;
	}

	return err;
}