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
struct net_device {int /*<<< orphan*/ * ethtool_ops; } ;
struct enetc_ndev_priv {int /*<<< orphan*/  si; } ;

/* Variables and functions */
 int /*<<< orphan*/  enetc_pf_ethtool_ops ; 
 scalar_t__ enetc_si_is_pf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enetc_vf_ethtool_ops ; 
 struct enetc_ndev_priv* netdev_priv (struct net_device*) ; 

void enetc_set_ethtool_ops(struct net_device *ndev)
{
	struct enetc_ndev_priv *priv = netdev_priv(ndev);

	if (enetc_si_is_pf(priv->si))
		ndev->ethtool_ops = &enetc_pf_ethtool_ops;
	else
		ndev->ethtool_ops = &enetc_vf_ethtool_ops;
}