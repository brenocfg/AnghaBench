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
struct phy_device {int dummy; } ;
struct net_device {struct phy_device* phydev; } ;
struct nb8800_priv {int /*<<< orphan*/  pause_tx; int /*<<< orphan*/  pause_rx; } ;

/* Variables and functions */
 struct nb8800_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_set_asym_pause (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nb8800_pause_adv(struct net_device *dev)
{
	struct nb8800_priv *priv = netdev_priv(dev);
	struct phy_device *phydev = dev->phydev;

	if (!phydev)
		return;

	phy_set_asym_pause(phydev, priv->pause_rx, priv->pause_tx);
}