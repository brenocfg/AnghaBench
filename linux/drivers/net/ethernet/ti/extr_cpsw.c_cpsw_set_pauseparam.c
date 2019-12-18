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
struct ethtool_pauseparam {scalar_t__ tx_pause; scalar_t__ rx_pause; } ;
struct cpsw_priv {int rx_pause; int tx_pause; } ;

/* Variables and functions */
 int /*<<< orphan*/  _cpsw_adjust_link ; 
 int /*<<< orphan*/  for_each_slave (struct cpsw_priv*,int /*<<< orphan*/ ,struct cpsw_priv*,int*) ; 
 struct cpsw_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int cpsw_set_pauseparam(struct net_device *ndev,
			       struct ethtool_pauseparam *pause)
{
	struct cpsw_priv *priv = netdev_priv(ndev);
	bool link;

	priv->rx_pause = pause->rx_pause ? true : false;
	priv->tx_pause = pause->tx_pause ? true : false;

	for_each_slave(priv, _cpsw_adjust_link, priv, &link);
	return 0;
}