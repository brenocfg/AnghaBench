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
struct i40e_vsi {int /*<<< orphan*/  rss_size; struct i40e_pf* back; } ;
struct i40e_pf {int /*<<< orphan*/  fdir_pf_active_filters; } ;
struct i40e_netdev_priv {struct i40e_vsi* vsi; } ;
struct ethtool_rxnfc {int cmd; int /*<<< orphan*/  data; int /*<<< orphan*/  rule_cnt; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETHTOOL_GRXCLSRLALL 132 
#define  ETHTOOL_GRXCLSRLCNT 131 
#define  ETHTOOL_GRXCLSRULE 130 
#define  ETHTOOL_GRXFH 129 
#define  ETHTOOL_GRXRINGS 128 
 int i40e_get_ethtool_fdir_all (struct i40e_pf*,struct ethtool_rxnfc*,int /*<<< orphan*/ *) ; 
 int i40e_get_ethtool_fdir_entry (struct i40e_pf*,struct ethtool_rxnfc*) ; 
 int /*<<< orphan*/  i40e_get_fd_cnt_all (struct i40e_pf*) ; 
 int i40e_get_rss_hash_opts (struct i40e_pf*,struct ethtool_rxnfc*) ; 
 struct i40e_netdev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int i40e_get_rxnfc(struct net_device *netdev, struct ethtool_rxnfc *cmd,
			  u32 *rule_locs)
{
	struct i40e_netdev_priv *np = netdev_priv(netdev);
	struct i40e_vsi *vsi = np->vsi;
	struct i40e_pf *pf = vsi->back;
	int ret = -EOPNOTSUPP;

	switch (cmd->cmd) {
	case ETHTOOL_GRXRINGS:
		cmd->data = vsi->rss_size;
		ret = 0;
		break;
	case ETHTOOL_GRXFH:
		ret = i40e_get_rss_hash_opts(pf, cmd);
		break;
	case ETHTOOL_GRXCLSRLCNT:
		cmd->rule_cnt = pf->fdir_pf_active_filters;
		/* report total rule count */
		cmd->data = i40e_get_fd_cnt_all(pf);
		ret = 0;
		break;
	case ETHTOOL_GRXCLSRULE:
		ret = i40e_get_ethtool_fdir_entry(pf, cmd);
		break;
	case ETHTOOL_GRXCLSRLALL:
		ret = i40e_get_ethtool_fdir_all(pf, cmd, rule_locs);
		break;
	default:
		break;
	}

	return ret;
}