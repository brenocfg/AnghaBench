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
struct sk_buff {scalar_t__ len; scalar_t__ ip_summed; int /*<<< orphan*/  data; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_dropped; } ;
struct net_device {TYPE_1__ stats; } ;
struct ftgmac100_txdes {void* txdes0; void* txdes3; void* txdes1; } ;
struct ftgmac100 {unsigned int tx_pointer; int txdes0_edotr_mask; struct ftgmac100_txdes* txdes; scalar_t__ base; struct sk_buff** tx_skbs; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
typedef  int dma_addr_t ;
struct TYPE_4__ {unsigned int nr_frags; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ FTGMAC100_OFFSET_NPTXPD ; 
 int FTGMAC100_TXDES0_FTS ; 
 int FTGMAC100_TXDES0_LTS ; 
 int FTGMAC100_TXDES0_TXBUF_SIZE (unsigned int) ; 
 int FTGMAC100_TXDES0_TXDMA_OWN ; 
 int FTGMAC100_TXDES1_INS_VLANTAG ; 
 scalar_t__ MAX_PKT_SIZE ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 scalar_t__ TX_THRESHOLD ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dma_wmb () ; 
 scalar_t__ eth_skb_pad (struct sk_buff*) ; 
 int ftgmac100_base_tx_ctlstat (struct ftgmac100*,unsigned int) ; 
 int /*<<< orphan*/  ftgmac100_free_tx_packet (struct ftgmac100*,unsigned int,struct sk_buff*,struct ftgmac100_txdes*,int) ; 
 unsigned int ftgmac100_next_tx_pointer (struct ftgmac100*,unsigned int) ; 
 int /*<<< orphan*/  ftgmac100_prep_tx_csum (struct sk_buff*,int*) ; 
 scalar_t__ ftgmac100_tx_buf_avail (struct ftgmac100*) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int le32_to_cpu (void*) ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct ftgmac100* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int skb_frag_dma_map (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int skb_frag_size (int /*<<< orphan*/ *) ; 
 unsigned int skb_headlen (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int skb_vlan_tag_get (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static netdev_tx_t ftgmac100_hard_start_xmit(struct sk_buff *skb,
					     struct net_device *netdev)
{
	struct ftgmac100 *priv = netdev_priv(netdev);
	struct ftgmac100_txdes *txdes, *first;
	unsigned int pointer, nfrags, len, i, j;
	u32 f_ctl_stat, ctl_stat, csum_vlan;
	dma_addr_t map;

	/* The HW doesn't pad small frames */
	if (eth_skb_pad(skb)) {
		netdev->stats.tx_dropped++;
		return NETDEV_TX_OK;
	}

	/* Reject oversize packets */
	if (unlikely(skb->len > MAX_PKT_SIZE)) {
		if (net_ratelimit())
			netdev_dbg(netdev, "tx packet too big\n");
		goto drop;
	}

	/* Do we have a limit on #fragments ? I yet have to get a reply
	 * from Aspeed. If there's one I haven't hit it.
	 */
	nfrags = skb_shinfo(skb)->nr_frags;

	/* Setup HW checksumming */
	csum_vlan = 0;
	if (skb->ip_summed == CHECKSUM_PARTIAL &&
	    !ftgmac100_prep_tx_csum(skb, &csum_vlan))
		goto drop;

	/* Add VLAN tag */
	if (skb_vlan_tag_present(skb)) {
		csum_vlan |= FTGMAC100_TXDES1_INS_VLANTAG;
		csum_vlan |= skb_vlan_tag_get(skb) & 0xffff;
	}

	/* Get header len */
	len = skb_headlen(skb);

	/* Map the packet head */
	map = dma_map_single(priv->dev, skb->data, len, DMA_TO_DEVICE);
	if (dma_mapping_error(priv->dev, map)) {
		if (net_ratelimit())
			netdev_err(netdev, "map tx packet head failed\n");
		goto drop;
	}

	/* Grab the next free tx descriptor */
	pointer = priv->tx_pointer;
	txdes = first = &priv->txdes[pointer];

	/* Setup it up with the packet head. Don't write the head to the
	 * ring just yet
	 */
	priv->tx_skbs[pointer] = skb;
	f_ctl_stat = ftgmac100_base_tx_ctlstat(priv, pointer);
	f_ctl_stat |= FTGMAC100_TXDES0_TXDMA_OWN;
	f_ctl_stat |= FTGMAC100_TXDES0_TXBUF_SIZE(len);
	f_ctl_stat |= FTGMAC100_TXDES0_FTS;
	if (nfrags == 0)
		f_ctl_stat |= FTGMAC100_TXDES0_LTS;
	txdes->txdes3 = cpu_to_le32(map);
	txdes->txdes1 = cpu_to_le32(csum_vlan);

	/* Next descriptor */
	pointer = ftgmac100_next_tx_pointer(priv, pointer);

	/* Add the fragments */
	for (i = 0; i < nfrags; i++) {
		skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

		len = skb_frag_size(frag);

		/* Map it */
		map = skb_frag_dma_map(priv->dev, frag, 0, len,
				       DMA_TO_DEVICE);
		if (dma_mapping_error(priv->dev, map))
			goto dma_err;

		/* Setup descriptor */
		priv->tx_skbs[pointer] = skb;
		txdes = &priv->txdes[pointer];
		ctl_stat = ftgmac100_base_tx_ctlstat(priv, pointer);
		ctl_stat |= FTGMAC100_TXDES0_TXDMA_OWN;
		ctl_stat |= FTGMAC100_TXDES0_TXBUF_SIZE(len);
		if (i == (nfrags - 1))
			ctl_stat |= FTGMAC100_TXDES0_LTS;
		txdes->txdes0 = cpu_to_le32(ctl_stat);
		txdes->txdes1 = 0;
		txdes->txdes3 = cpu_to_le32(map);

		/* Next one */
		pointer = ftgmac100_next_tx_pointer(priv, pointer);
	}

	/* Order the previous packet and descriptor udpates
	 * before setting the OWN bit on the first descriptor.
	 */
	dma_wmb();
	first->txdes0 = cpu_to_le32(f_ctl_stat);

	/* Update next TX pointer */
	priv->tx_pointer = pointer;

	/* If there isn't enough room for all the fragments of a new packet
	 * in the TX ring, stop the queue. The sequence below is race free
	 * vs. a concurrent restart in ftgmac100_poll()
	 */
	if (unlikely(ftgmac100_tx_buf_avail(priv) < TX_THRESHOLD)) {
		netif_stop_queue(netdev);
		/* Order the queue stop with the test below */
		smp_mb();
		if (ftgmac100_tx_buf_avail(priv) >= TX_THRESHOLD)
			netif_wake_queue(netdev);
	}

	/* Poke transmitter to read the updated TX descriptors */
	iowrite32(1, priv->base + FTGMAC100_OFFSET_NPTXPD);

	return NETDEV_TX_OK;

 dma_err:
	if (net_ratelimit())
		netdev_err(netdev, "map tx fragment failed\n");

	/* Free head */
	pointer = priv->tx_pointer;
	ftgmac100_free_tx_packet(priv, pointer, skb, first, f_ctl_stat);
	first->txdes0 = cpu_to_le32(f_ctl_stat & priv->txdes0_edotr_mask);

	/* Then all fragments */
	for (j = 0; j < i; j++) {
		pointer = ftgmac100_next_tx_pointer(priv, pointer);
		txdes = &priv->txdes[pointer];
		ctl_stat = le32_to_cpu(txdes->txdes0);
		ftgmac100_free_tx_packet(priv, pointer, skb, txdes, ctl_stat);
		txdes->txdes0 = cpu_to_le32(ctl_stat & priv->txdes0_edotr_mask);
	}

	/* This cannot be reached if we successfully mapped the
	 * last fragment, so we know ftgmac100_free_tx_packet()
	 * hasn't freed the skb yet.
	 */
 drop:
	/* Drop the packet */
	dev_kfree_skb_any(skb);
	netdev->stats.tx_dropped++;

	return NETDEV_TX_OK;
}