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
struct net_device {int dummy; } ;
struct TYPE_6__ {size_t location; int /*<<< orphan*/  ring_cookie; } ;
struct ethtool_rxnfc {int cmd; TYPE_3__ fs; } ;
struct enetc_ndev_priv {TYPE_1__* cls_rules; TYPE_2__* si; int /*<<< orphan*/  num_rx_rings; } ;
struct TYPE_5__ {size_t num_fs_entries; } ;
struct TYPE_4__ {int used; TYPE_3__ fs; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  ETHTOOL_SRXCLSRLDEL 129 
#define  ETHTOOL_SRXCLSRLINS 128 
 int /*<<< orphan*/  RX_CLS_FLOW_DISC ; 
 int enetc_set_cls_entry (TYPE_2__*,TYPE_3__*,int) ; 
 struct enetc_ndev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int enetc_set_rxnfc(struct net_device *ndev, struct ethtool_rxnfc *rxnfc)
{
	struct enetc_ndev_priv *priv = netdev_priv(ndev);
	int err;

	switch (rxnfc->cmd) {
	case ETHTOOL_SRXCLSRLINS:
		if (rxnfc->fs.location >= priv->si->num_fs_entries)
			return -EINVAL;

		if (rxnfc->fs.ring_cookie >= priv->num_rx_rings &&
		    rxnfc->fs.ring_cookie != RX_CLS_FLOW_DISC)
			return -EINVAL;

		err = enetc_set_cls_entry(priv->si, &rxnfc->fs, true);
		if (err)
			return err;
		priv->cls_rules[rxnfc->fs.location].fs = rxnfc->fs;
		priv->cls_rules[rxnfc->fs.location].used = 1;
		break;
	case ETHTOOL_SRXCLSRLDEL:
		if (rxnfc->fs.location >= priv->si->num_fs_entries)
			return -EINVAL;

		err = enetc_set_cls_entry(priv->si, &rxnfc->fs, false);
		if (err)
			return err;
		priv->cls_rules[rxnfc->fs.location].used = 0;
		break;
	default:
		return -EOPNOTSUPP;
	}

	return 0;
}