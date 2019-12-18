#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct xlgmac_pkt_info {int /*<<< orphan*/  rss_hash_type; int /*<<< orphan*/  rss_hash; int /*<<< orphan*/  attributes; int /*<<< orphan*/  vlan_ctag; scalar_t__ errors; } ;
struct xlgmac_ring {int /*<<< orphan*/  cur; struct xlgmac_pkt_info pkt_info; } ;
struct TYPE_10__ {int /*<<< orphan*/  rx_vlan_packets; } ;
struct napi_struct {int dummy; } ;
struct xlgmac_hw_ops {scalar_t__ (* dev_read ) (struct xlgmac_channel*) ;} ;
struct xlgmac_pdata {TYPE_4__ stats; int /*<<< orphan*/  dev; struct napi_struct napi; scalar_t__ per_channel_irq; struct xlgmac_hw_ops hw_ops; struct net_device* netdev; } ;
struct TYPE_11__ {unsigned int error; unsigned int len; struct sk_buff* skb; } ;
struct TYPE_7__ {int /*<<< orphan*/ * pages; int /*<<< orphan*/  pages_offset; } ;
struct TYPE_8__ {TYPE_1__ pa; int /*<<< orphan*/  dma_len; int /*<<< orphan*/  dma_off; int /*<<< orphan*/  dma_base; } ;
struct TYPE_9__ {unsigned int len; TYPE_2__ buf; } ;
struct xlgmac_desc_data {int state_saved; TYPE_5__ state; TYPE_3__ rx; } ;
struct xlgmac_channel {int /*<<< orphan*/  queue_index; struct napi_struct napi; struct xlgmac_ring* rx_ring; struct xlgmac_pdata* pdata; } ;
struct sk_buff {scalar_t__ protocol; unsigned int len; struct net_device* dev; int /*<<< orphan*/  ip_summed; } ;
struct net_device {unsigned int mtu; int features; } ;
struct TYPE_12__ {int /*<<< orphan*/  nr_frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 unsigned int ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int /*<<< orphan*/  RX_PACKET_ATTRIBUTES_CONTEXT_LEN ; 
 int /*<<< orphan*/  RX_PACKET_ATTRIBUTES_CONTEXT_NEXT_LEN ; 
 int /*<<< orphan*/  RX_PACKET_ATTRIBUTES_CONTEXT_NEXT_POS ; 
 int /*<<< orphan*/  RX_PACKET_ATTRIBUTES_CONTEXT_POS ; 
 int /*<<< orphan*/  RX_PACKET_ATTRIBUTES_CSUM_DONE_LEN ; 
 int /*<<< orphan*/  RX_PACKET_ATTRIBUTES_CSUM_DONE_POS ; 
 int /*<<< orphan*/  RX_PACKET_ATTRIBUTES_INCOMPLETE_LEN ; 
 int /*<<< orphan*/  RX_PACKET_ATTRIBUTES_INCOMPLETE_POS ; 
 int /*<<< orphan*/  RX_PACKET_ATTRIBUTES_RSS_HASH_LEN ; 
 int /*<<< orphan*/  RX_PACKET_ATTRIBUTES_RSS_HASH_POS ; 
 int /*<<< orphan*/  RX_PACKET_ATTRIBUTES_VLAN_CTAG_LEN ; 
 int /*<<< orphan*/  RX_PACKET_ATTRIBUTES_VLAN_CTAG_POS ; 
 scalar_t__ VLAN_HLEN ; 
 struct xlgmac_desc_data* XLGMAC_GET_DESC_DATA (struct xlgmac_ring*,int /*<<< orphan*/ ) ; 
 int XLGMAC_GET_REG_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLGMAC_PR (char*,int) ; 
 scalar_t__ XLGMAC_RX_DESC_MAX_DIRTY ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_sync_single_range_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ eth_type_trans (struct sk_buff*,struct net_device*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct xlgmac_pkt_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  napi_gro_receive (struct napi_struct*,struct sk_buff*) ; 
 int /*<<< orphan*/  netif_err (struct xlgmac_pdata*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 scalar_t__ netif_msg_pktdata (struct xlgmac_pdata*) ; 
 int /*<<< orphan*/  rx_err ; 
 int /*<<< orphan*/  skb_add_rx_frag (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_record_rx_queue (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_hash (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ stub1 (struct xlgmac_channel*) ; 
 struct sk_buff* xlgmac_create_skb (struct xlgmac_pdata*,struct napi_struct*,struct xlgmac_desc_data*,unsigned int) ; 
 int /*<<< orphan*/  xlgmac_print_pkt (struct net_device*,struct sk_buff*,int) ; 
 scalar_t__ xlgmac_rx_dirty_desc (struct xlgmac_ring*) ; 
 int /*<<< orphan*/  xlgmac_rx_refresh (struct xlgmac_channel*) ; 

__attribute__((used)) static int xlgmac_rx_poll(struct xlgmac_channel *channel, int budget)
{
	struct xlgmac_pdata *pdata = channel->pdata;
	struct xlgmac_ring *ring = channel->rx_ring;
	struct net_device *netdev = pdata->netdev;
	unsigned int len, dma_desc_len, max_len;
	unsigned int context_next, context;
	struct xlgmac_desc_data *desc_data;
	struct xlgmac_pkt_info *pkt_info;
	unsigned int incomplete, error;
	struct xlgmac_hw_ops *hw_ops;
	unsigned int received = 0;
	struct napi_struct *napi;
	struct sk_buff *skb;
	int packet_count = 0;

	hw_ops = &pdata->hw_ops;

	/* Nothing to do if there isn't a Rx ring for this channel */
	if (!ring)
		return 0;

	incomplete = 0;
	context_next = 0;

	napi = (pdata->per_channel_irq) ? &channel->napi : &pdata->napi;

	desc_data = XLGMAC_GET_DESC_DATA(ring, ring->cur);
	pkt_info = &ring->pkt_info;
	while (packet_count < budget) {
		/* First time in loop see if we need to restore state */
		if (!received && desc_data->state_saved) {
			skb = desc_data->state.skb;
			error = desc_data->state.error;
			len = desc_data->state.len;
		} else {
			memset(pkt_info, 0, sizeof(*pkt_info));
			skb = NULL;
			error = 0;
			len = 0;
		}

read_again:
		desc_data = XLGMAC_GET_DESC_DATA(ring, ring->cur);

		if (xlgmac_rx_dirty_desc(ring) > XLGMAC_RX_DESC_MAX_DIRTY)
			xlgmac_rx_refresh(channel);

		if (hw_ops->dev_read(channel))
			break;

		received++;
		ring->cur++;

		incomplete = XLGMAC_GET_REG_BITS(
					pkt_info->attributes,
					RX_PACKET_ATTRIBUTES_INCOMPLETE_POS,
					RX_PACKET_ATTRIBUTES_INCOMPLETE_LEN);
		context_next = XLGMAC_GET_REG_BITS(
					pkt_info->attributes,
					RX_PACKET_ATTRIBUTES_CONTEXT_NEXT_POS,
					RX_PACKET_ATTRIBUTES_CONTEXT_NEXT_LEN);
		context = XLGMAC_GET_REG_BITS(
					pkt_info->attributes,
					RX_PACKET_ATTRIBUTES_CONTEXT_POS,
					RX_PACKET_ATTRIBUTES_CONTEXT_LEN);

		/* Earlier error, just drain the remaining data */
		if ((incomplete || context_next) && error)
			goto read_again;

		if (error || pkt_info->errors) {
			if (pkt_info->errors)
				netif_err(pdata, rx_err, netdev,
					  "error in received packet\n");
			dev_kfree_skb(skb);
			goto next_packet;
		}

		if (!context) {
			/* Length is cumulative, get this descriptor's length */
			dma_desc_len = desc_data->rx.len - len;
			len += dma_desc_len;

			if (dma_desc_len && !skb) {
				skb = xlgmac_create_skb(pdata, napi, desc_data,
							dma_desc_len);
				if (!skb)
					error = 1;
			} else if (dma_desc_len) {
				dma_sync_single_range_for_cpu(
						pdata->dev,
						desc_data->rx.buf.dma_base,
						desc_data->rx.buf.dma_off,
						desc_data->rx.buf.dma_len,
						DMA_FROM_DEVICE);

				skb_add_rx_frag(
					skb, skb_shinfo(skb)->nr_frags,
					desc_data->rx.buf.pa.pages,
					desc_data->rx.buf.pa.pages_offset,
					dma_desc_len,
					desc_data->rx.buf.dma_len);
				desc_data->rx.buf.pa.pages = NULL;
			}
		}

		if (incomplete || context_next)
			goto read_again;

		if (!skb)
			goto next_packet;

		/* Be sure we don't exceed the configured MTU */
		max_len = netdev->mtu + ETH_HLEN;
		if (!(netdev->features & NETIF_F_HW_VLAN_CTAG_RX) &&
		    (skb->protocol == htons(ETH_P_8021Q)))
			max_len += VLAN_HLEN;

		if (skb->len > max_len) {
			netif_err(pdata, rx_err, netdev,
				  "packet length exceeds configured MTU\n");
			dev_kfree_skb(skb);
			goto next_packet;
		}

		if (netif_msg_pktdata(pdata))
			xlgmac_print_pkt(netdev, skb, false);

		skb_checksum_none_assert(skb);
		if (XLGMAC_GET_REG_BITS(pkt_info->attributes,
					RX_PACKET_ATTRIBUTES_CSUM_DONE_POS,
				    RX_PACKET_ATTRIBUTES_CSUM_DONE_LEN))
			skb->ip_summed = CHECKSUM_UNNECESSARY;

		if (XLGMAC_GET_REG_BITS(pkt_info->attributes,
					RX_PACKET_ATTRIBUTES_VLAN_CTAG_POS,
				    RX_PACKET_ATTRIBUTES_VLAN_CTAG_LEN)) {
			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
					       pkt_info->vlan_ctag);
			pdata->stats.rx_vlan_packets++;
		}

		if (XLGMAC_GET_REG_BITS(pkt_info->attributes,
					RX_PACKET_ATTRIBUTES_RSS_HASH_POS,
				    RX_PACKET_ATTRIBUTES_RSS_HASH_LEN))
			skb_set_hash(skb, pkt_info->rss_hash,
				     pkt_info->rss_hash_type);

		skb->dev = netdev;
		skb->protocol = eth_type_trans(skb, netdev);
		skb_record_rx_queue(skb, channel->queue_index);

		napi_gro_receive(napi, skb);

next_packet:
		packet_count++;
	}

	/* Check if we need to save state before leaving */
	if (received && (incomplete || context_next)) {
		desc_data = XLGMAC_GET_DESC_DATA(ring, ring->cur);
		desc_data->state_saved = 1;
		desc_data->state.skb = skb;
		desc_data->state.len = len;
		desc_data->state.error = error;
	}

	XLGMAC_PR("packet_count = %d\n", packet_count);

	return packet_count;
}