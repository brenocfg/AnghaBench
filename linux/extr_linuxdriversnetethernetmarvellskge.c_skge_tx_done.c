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
typedef  int u32 ;
struct skge_tx_desc {int control; } ;
struct skge_ring {int start; struct skge_element* to_clean; struct skge_element* to_use; } ;
struct skge_port {size_t port; struct skge_ring tx_ring; int /*<<< orphan*/  netdev; TYPE_1__* hw; } ;
struct skge_element {TYPE_2__* skb; scalar_t__ desc; struct skge_element* next; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ len; } ;
struct TYPE_3__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int BMU_EOF ; 
 int BMU_OWN ; 
 int /*<<< orphan*/  CSR_IRQ_CL_F ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  Q_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q_CSR ; 
 scalar_t__ TX_LOW_WATER ; 
 int /*<<< orphan*/  dev_consume_skb_any (TYPE_2__*) ; 
 int /*<<< orphan*/  netdev_completed_queue (struct net_device*,unsigned int,unsigned int) ; 
 struct skge_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_printk (struct skge_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct skge_element*) ; 
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_lock (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_unlock (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 scalar_t__ skge_avail (struct skge_ring*) ; 
 int /*<<< orphan*/  skge_tx_unmap (int /*<<< orphan*/ ,struct skge_element*,int) ; 
 int /*<<< orphan*/  skge_write8 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  tx_done ; 
 int /*<<< orphan*/ * txqaddr ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void skge_tx_done(struct net_device *dev)
{
	struct skge_port *skge = netdev_priv(dev);
	struct skge_ring *ring = &skge->tx_ring;
	struct skge_element *e;
	unsigned int bytes_compl = 0, pkts_compl = 0;

	skge_write8(skge->hw, Q_ADDR(txqaddr[skge->port], Q_CSR), CSR_IRQ_CL_F);

	for (e = ring->to_clean; e != ring->to_use; e = e->next) {
		u32 control = ((const struct skge_tx_desc *) e->desc)->control;

		if (control & BMU_OWN)
			break;

		skge_tx_unmap(skge->hw->pdev, e, control);

		if (control & BMU_EOF) {
			netif_printk(skge, tx_done, KERN_DEBUG, skge->netdev,
				     "tx done slot %td\n",
				     e - skge->tx_ring.start);

			pkts_compl++;
			bytes_compl += e->skb->len;

			dev_consume_skb_any(e->skb);
		}
	}
	netdev_completed_queue(dev, pkts_compl, bytes_compl);
	skge->tx_ring.to_clean = e;

	/* Can run lockless until we need to synchronize to restart queue. */
	smp_mb();

	if (unlikely(netif_queue_stopped(dev) &&
		     skge_avail(&skge->tx_ring) > TX_LOW_WATER)) {
		netif_tx_lock(dev);
		if (unlikely(netif_queue_stopped(dev) &&
			     skge_avail(&skge->tx_ring) > TX_LOW_WATER)) {
			netif_wake_queue(dev);

		}
		netif_tx_unlock(dev);
	}
}