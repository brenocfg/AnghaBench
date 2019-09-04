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
struct sk_buff {int dummy; } ;
struct pch_gbe_tx_ring {int /*<<< orphan*/  next_to_clean; int /*<<< orphan*/  next_to_use; } ;
struct pch_gbe_adapter {struct pch_gbe_tx_ring* tx_ring; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int NETDEV_TX_BUSY ; 
 int NETDEV_TX_OK ; 
 int /*<<< orphan*/  PCH_GBE_DESC_UNUSED (struct pch_gbe_tx_ring*) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pch_gbe_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  pch_gbe_tx_queue (struct pch_gbe_adapter*,struct pch_gbe_tx_ring*,struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int pch_gbe_xmit_frame(struct sk_buff *skb, struct net_device *netdev)
{
	struct pch_gbe_adapter *adapter = netdev_priv(netdev);
	struct pch_gbe_tx_ring *tx_ring = adapter->tx_ring;

	if (unlikely(!PCH_GBE_DESC_UNUSED(tx_ring))) {
		netif_stop_queue(netdev);
		netdev_dbg(netdev,
			   "Return : BUSY  next_to use : 0x%08x  next_to clean : 0x%08x\n",
			   tx_ring->next_to_use, tx_ring->next_to_clean);
		return NETDEV_TX_BUSY;
	}

	/* CRC,ITAG no support */
	pch_gbe_tx_queue(adapter, tx_ring, skb);
	return NETDEV_TX_OK;
}