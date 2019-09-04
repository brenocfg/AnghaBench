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
typedef  int /*<<< orphan*/  u_short ;
struct sk_buff {int len; scalar_t__ data; } ;
struct TYPE_3__ {int tx_bytes; } ;
struct net_device {TYPE_1__ stats; scalar_t__ base_addr; } ;
struct ariadne_private {int cur_tx; int dirty_tx; int tx_full; TYPE_2__** tx_ring; int /*<<< orphan*/ * tx_buff; } ;
struct Am79C960 {int RDP; int /*<<< orphan*/  RAP; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_4__ {int TMD3; int TMD1; int /*<<< orphan*/  TMD2; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR0 ; 
 int ETH_ZLEN ; 
 int INEA ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int TDMD ; 
 int TF_ENP ; 
 int TF_OWN ; 
 int TF_STP ; 
 int TX_RING_SIZE ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 scalar_t__ lowb (int) ; 
 int /*<<< orphan*/  memcpyw (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int,int,...) ; 
 struct ariadne_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 scalar_t__ skb_padto (struct sk_buff*,int) ; 
 int /*<<< orphan*/  swapw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static netdev_tx_t ariadne_start_xmit(struct sk_buff *skb,
				      struct net_device *dev)
{
	struct ariadne_private *priv = netdev_priv(dev);
	volatile struct Am79C960 *lance = (struct Am79C960 *)dev->base_addr;
	int entry;
	unsigned long flags;
	int len = skb->len;

#if 0
	if (ariadne_debug > 3) {
		lance->RAP = CSR0;	/* PCnet-ISA Controller Status */
		netdev_dbg(dev, "%s: csr0 %04x\n", __func__, lance->RDP);
		lance->RDP = 0x0000;
	}
#endif

	/* FIXME: is the 79C960 new enough to do its own padding right ? */
	if (skb->len < ETH_ZLEN) {
		if (skb_padto(skb, ETH_ZLEN))
			return NETDEV_TX_OK;
		len = ETH_ZLEN;
	}

	/* Fill in a Tx ring entry */

	netdev_dbg(dev, "TX pkt type 0x%04x from %pM to %pM data %p len %u\n",
		   ((u_short *)skb->data)[6],
		   skb->data + 6, skb->data,
		   skb->data, skb->len);

	local_irq_save(flags);

	entry = priv->cur_tx % TX_RING_SIZE;

	/* Caution: the write order is important here, set the base address with
	   the "ownership" bits last */

	priv->tx_ring[entry]->TMD2 = swapw((u_short)-skb->len);
	priv->tx_ring[entry]->TMD3 = 0x0000;
	memcpyw(priv->tx_buff[entry], (u_short *)skb->data, len);

#ifdef DEBUG
	print_hex_dump(KERN_DEBUG, "tx_buff: ", DUMP_PREFIX_OFFSET, 16, 1,
		       (void *)priv->tx_buff[entry],
		       skb->len > 64 ? 64 : skb->len, true);
#endif

	priv->tx_ring[entry]->TMD1 = (priv->tx_ring[entry]->TMD1 & 0xff00)
		| TF_OWN | TF_STP | TF_ENP;

	dev_kfree_skb(skb);

	priv->cur_tx++;
	if ((priv->cur_tx >= TX_RING_SIZE) &&
	    (priv->dirty_tx >= TX_RING_SIZE)) {

		netdev_dbg(dev, "*** Subtracting TX_RING_SIZE from cur_tx (%d) and dirty_tx (%d)\n",
			   priv->cur_tx, priv->dirty_tx);

		priv->cur_tx -= TX_RING_SIZE;
		priv->dirty_tx -= TX_RING_SIZE;
	}
	dev->stats.tx_bytes += len;

	/* Trigger an immediate send poll */
	lance->RAP = CSR0;		/* PCnet-ISA Controller Status */
	lance->RDP = INEA | TDMD;

	if (lowb(priv->tx_ring[(entry + 1) % TX_RING_SIZE]->TMD1) != 0) {
		netif_stop_queue(dev);
		priv->tx_full = 1;
	}
	local_irq_restore(flags);

	return NETDEV_TX_OK;
}