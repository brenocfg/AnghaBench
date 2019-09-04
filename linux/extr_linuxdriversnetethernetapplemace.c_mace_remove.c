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
struct net_device {int /*<<< orphan*/  irq; } ;
struct macio_dev {int dummy; } ;
struct mace_data {int /*<<< orphan*/  mace; int /*<<< orphan*/  tx_dma; int /*<<< orphan*/  rx_dma; int /*<<< orphan*/  rx_dma_intr; int /*<<< orphan*/  tx_dma_intr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct net_device* macio_get_drvdata (struct macio_dev*) ; 
 int /*<<< orphan*/  macio_release_resources (struct macio_dev*) ; 
 int /*<<< orphan*/  macio_set_drvdata (struct macio_dev*,int /*<<< orphan*/ *) ; 
 struct mace_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int mace_remove(struct macio_dev *mdev)
{
	struct net_device *dev = macio_get_drvdata(mdev);
	struct mace_data *mp;

	BUG_ON(dev == NULL);

	macio_set_drvdata(mdev, NULL);

	mp = netdev_priv(dev);

	unregister_netdev(dev);

	free_irq(dev->irq, dev);
	free_irq(mp->tx_dma_intr, dev);
	free_irq(mp->rx_dma_intr, dev);

	iounmap(mp->rx_dma);
	iounmap(mp->tx_dma);
	iounmap(mp->mace);

	free_netdev(dev);

	macio_release_resources(mdev);

	return 0;
}