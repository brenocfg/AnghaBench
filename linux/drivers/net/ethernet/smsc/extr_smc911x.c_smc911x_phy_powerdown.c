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
struct smc911x_local {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 unsigned int BMCR_PDOWN ; 
 int /*<<< orphan*/  SMC_GET_PHY_BMCR (struct smc911x_local*,int,unsigned int) ; 
 int /*<<< orphan*/  SMC_SET_PHY_BMCR (struct smc911x_local*,int,unsigned int) ; 
 struct smc911x_local* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void smc911x_phy_powerdown(struct net_device *dev, int phy)
{
	struct smc911x_local *lp = netdev_priv(dev);
	unsigned int bmcr;

	/* Enter Link Disable state */
	SMC_GET_PHY_BMCR(lp, phy, bmcr);
	bmcr |= BMCR_PDOWN;
	SMC_SET_PHY_BMCR(lp, phy, bmcr);
}