#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct mtk_mac {size_t id; struct mtk_eth* hw; } ;
struct mtk_eth {int /*<<< orphan*/  pending_work; TYPE_2__** netdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_errors; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 struct mtk_mac* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct mtk_eth*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tx_err ; 

__attribute__((used)) static void mtk_tx_timeout(struct net_device *dev)
{
	struct mtk_mac *mac = netdev_priv(dev);
	struct mtk_eth *eth = mac->hw;

	eth->netdev[mac->id]->stats.tx_errors++;
	netif_err(eth, tx_err, dev,
		  "transmit timed out\n");
	schedule_work(&eth->pending_work);
}