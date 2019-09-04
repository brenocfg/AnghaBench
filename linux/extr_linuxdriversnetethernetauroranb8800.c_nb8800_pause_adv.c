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
typedef  int u32 ;
struct phy_device {int supported; int advertising; } ;
struct net_device {struct phy_device* phydev; } ;
struct nb8800_priv {scalar_t__ pause_tx; scalar_t__ pause_rx; } ;

/* Variables and functions */
 int ADVERTISED_Asym_Pause ; 
 int ADVERTISED_Pause ; 
 struct nb8800_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void nb8800_pause_adv(struct net_device *dev)
{
	struct nb8800_priv *priv = netdev_priv(dev);
	struct phy_device *phydev = dev->phydev;
	u32 adv = 0;

	if (!phydev)
		return;

	if (priv->pause_rx)
		adv |= ADVERTISED_Pause | ADVERTISED_Asym_Pause;
	if (priv->pause_tx)
		adv ^= ADVERTISED_Asym_Pause;

	phydev->supported |= adv;
	phydev->advertising |= adv;
}