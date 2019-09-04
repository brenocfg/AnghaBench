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
struct sk_buff {int /*<<< orphan*/  protocol; struct net_device* dev; scalar_t__ data; } ;
struct net_device_stats {unsigned int rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_length_errors; } ;
struct net_device {int /*<<< orphan*/  dev; struct net_device_stats stats; } ;
struct buffer_state {struct sk_buff* skb; } ;
struct arc_emac_priv {unsigned int last_rx_bd; struct arc_emac_bd* rxbd; struct buffer_state* rx_buff; } ;
struct arc_emac_bd {void* info; void* data; } ;
typedef  unsigned int dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 unsigned int EMAC_BUFFER_SIZE ; 
 unsigned int FIRST_OR_LAST_MASK ; 
 unsigned int FOR_EMAC ; 
 unsigned int LEN_MASK ; 
 unsigned int OWN_MASK ; 
 unsigned int RX_BD_NUM ; 
 void* cpu_to_le32 (unsigned int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 unsigned int dma_map_single (int /*<<< orphan*/ *,void*,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  dma_unmap_addr (struct buffer_state*,unsigned int) ; 
 int /*<<< orphan*/  dma_unmap_addr_set (struct buffer_state*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dma_unmap_len (struct buffer_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len_set (struct buffer_state*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 unsigned int le32_to_cpu (void*) ; 
 int /*<<< orphan*/  len ; 
 scalar_t__ net_ratelimit () ; 
 struct sk_buff* netdev_alloc_skb_ip_align (struct net_device*,unsigned int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct arc_emac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int arc_emac_rx(struct net_device *ndev, int budget)
{
	struct arc_emac_priv *priv = netdev_priv(ndev);
	unsigned int work_done;

	for (work_done = 0; work_done < budget; work_done++) {
		unsigned int *last_rx_bd = &priv->last_rx_bd;
		struct net_device_stats *stats = &ndev->stats;
		struct buffer_state *rx_buff = &priv->rx_buff[*last_rx_bd];
		struct arc_emac_bd *rxbd = &priv->rxbd[*last_rx_bd];
		unsigned int pktlen, info = le32_to_cpu(rxbd->info);
		struct sk_buff *skb;
		dma_addr_t addr;

		if (unlikely((info & OWN_MASK) == FOR_EMAC))
			break;

		/* Make a note that we saw a packet at this BD.
		 * So next time, driver starts from this + 1
		 */
		*last_rx_bd = (*last_rx_bd + 1) % RX_BD_NUM;

		if (unlikely((info & FIRST_OR_LAST_MASK) !=
			     FIRST_OR_LAST_MASK)) {
			/* We pre-allocate buffers of MTU size so incoming
			 * packets won't be split/chained.
			 */
			if (net_ratelimit())
				netdev_err(ndev, "incomplete packet received\n");

			/* Return ownership to EMAC */
			rxbd->info = cpu_to_le32(FOR_EMAC | EMAC_BUFFER_SIZE);
			stats->rx_errors++;
			stats->rx_length_errors++;
			continue;
		}

		/* Prepare the BD for next cycle. netif_receive_skb()
		 * only if new skb was allocated and mapped to avoid holes
		 * in the RX fifo.
		 */
		skb = netdev_alloc_skb_ip_align(ndev, EMAC_BUFFER_SIZE);
		if (unlikely(!skb)) {
			if (net_ratelimit())
				netdev_err(ndev, "cannot allocate skb\n");
			/* Return ownership to EMAC */
			rxbd->info = cpu_to_le32(FOR_EMAC | EMAC_BUFFER_SIZE);
			stats->rx_errors++;
			stats->rx_dropped++;
			continue;
		}

		addr = dma_map_single(&ndev->dev, (void *)skb->data,
				      EMAC_BUFFER_SIZE, DMA_FROM_DEVICE);
		if (dma_mapping_error(&ndev->dev, addr)) {
			if (net_ratelimit())
				netdev_err(ndev, "cannot map dma buffer\n");
			dev_kfree_skb(skb);
			/* Return ownership to EMAC */
			rxbd->info = cpu_to_le32(FOR_EMAC | EMAC_BUFFER_SIZE);
			stats->rx_errors++;
			stats->rx_dropped++;
			continue;
		}

		/* unmap previosly mapped skb */
		dma_unmap_single(&ndev->dev, dma_unmap_addr(rx_buff, addr),
				 dma_unmap_len(rx_buff, len), DMA_FROM_DEVICE);

		pktlen = info & LEN_MASK;
		stats->rx_packets++;
		stats->rx_bytes += pktlen;
		skb_put(rx_buff->skb, pktlen);
		rx_buff->skb->dev = ndev;
		rx_buff->skb->protocol = eth_type_trans(rx_buff->skb, ndev);

		netif_receive_skb(rx_buff->skb);

		rx_buff->skb = skb;
		dma_unmap_addr_set(rx_buff, addr, addr);
		dma_unmap_len_set(rx_buff, len, EMAC_BUFFER_SIZE);

		rxbd->data = cpu_to_le32(addr);

		/* Make sure pointer to data buffer is set */
		wmb();

		/* Return ownership to EMAC */
		rxbd->info = cpu_to_le32(FOR_EMAC | EMAC_BUFFER_SIZE);
	}

	return work_done;
}