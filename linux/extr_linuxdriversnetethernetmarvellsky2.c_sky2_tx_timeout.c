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
struct sky2_port {size_t port; int /*<<< orphan*/  tx_prod; int /*<<< orphan*/  tx_cons; struct sky2_hw* hw; } ;
struct sky2_hw {int /*<<< orphan*/  restart_work; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  Q_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q_DONE ; 
 int /*<<< orphan*/  STAT_TXA1_RIDX ; 
 int /*<<< orphan*/  STAT_TXA2_RIDX ; 
 int /*<<< orphan*/  netdev_printk (int /*<<< orphan*/ ,struct net_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sky2_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct sky2_port*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sky2_read16 (struct sky2_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer ; 
 int /*<<< orphan*/ * txqaddr ; 

__attribute__((used)) static void sky2_tx_timeout(struct net_device *dev)
{
	struct sky2_port *sky2 = netdev_priv(dev);
	struct sky2_hw *hw = sky2->hw;

	netif_err(sky2, timer, dev, "tx timeout\n");

	netdev_printk(KERN_DEBUG, dev, "transmit ring %u .. %u report=%u done=%u\n",
		      sky2->tx_cons, sky2->tx_prod,
		      sky2_read16(hw, sky2->port == 0 ? STAT_TXA1_RIDX : STAT_TXA2_RIDX),
		      sky2_read16(hw, Q_ADDR(txqaddr[sky2->port], Q_DONE)));

	/* can't restart safely under softirq */
	schedule_work(&hw->restart_work);
}