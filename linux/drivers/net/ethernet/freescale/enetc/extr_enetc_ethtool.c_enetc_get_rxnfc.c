#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct net_device {int dummy; } ;
struct TYPE_4__ {size_t location; } ;
struct ethtool_rxnfc {int cmd; int data; int rule_cnt; TYPE_1__ fs; } ;
struct enetc_ndev_priv {int num_rx_rings; TYPE_3__* cls_rules; TYPE_2__* si; } ;
struct TYPE_6__ {int /*<<< orphan*/  used; TYPE_1__ fs; } ;
struct TYPE_5__ {int num_fs_entries; } ;

/* Variables and functions */
 int EINVAL ; 
 int EMSGSIZE ; 
 int EOPNOTSUPP ; 
#define  ETHTOOL_GRXCLSRLALL 132 
#define  ETHTOOL_GRXCLSRLCNT 131 
#define  ETHTOOL_GRXCLSRULE 130 
#define  ETHTOOL_GRXFH 129 
#define  ETHTOOL_GRXRINGS 128 
 int enetc_get_rsshash (struct ethtool_rxnfc*) ; 
 struct enetc_ndev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int enetc_get_rxnfc(struct net_device *ndev, struct ethtool_rxnfc *rxnfc,
			   u32 *rule_locs)
{
	struct enetc_ndev_priv *priv = netdev_priv(ndev);
	int i, j;

	switch (rxnfc->cmd) {
	case ETHTOOL_GRXRINGS:
		rxnfc->data = priv->num_rx_rings;
		break;
	case ETHTOOL_GRXFH:
		/* get RSS hash config */
		return enetc_get_rsshash(rxnfc);
	case ETHTOOL_GRXCLSRLCNT:
		/* total number of entries */
		rxnfc->data = priv->si->num_fs_entries;
		/* number of entries in use */
		rxnfc->rule_cnt = 0;
		for (i = 0; i < priv->si->num_fs_entries; i++)
			if (priv->cls_rules[i].used)
				rxnfc->rule_cnt++;
		break;
	case ETHTOOL_GRXCLSRULE:
		if (rxnfc->fs.location >= priv->si->num_fs_entries)
			return -EINVAL;

		/* get entry x */
		rxnfc->fs = priv->cls_rules[rxnfc->fs.location].fs;
		break;
	case ETHTOOL_GRXCLSRLALL:
		/* total number of entries */
		rxnfc->data = priv->si->num_fs_entries;
		/* array of indexes of used entries */
		j = 0;
		for (i = 0; i < priv->si->num_fs_entries; i++) {
			if (!priv->cls_rules[i].used)
				continue;
			if (j == rxnfc->rule_cnt)
				return -EMSGSIZE;
			rule_locs[j++] = i;
		}
		/* number of entries in use */
		rxnfc->rule_cnt = j;
		break;
	default:
		return -EOPNOTSUPP;
	}

	return 0;
}