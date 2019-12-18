#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_6__ {unsigned int error; unsigned int len; struct sk_buff* skb; } ;
struct TYPE_7__ {int /*<<< orphan*/ * pages; int /*<<< orphan*/  pages_offset; } ;
struct TYPE_8__ {TYPE_2__ pa; int /*<<< orphan*/  dma_len; int /*<<< orphan*/  dma_off; int /*<<< orphan*/  dma_base; } ;
struct TYPE_9__ {TYPE_3__ buf; } ;
struct xgbe_ring_data {int state_saved; TYPE_1__ state; TYPE_4__ rx; } ;
struct xgbe_packet_data {int /*<<< orphan*/  rss_hash_type; int /*<<< orphan*/  rss_hash; int /*<<< orphan*/  attributes; int /*<<< orphan*/  rx_tstamp; int /*<<< orphan*/  vlan_ctag; scalar_t__ errors; } ;
struct xgbe_ring {int cur; struct xgbe_packet_data packet_data; } ;
struct napi_struct {int dummy; } ;
struct xgbe_hw_if {scalar_t__ (* dev_read ) (struct xgbe_channel*) ;} ;
struct xgbe_prv_data {int /*<<< orphan*/  tstamp_tc; int /*<<< orphan*/  dev; struct napi_struct napi; scalar_t__ per_channel_irq; struct net_device* netdev; struct xgbe_hw_if hw_if; } ;
struct xgbe_channel {int /*<<< orphan*/  queue_index; struct napi_struct napi; struct xgbe_ring* rx_ring; struct xgbe_prv_data* pdata; } ;
struct skb_shared_hwtstamps {int /*<<< orphan*/  hwtstamp; } ;
struct sk_buff {scalar_t__ protocol; unsigned int len; int encapsulation; int csum_level; struct net_device* dev; int /*<<< orphan*/  ip_summed; } ;
struct net_device {unsigned int mtu; int features; } ;
struct TYPE_10__ {int /*<<< orphan*/  nr_frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  CONTEXT ; 
 int /*<<< orphan*/  CONTEXT_NEXT ; 
 int /*<<< orphan*/  CSUM_DONE ; 
 int /*<<< orphan*/  DBGPR (char*,int) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 unsigned int ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  LAST ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int /*<<< orphan*/  RSS_HASH ; 
 int /*<<< orphan*/  RX_PACKET_ATTRIBUTES ; 
 int /*<<< orphan*/  RX_TSTAMP ; 
 int /*<<< orphan*/  TNP ; 
 int /*<<< orphan*/  TNPCSUM_DONE ; 
 int /*<<< orphan*/  VLAN_CTAG ; 
 scalar_t__ VLAN_HLEN ; 
 struct xgbe_ring_data* XGBE_GET_DESC_DATA (struct xgbe_ring*,int) ; 
 int XGBE_RX_DESC_CNT ; 
 int XGMAC_GET_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_sync_single_range_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ eth_type_trans (struct sk_buff*,struct net_device*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct xgbe_packet_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  napi_gro_receive (struct napi_struct*,struct sk_buff*) ; 
 int /*<<< orphan*/  netif_err (struct xgbe_prv_data*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 scalar_t__ netif_msg_pktdata (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  ns_to_ktime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rx_err ; 
 int /*<<< orphan*/  skb_add_rx_frag (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 
 struct skb_shared_hwtstamps* skb_hwtstamps (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_record_rx_queue (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_hash (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ stub1 (struct xgbe_channel*) ; 
 int /*<<< orphan*/  timecounter_cyc2time (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct sk_buff* xgbe_create_skb (struct xgbe_prv_data*,struct napi_struct*,struct xgbe_ring_data*,unsigned int) ; 
 int /*<<< orphan*/  xgbe_print_pkt (struct net_device*,struct sk_buff*,int) ; 
 unsigned int xgbe_rx_buf1_len (struct xgbe_ring_data*,struct xgbe_packet_data*) ; 
 unsigned int xgbe_rx_buf2_len (struct xgbe_ring_data*,struct xgbe_packet_data*,unsigned int) ; 
 int xgbe_rx_dirty_desc (struct xgbe_ring*) ; 
 int /*<<< orphan*/  xgbe_rx_refresh (struct xgbe_channel*) ; 

__attribute__((used)) static int xgbe_rx_poll(struct xgbe_channel *channel, int budget)
{
	struct xgbe_prv_data *pdata = channel->pdata;
	struct xgbe_hw_if *hw_if = &pdata->hw_if;
	struct xgbe_ring *ring = channel->rx_ring;
	struct xgbe_ring_data *rdata;
	struct xgbe_packet_data *packet;
	struct net_device *netdev = pdata->netdev;
	struct napi_struct *napi;
	struct sk_buff *skb;
	struct skb_shared_hwtstamps *hwtstamps;
	unsigned int last, error, context_next, context;
	unsigned int len, buf1_len, buf2_len, max_len;
	unsigned int received = 0;
	int packet_count = 0;

	DBGPR("-->xgbe_rx_poll: budget=%d\n", budget);

	/* Nothing to do if there isn't a Rx ring for this channel */
	if (!ring)
		return 0;

	last = 0;
	context_next = 0;

	napi = (pdata->per_channel_irq) ? &channel->napi : &pdata->napi;

	rdata = XGBE_GET_DESC_DATA(ring, ring->cur);
	packet = &ring->packet_data;
	while (packet_count < budget) {
		DBGPR("  cur = %d\n", ring->cur);

		/* First time in loop see if we need to restore state */
		if (!received && rdata->state_saved) {
			skb = rdata->state.skb;
			error = rdata->state.error;
			len = rdata->state.len;
		} else {
			memset(packet, 0, sizeof(*packet));
			skb = NULL;
			error = 0;
			len = 0;
		}

read_again:
		rdata = XGBE_GET_DESC_DATA(ring, ring->cur);

		if (xgbe_rx_dirty_desc(ring) > (XGBE_RX_DESC_CNT >> 3))
			xgbe_rx_refresh(channel);

		if (hw_if->dev_read(channel))
			break;

		received++;
		ring->cur++;

		last = XGMAC_GET_BITS(packet->attributes, RX_PACKET_ATTRIBUTES,
				      LAST);
		context_next = XGMAC_GET_BITS(packet->attributes,
					      RX_PACKET_ATTRIBUTES,
					      CONTEXT_NEXT);
		context = XGMAC_GET_BITS(packet->attributes,
					 RX_PACKET_ATTRIBUTES,
					 CONTEXT);

		/* Earlier error, just drain the remaining data */
		if ((!last || context_next) && error)
			goto read_again;

		if (error || packet->errors) {
			if (packet->errors)
				netif_err(pdata, rx_err, netdev,
					  "error in received packet\n");
			dev_kfree_skb(skb);
			goto next_packet;
		}

		if (!context) {
			/* Get the data length in the descriptor buffers */
			buf1_len = xgbe_rx_buf1_len(rdata, packet);
			len += buf1_len;
			buf2_len = xgbe_rx_buf2_len(rdata, packet, len);
			len += buf2_len;

			if (!skb) {
				skb = xgbe_create_skb(pdata, napi, rdata,
						      buf1_len);
				if (!skb) {
					error = 1;
					goto skip_data;
				}
			}

			if (buf2_len) {
				dma_sync_single_range_for_cpu(pdata->dev,
							rdata->rx.buf.dma_base,
							rdata->rx.buf.dma_off,
							rdata->rx.buf.dma_len,
							DMA_FROM_DEVICE);

				skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags,
						rdata->rx.buf.pa.pages,
						rdata->rx.buf.pa.pages_offset,
						buf2_len,
						rdata->rx.buf.dma_len);
				rdata->rx.buf.pa.pages = NULL;
			}
		}

skip_data:
		if (!last || context_next)
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
			xgbe_print_pkt(netdev, skb, false);

		skb_checksum_none_assert(skb);
		if (XGMAC_GET_BITS(packet->attributes,
				   RX_PACKET_ATTRIBUTES, CSUM_DONE))
			skb->ip_summed = CHECKSUM_UNNECESSARY;

		if (XGMAC_GET_BITS(packet->attributes,
				   RX_PACKET_ATTRIBUTES, TNP)) {
			skb->encapsulation = 1;

			if (XGMAC_GET_BITS(packet->attributes,
					   RX_PACKET_ATTRIBUTES, TNPCSUM_DONE))
				skb->csum_level = 1;
		}

		if (XGMAC_GET_BITS(packet->attributes,
				   RX_PACKET_ATTRIBUTES, VLAN_CTAG))
			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
					       packet->vlan_ctag);

		if (XGMAC_GET_BITS(packet->attributes,
				   RX_PACKET_ATTRIBUTES, RX_TSTAMP)) {
			u64 nsec;

			nsec = timecounter_cyc2time(&pdata->tstamp_tc,
						    packet->rx_tstamp);
			hwtstamps = skb_hwtstamps(skb);
			hwtstamps->hwtstamp = ns_to_ktime(nsec);
		}

		if (XGMAC_GET_BITS(packet->attributes,
				   RX_PACKET_ATTRIBUTES, RSS_HASH))
			skb_set_hash(skb, packet->rss_hash,
				     packet->rss_hash_type);

		skb->dev = netdev;
		skb->protocol = eth_type_trans(skb, netdev);
		skb_record_rx_queue(skb, channel->queue_index);

		napi_gro_receive(napi, skb);

next_packet:
		packet_count++;
	}

	/* Check if we need to save state before leaving */
	if (received && (!last || context_next)) {
		rdata = XGBE_GET_DESC_DATA(ring, ring->cur);
		rdata->state_saved = 1;
		rdata->state.skb = skb;
		rdata->state.len = len;
		rdata->state.error = error;
	}

	DBGPR("<--xgbe_rx_poll: packet_count = %d\n", packet_count);

	return packet_count;
}