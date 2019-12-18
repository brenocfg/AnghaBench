#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u64 ;
struct tx_ring_info {int prod; scalar_t__ mark_counter; scalar_t__ mark_freq; int wrap_bit; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_channel; TYPE_2__* tx_buffs; int /*<<< orphan*/  mark_pending; } ;
struct tx_pkt_hdr {scalar_t__ resv; int /*<<< orphan*/  flags; } ;
struct sk_buff {int len; scalar_t__ data; } ;
struct niu {int /*<<< orphan*/  device; TYPE_1__* ops; struct tx_ring_info* tx_rings; } ;
struct netdev_queue {int dummy; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct ethhdr {int dummy; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_6__ {int nr_frags; int /*<<< orphan*/ * frags; } ;
struct TYPE_5__ {unsigned int mapping; struct sk_buff* skb; } ;
struct TYPE_4__ {unsigned int (* map_single ) (int /*<<< orphan*/ ,scalar_t__,unsigned int,int /*<<< orphan*/ ) ;unsigned int (* map_page ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ MAX_SKB_FRAGS ; 
 int MAX_TX_DESC_LEN ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int NEXT_TX (struct tx_ring_info*,int) ; 
 scalar_t__ NIU_TX_WAKEUP_THRESH (struct tx_ring_info*) ; 
 unsigned int TX_DESC_MARK ; 
 unsigned int TX_DESC_SOP ; 
 int /*<<< orphan*/  TX_RING_KICK (int /*<<< orphan*/ ) ; 
 int TX_RING_KICK_WRAP ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ eth_skb_pad (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,int) ; 
 struct niu* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_queue (struct netdev_queue*) ; 
 int /*<<< orphan*/  netif_tx_wake_queue (struct netdev_queue*) ; 
 int /*<<< orphan*/  niu_compute_tx_flags (struct sk_buff*,struct ethhdr*,unsigned long,unsigned int) ; 
 int /*<<< orphan*/  niu_set_txd (struct tx_ring_info*,int,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 scalar_t__ niu_tx_avail (struct tx_ring_info*) ; 
 int /*<<< orphan*/  nw64 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_frag_off (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  skb_frag_page (int /*<<< orphan*/  const*) ; 
 unsigned int skb_frag_size (int /*<<< orphan*/  const*) ; 
 int skb_get_queue_mapping (struct sk_buff*) ; 
 unsigned int skb_headlen (struct sk_buff*) ; 
 unsigned int skb_headroom (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 
 struct tx_pkt_hdr* skb_push (struct sk_buff*,unsigned long) ; 
 struct sk_buff* skb_realloc_headroom (struct sk_buff*,unsigned int) ; 
 TYPE_3__* skb_shinfo (struct sk_buff*) ; 
 unsigned int stub1 (int /*<<< orphan*/ ,scalar_t__,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static netdev_tx_t niu_start_xmit(struct sk_buff *skb,
				  struct net_device *dev)
{
	struct niu *np = netdev_priv(dev);
	unsigned long align, headroom;
	struct netdev_queue *txq;
	struct tx_ring_info *rp;
	struct tx_pkt_hdr *tp;
	unsigned int len, nfg;
	struct ethhdr *ehdr;
	int prod, i, tlen;
	u64 mapping, mrk;

	i = skb_get_queue_mapping(skb);
	rp = &np->tx_rings[i];
	txq = netdev_get_tx_queue(dev, i);

	if (niu_tx_avail(rp) <= (skb_shinfo(skb)->nr_frags + 1)) {
		netif_tx_stop_queue(txq);
		dev_err(np->device, "%s: BUG! Tx ring full when queue awake!\n", dev->name);
		rp->tx_errors++;
		return NETDEV_TX_BUSY;
	}

	if (eth_skb_pad(skb))
		goto out;

	len = sizeof(struct tx_pkt_hdr) + 15;
	if (skb_headroom(skb) < len) {
		struct sk_buff *skb_new;

		skb_new = skb_realloc_headroom(skb, len);
		if (!skb_new)
			goto out_drop;
		kfree_skb(skb);
		skb = skb_new;
	} else
		skb_orphan(skb);

	align = ((unsigned long) skb->data & (16 - 1));
	headroom = align + sizeof(struct tx_pkt_hdr);

	ehdr = (struct ethhdr *) skb->data;
	tp = skb_push(skb, headroom);

	len = skb->len - sizeof(struct tx_pkt_hdr);
	tp->flags = cpu_to_le64(niu_compute_tx_flags(skb, ehdr, align, len));
	tp->resv = 0;

	len = skb_headlen(skb);
	mapping = np->ops->map_single(np->device, skb->data,
				      len, DMA_TO_DEVICE);

	prod = rp->prod;

	rp->tx_buffs[prod].skb = skb;
	rp->tx_buffs[prod].mapping = mapping;

	mrk = TX_DESC_SOP;
	if (++rp->mark_counter == rp->mark_freq) {
		rp->mark_counter = 0;
		mrk |= TX_DESC_MARK;
		rp->mark_pending++;
	}

	tlen = len;
	nfg = skb_shinfo(skb)->nr_frags;
	while (tlen > 0) {
		tlen -= MAX_TX_DESC_LEN;
		nfg++;
	}

	while (len > 0) {
		unsigned int this_len = len;

		if (this_len > MAX_TX_DESC_LEN)
			this_len = MAX_TX_DESC_LEN;

		niu_set_txd(rp, prod, mapping, this_len, mrk, nfg);
		mrk = nfg = 0;

		prod = NEXT_TX(rp, prod);
		mapping += this_len;
		len -= this_len;
	}

	for (i = 0; i <  skb_shinfo(skb)->nr_frags; i++) {
		const skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

		len = skb_frag_size(frag);
		mapping = np->ops->map_page(np->device, skb_frag_page(frag),
					    skb_frag_off(frag), len,
					    DMA_TO_DEVICE);

		rp->tx_buffs[prod].skb = NULL;
		rp->tx_buffs[prod].mapping = mapping;

		niu_set_txd(rp, prod, mapping, len, 0, 0);

		prod = NEXT_TX(rp, prod);
	}

	if (prod < rp->prod)
		rp->wrap_bit ^= TX_RING_KICK_WRAP;
	rp->prod = prod;

	nw64(TX_RING_KICK(rp->tx_channel), rp->wrap_bit | (prod << 3));

	if (unlikely(niu_tx_avail(rp) <= (MAX_SKB_FRAGS + 1))) {
		netif_tx_stop_queue(txq);
		if (niu_tx_avail(rp) > NIU_TX_WAKEUP_THRESH(rp))
			netif_tx_wake_queue(txq);
	}

out:
	return NETDEV_TX_OK;

out_drop:
	rp->tx_errors++;
	kfree_skb(skb);
	goto out;
}