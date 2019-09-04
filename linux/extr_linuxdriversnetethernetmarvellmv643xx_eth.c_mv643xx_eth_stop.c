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
struct net_device {int /*<<< orphan*/  irq; scalar_t__ phydev; } ;
struct mv643xx_eth_private {int rxq_count; int txq_count; scalar_t__ txq; scalar_t__ rxq; int /*<<< orphan*/  mib_counters_timer; int /*<<< orphan*/  rx_oom; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MASK ; 
 int /*<<< orphan*/  INT_MASK_EXT ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  mib_counters_update (struct mv643xx_eth_private*) ; 
 int /*<<< orphan*/  mv643xx_eth_get_stats (struct net_device*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct mv643xx_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  phy_stop (scalar_t__) ; 
 int /*<<< orphan*/  port_reset (struct mv643xx_eth_private*) ; 
 int /*<<< orphan*/  rdlp (struct mv643xx_eth_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxq_deinit (scalar_t__) ; 
 int /*<<< orphan*/  txq_deinit (scalar_t__) ; 
 int /*<<< orphan*/  wrlp (struct mv643xx_eth_private*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mv643xx_eth_stop(struct net_device *dev)
{
	struct mv643xx_eth_private *mp = netdev_priv(dev);
	int i;

	wrlp(mp, INT_MASK_EXT, 0x00000000);
	wrlp(mp, INT_MASK, 0x00000000);
	rdlp(mp, INT_MASK);

	napi_disable(&mp->napi);

	del_timer_sync(&mp->rx_oom);

	netif_carrier_off(dev);
	if (dev->phydev)
		phy_stop(dev->phydev);
	free_irq(dev->irq, dev);

	port_reset(mp);
	mv643xx_eth_get_stats(dev);
	mib_counters_update(mp);
	del_timer_sync(&mp->mib_counters_timer);

	for (i = 0; i < mp->rxq_count; i++)
		rxq_deinit(mp->rxq + i);
	for (i = 0; i < mp->txq_count; i++)
		txq_deinit(mp->txq + i);

	return 0;
}