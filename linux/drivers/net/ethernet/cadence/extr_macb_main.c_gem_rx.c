#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sk_buff {unsigned int len; unsigned int csum; int /*<<< orphan*/  data; int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  protocol; } ;
struct napi_struct {int dummy; } ;
struct TYPE_9__ {unsigned int rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; } ;
struct macb_queue {TYPE_3__ stats; struct sk_buff** rx_skbuff; int /*<<< orphan*/  rx_tail; struct macb* bp; } ;
struct macb_dma_desc {int addr; int ctrl; } ;
struct macb {int rx_frm_len_mask; TYPE_4__* dev; int /*<<< orphan*/  rx_buffer_size; TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_8__ {unsigned int rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; } ;
struct TYPE_10__ {int features; int flags; TYPE_2__ stats; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DUMP_PREFIX_ADDRESS ; 
 int GEM_BFEXT (int /*<<< orphan*/ ,int) ; 
 int GEM_RX_CSUM_CHECKED_MASK ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int MACB_BIT (int /*<<< orphan*/ ) ; 
 int NETIF_F_RXCSUM ; 
 int /*<<< orphan*/  RX_CSUM ; 
 int /*<<< orphan*/  RX_EOF ; 
 int /*<<< orphan*/  RX_SOF ; 
 int /*<<< orphan*/  RX_USED ; 
 int /*<<< orphan*/  dma_rmb () ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,TYPE_4__*) ; 
 int /*<<< orphan*/  gem_ptp_do_rxstamp (struct macb*,struct sk_buff*,struct macb_dma_desc*) ; 
 int /*<<< orphan*/  gem_rx_refill (struct macb_queue*) ; 
 int /*<<< orphan*/  macb_get_addr (struct macb*,struct macb_dma_desc*) ; 
 struct macb_dma_desc* macb_rx_desc (struct macb_queue*,unsigned int) ; 
 unsigned int macb_rx_ring_wrap (struct macb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_gro_receive (struct napi_struct*,struct sk_buff*) ; 
 int /*<<< orphan*/  netdev_err (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  netdev_vdbg (TYPE_4__*,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int gem_rx(struct macb_queue *queue, struct napi_struct *napi,
		  int budget)
{
	struct macb *bp = queue->bp;
	unsigned int		len;
	unsigned int		entry;
	struct sk_buff		*skb;
	struct macb_dma_desc	*desc;
	int			count = 0;

	while (count < budget) {
		u32 ctrl;
		dma_addr_t addr;
		bool rxused;

		entry = macb_rx_ring_wrap(bp, queue->rx_tail);
		desc = macb_rx_desc(queue, entry);

		/* Make hw descriptor updates visible to CPU */
		rmb();

		rxused = (desc->addr & MACB_BIT(RX_USED)) ? true : false;
		addr = macb_get_addr(bp, desc);

		if (!rxused)
			break;

		/* Ensure ctrl is at least as up-to-date as rxused */
		dma_rmb();

		ctrl = desc->ctrl;

		queue->rx_tail++;
		count++;

		if (!(ctrl & MACB_BIT(RX_SOF) && ctrl & MACB_BIT(RX_EOF))) {
			netdev_err(bp->dev,
				   "not whole frame pointed by descriptor\n");
			bp->dev->stats.rx_dropped++;
			queue->stats.rx_dropped++;
			break;
		}
		skb = queue->rx_skbuff[entry];
		if (unlikely(!skb)) {
			netdev_err(bp->dev,
				   "inconsistent Rx descriptor chain\n");
			bp->dev->stats.rx_dropped++;
			queue->stats.rx_dropped++;
			break;
		}
		/* now everything is ready for receiving packet */
		queue->rx_skbuff[entry] = NULL;
		len = ctrl & bp->rx_frm_len_mask;

		netdev_vdbg(bp->dev, "gem_rx %u (len %u)\n", entry, len);

		skb_put(skb, len);
		dma_unmap_single(&bp->pdev->dev, addr,
				 bp->rx_buffer_size, DMA_FROM_DEVICE);

		skb->protocol = eth_type_trans(skb, bp->dev);
		skb_checksum_none_assert(skb);
		if (bp->dev->features & NETIF_F_RXCSUM &&
		    !(bp->dev->flags & IFF_PROMISC) &&
		    GEM_BFEXT(RX_CSUM, ctrl) & GEM_RX_CSUM_CHECKED_MASK)
			skb->ip_summed = CHECKSUM_UNNECESSARY;

		bp->dev->stats.rx_packets++;
		queue->stats.rx_packets++;
		bp->dev->stats.rx_bytes += skb->len;
		queue->stats.rx_bytes += skb->len;

		gem_ptp_do_rxstamp(bp, skb, desc);

#if defined(DEBUG) && defined(VERBOSE_DEBUG)
		netdev_vdbg(bp->dev, "received skb of length %u, csum: %08x\n",
			    skb->len, skb->csum);
		print_hex_dump(KERN_DEBUG, " mac: ", DUMP_PREFIX_ADDRESS, 16, 1,
			       skb_mac_header(skb), 16, true);
		print_hex_dump(KERN_DEBUG, "data: ", DUMP_PREFIX_ADDRESS, 16, 1,
			       skb->data, 32, true);
#endif

		napi_gro_receive(napi, skb);
	}

	gem_rx_refill(queue);

	return count;
}