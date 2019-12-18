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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct ethtool_rxnfc {int cmd; int /*<<< orphan*/  rule_cnt; int /*<<< orphan*/  data; } ;
struct aq_nic_s {int dummy; } ;
struct aq_nic_cfg_s {int /*<<< orphan*/  vecs; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETHTOOL_GRXCLSRLALL 131 
#define  ETHTOOL_GRXCLSRLCNT 130 
#define  ETHTOOL_GRXCLSRULE 129 
#define  ETHTOOL_GRXRINGS 128 
 int aq_get_rxnfc_all_rules (struct aq_nic_s*,struct ethtool_rxnfc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aq_get_rxnfc_count_all_rules (struct aq_nic_s*) ; 
 int aq_get_rxnfc_rule (struct aq_nic_s*,struct ethtool_rxnfc*) ; 
 struct aq_nic_cfg_s* aq_nic_get_cfg (struct aq_nic_s*) ; 
 struct aq_nic_s* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int aq_ethtool_get_rxnfc(struct net_device *ndev,
				struct ethtool_rxnfc *cmd,
				u32 *rule_locs)
{
	struct aq_nic_s *aq_nic = netdev_priv(ndev);
	struct aq_nic_cfg_s *cfg = aq_nic_get_cfg(aq_nic);
	int err = 0;

	switch (cmd->cmd) {
	case ETHTOOL_GRXRINGS:
		cmd->data = cfg->vecs;
		break;
	case ETHTOOL_GRXCLSRLCNT:
		cmd->rule_cnt = aq_get_rxnfc_count_all_rules(aq_nic);
		break;
	case ETHTOOL_GRXCLSRULE:
		err = aq_get_rxnfc_rule(aq_nic, cmd);
		break;
	case ETHTOOL_GRXCLSRLALL:
		err = aq_get_rxnfc_all_rules(aq_nic, cmd, rule_locs);
		break;
	default:
		err = -EOPNOTSUPP;
		break;
	}

	return err;
}