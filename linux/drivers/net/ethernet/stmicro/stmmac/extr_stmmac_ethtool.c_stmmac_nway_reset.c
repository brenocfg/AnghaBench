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
struct stmmac_priv {int /*<<< orphan*/  phylink; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct stmmac_priv* netdev_priv (struct net_device*) ; 
 int phylink_ethtool_nway_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stmmac_nway_reset(struct net_device *dev)
{
	struct stmmac_priv *priv = netdev_priv(dev);

	return phylink_ethtool_nway_reset(priv->phylink);
}