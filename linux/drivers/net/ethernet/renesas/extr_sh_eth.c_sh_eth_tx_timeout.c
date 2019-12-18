#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sh_eth_rxdesc {void* addr; void* status; } ;
struct sh_eth_private {int num_rx_ring; int num_tx_ring; int /*<<< orphan*/ ** tx_skbuff; int /*<<< orphan*/ ** rx_skbuff; struct sh_eth_rxdesc* rx_ring; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_errors; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  EESR ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 struct sh_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct sh_eth_private*,int /*<<< orphan*/ ,struct net_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  sh_eth_dev_init (struct net_device*) ; 
 int /*<<< orphan*/  sh_eth_read (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void sh_eth_tx_timeout(struct net_device *ndev)
{
	struct sh_eth_private *mdp = netdev_priv(ndev);
	struct sh_eth_rxdesc *rxdesc;
	int i;

	netif_stop_queue(ndev);

	netif_err(mdp, timer, ndev,
		  "transmit timed out, status %8.8x, resetting...\n",
		  sh_eth_read(ndev, EESR));

	/* tx_errors count up */
	ndev->stats.tx_errors++;

	/* Free all the skbuffs in the Rx queue. */
	for (i = 0; i < mdp->num_rx_ring; i++) {
		rxdesc = &mdp->rx_ring[i];
		rxdesc->status = cpu_to_le32(0);
		rxdesc->addr = cpu_to_le32(0xBADF00D0);
		dev_kfree_skb(mdp->rx_skbuff[i]);
		mdp->rx_skbuff[i] = NULL;
	}
	for (i = 0; i < mdp->num_tx_ring; i++) {
		dev_kfree_skb(mdp->tx_skbuff[i]);
		mdp->tx_skbuff[i] = NULL;
	}

	/* device init */
	sh_eth_dev_init(ndev);

	netif_start_queue(ndev);
}