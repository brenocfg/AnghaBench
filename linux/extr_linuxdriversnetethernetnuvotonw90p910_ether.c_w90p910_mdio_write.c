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
struct w90p910_ether {scalar_t__ reg; struct platform_device* pdev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 unsigned int DELAY ; 
 unsigned int MDCCR_VAL ; 
 unsigned int PHYBUSY ; 
 unsigned int PHYWR ; 
 scalar_t__ REG_MIID ; 
 scalar_t__ REG_MIIDA ; 
 unsigned int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct w90p910_ether* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void w90p910_mdio_write(struct net_device *dev,
					int phy_id, int reg, int data)
{
	struct w90p910_ether *ether = netdev_priv(dev);
	struct platform_device *pdev;
	unsigned int val, i;

	pdev = ether->pdev;

	__raw_writel(data, ether->reg + REG_MIID);

	val = (phy_id << 0x08) | reg;
	val |= PHYBUSY | PHYWR | MDCCR_VAL;
	__raw_writel(val, ether->reg + REG_MIIDA);

	for (i = 0; i < DELAY; i++) {
		if ((__raw_readl(ether->reg + REG_MIIDA) & PHYBUSY) == 0)
			break;
	}

	if (i == DELAY)
		dev_warn(&pdev->dev, "mdio write timed out\n");
}