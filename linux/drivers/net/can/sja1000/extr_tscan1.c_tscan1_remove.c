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
struct sja1000_priv {scalar_t__ reg_base; } ;
struct net_device {unsigned long base_addr; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ TSCAN1_MODE ; 
 int /*<<< orphan*/  TSCAN1_PLD_SIZE ; 
 int /*<<< orphan*/  TSCAN1_SJA1000_SIZE ; 
 struct net_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_sja1000dev (struct net_device*) ; 
 struct sja1000_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  release_region (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_sja1000dev (struct net_device*) ; 

__attribute__((used)) static int tscan1_remove(struct device *dev, unsigned id /*unused*/)
{
	struct net_device *netdev;
	struct sja1000_priv *priv;
	unsigned long pld_base, sja1000_base;

	netdev = dev_get_drvdata(dev);
	unregister_sja1000dev(netdev);
	dev_set_drvdata(dev, NULL);

	priv = netdev_priv(netdev);
	pld_base = netdev->base_addr;
	sja1000_base = (unsigned long)priv->reg_base;

	outb(0, pld_base + TSCAN1_MODE);	/* disable SJA1000 IO space */

	release_region(sja1000_base, TSCAN1_SJA1000_SIZE);
	release_region(pld_base, TSCAN1_PLD_SIZE);

	free_sja1000dev(netdev);

	return 0;
}