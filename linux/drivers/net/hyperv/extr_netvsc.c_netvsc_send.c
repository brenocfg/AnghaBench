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
typedef  scalar_t__ u32 ;
struct sk_buff {int dummy; } ;
struct rndis_message {int dummy; } ;
struct netvsc_device {scalar_t__ max_pkt; scalar_t__ pkt_align; scalar_t__ send_section_size; struct netvsc_channel* chan_table; scalar_t__ destroy; } ;
struct multi_send_data {scalar_t__ count; struct hv_netvsc_packet* pkt; struct sk_buff* skb; } ;
struct netvsc_channel {struct multi_send_data msd; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_send_full; } ;
struct net_device_context {TYPE_1__ eth_stats; struct hv_device* device_ctx; int /*<<< orphan*/  nvdev; } ;
struct net_device {int dummy; } ;
struct hv_page_buffer {int dummy; } ;
struct hv_netvsc_packet {scalar_t__ total_data_buflen; size_t q_idx; unsigned int send_buf_index; int cp_partial; scalar_t__ rmsg_size; scalar_t__ total_bytes; scalar_t__ total_packets; scalar_t__ page_buf_cnt; scalar_t__ rmsg_pgcnt; } ;
struct hv_device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 unsigned int NETVSC_INVALID_INDEX ; 
 int /*<<< orphan*/  dev_consume_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  move_pkt_msd (struct hv_netvsc_packet**,struct sk_buff**,struct multi_send_data*) ; 
 int /*<<< orphan*/  netdev_get_tx_queue (struct net_device*,size_t) ; 
 struct net_device_context* netdev_priv (struct net_device*) ; 
 scalar_t__ netdev_xmit_more () ; 
 int /*<<< orphan*/  netif_xmit_stopped (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netvsc_copy_to_send_buf (struct netvsc_device*,unsigned int,scalar_t__,struct hv_netvsc_packet*,struct rndis_message*,struct hv_page_buffer*,int) ; 
 int /*<<< orphan*/  netvsc_free_send_slot (struct netvsc_device*,unsigned int) ; 
 unsigned int netvsc_get_next_send_section (struct netvsc_device*) ; 
 int netvsc_send_pkt (struct hv_device*,struct hv_netvsc_packet*,struct netvsc_device*,struct hv_page_buffer*,struct sk_buff*) ; 
 struct netvsc_device* rcu_dereference_bh (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int netvsc_send(struct net_device *ndev,
		struct hv_netvsc_packet *packet,
		struct rndis_message *rndis_msg,
		struct hv_page_buffer *pb,
		struct sk_buff *skb)
{
	struct net_device_context *ndev_ctx = netdev_priv(ndev);
	struct netvsc_device *net_device
		= rcu_dereference_bh(ndev_ctx->nvdev);
	struct hv_device *device = ndev_ctx->device_ctx;
	int ret = 0;
	struct netvsc_channel *nvchan;
	u32 pktlen = packet->total_data_buflen, msd_len = 0;
	unsigned int section_index = NETVSC_INVALID_INDEX;
	struct multi_send_data *msdp;
	struct hv_netvsc_packet *msd_send = NULL, *cur_send = NULL;
	struct sk_buff *msd_skb = NULL;
	bool try_batch, xmit_more;

	/* If device is rescinded, return error and packet will get dropped. */
	if (unlikely(!net_device || net_device->destroy))
		return -ENODEV;

	nvchan = &net_device->chan_table[packet->q_idx];
	packet->send_buf_index = NETVSC_INVALID_INDEX;
	packet->cp_partial = false;

	/* Send control message directly without accessing msd (Multi-Send
	 * Data) field which may be changed during data packet processing.
	 */
	if (!skb)
		return netvsc_send_pkt(device, packet, net_device, pb, skb);

	/* batch packets in send buffer if possible */
	msdp = &nvchan->msd;
	if (msdp->pkt)
		msd_len = msdp->pkt->total_data_buflen;

	try_batch =  msd_len > 0 && msdp->count < net_device->max_pkt;
	if (try_batch && msd_len + pktlen + net_device->pkt_align <
	    net_device->send_section_size) {
		section_index = msdp->pkt->send_buf_index;

	} else if (try_batch && msd_len + packet->rmsg_size <
		   net_device->send_section_size) {
		section_index = msdp->pkt->send_buf_index;
		packet->cp_partial = true;

	} else if (pktlen + net_device->pkt_align <
		   net_device->send_section_size) {
		section_index = netvsc_get_next_send_section(net_device);
		if (unlikely(section_index == NETVSC_INVALID_INDEX)) {
			++ndev_ctx->eth_stats.tx_send_full;
		} else {
			move_pkt_msd(&msd_send, &msd_skb, msdp);
			msd_len = 0;
		}
	}

	/* Keep aggregating only if stack says more data is coming
	 * and not doing mixed modes send and not flow blocked
	 */
	xmit_more = netdev_xmit_more() &&
		!packet->cp_partial &&
		!netif_xmit_stopped(netdev_get_tx_queue(ndev, packet->q_idx));

	if (section_index != NETVSC_INVALID_INDEX) {
		netvsc_copy_to_send_buf(net_device,
					section_index, msd_len,
					packet, rndis_msg, pb, xmit_more);

		packet->send_buf_index = section_index;

		if (packet->cp_partial) {
			packet->page_buf_cnt -= packet->rmsg_pgcnt;
			packet->total_data_buflen = msd_len + packet->rmsg_size;
		} else {
			packet->page_buf_cnt = 0;
			packet->total_data_buflen += msd_len;
		}

		if (msdp->pkt) {
			packet->total_packets += msdp->pkt->total_packets;
			packet->total_bytes += msdp->pkt->total_bytes;
		}

		if (msdp->skb)
			dev_consume_skb_any(msdp->skb);

		if (xmit_more) {
			msdp->skb = skb;
			msdp->pkt = packet;
			msdp->count++;
		} else {
			cur_send = packet;
			msdp->skb = NULL;
			msdp->pkt = NULL;
			msdp->count = 0;
		}
	} else {
		move_pkt_msd(&msd_send, &msd_skb, msdp);
		cur_send = packet;
	}

	if (msd_send) {
		int m_ret = netvsc_send_pkt(device, msd_send, net_device,
					    NULL, msd_skb);

		if (m_ret != 0) {
			netvsc_free_send_slot(net_device,
					      msd_send->send_buf_index);
			dev_kfree_skb_any(msd_skb);
		}
	}

	if (cur_send)
		ret = netvsc_send_pkt(device, cur_send, net_device, pb, skb);

	if (ret != 0 && section_index != NETVSC_INVALID_INDEX)
		netvsc_free_send_slot(net_device, section_index);

	return ret;
}