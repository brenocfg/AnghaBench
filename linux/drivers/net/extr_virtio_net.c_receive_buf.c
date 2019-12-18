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
struct virtnet_rq_stats {int dummy; } ;
struct virtnet_info {unsigned int hdr_len; int /*<<< orphan*/  vdev; scalar_t__ big_packets; scalar_t__ mergeable_rx_bufs; struct net_device* dev; } ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  gso_size; int /*<<< orphan*/  gso_type; } ;
struct virtio_net_hdr_mrg_rxbuf {TYPE_2__ hdr; } ;
struct sk_buff {int /*<<< orphan*/  pkt_type; int /*<<< orphan*/  len; int /*<<< orphan*/  protocol; int /*<<< orphan*/  ip_summed; } ;
struct receive_queue {int /*<<< orphan*/  napi; int /*<<< orphan*/  vq; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_length_errors; } ;
struct net_device {TYPE_1__ stats; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 unsigned int ETH_HLEN ; 
 int VIRTIO_NET_HDR_F_DATA_VALID ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  give_pages (struct receive_queue*,void*) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  net_warn_ratelimited (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,unsigned int,...) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 struct sk_buff* receive_big (struct net_device*,struct virtnet_info*,struct receive_queue*,void*,unsigned int,struct virtnet_rq_stats*) ; 
 struct sk_buff* receive_mergeable (struct net_device*,struct virtnet_info*,struct receive_queue*,void*,void**,unsigned int,unsigned int*,struct virtnet_rq_stats*) ; 
 struct sk_buff* receive_small (struct net_device*,struct virtnet_info*,struct receive_queue*,void*,void**,unsigned int,unsigned int*,struct virtnet_rq_stats*) ; 
 int /*<<< orphan*/  skb_record_rx_queue (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct virtio_net_hdr_mrg_rxbuf* skb_vnet_hdr (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  virt_to_head_page (void*) ; 
 int /*<<< orphan*/  virtio_is_little_endian (int /*<<< orphan*/ ) ; 
 scalar_t__ virtio_net_hdr_to_skb (struct sk_buff*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vq2rxq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void receive_buf(struct virtnet_info *vi, struct receive_queue *rq,
			void *buf, unsigned int len, void **ctx,
			unsigned int *xdp_xmit,
			struct virtnet_rq_stats *stats)
{
	struct net_device *dev = vi->dev;
	struct sk_buff *skb;
	struct virtio_net_hdr_mrg_rxbuf *hdr;

	if (unlikely(len < vi->hdr_len + ETH_HLEN)) {
		pr_debug("%s: short packet %i\n", dev->name, len);
		dev->stats.rx_length_errors++;
		if (vi->mergeable_rx_bufs) {
			put_page(virt_to_head_page(buf));
		} else if (vi->big_packets) {
			give_pages(rq, buf);
		} else {
			put_page(virt_to_head_page(buf));
		}
		return;
	}

	if (vi->mergeable_rx_bufs)
		skb = receive_mergeable(dev, vi, rq, buf, ctx, len, xdp_xmit,
					stats);
	else if (vi->big_packets)
		skb = receive_big(dev, vi, rq, buf, len, stats);
	else
		skb = receive_small(dev, vi, rq, buf, ctx, len, xdp_xmit, stats);

	if (unlikely(!skb))
		return;

	hdr = skb_vnet_hdr(skb);

	if (hdr->hdr.flags & VIRTIO_NET_HDR_F_DATA_VALID)
		skb->ip_summed = CHECKSUM_UNNECESSARY;

	if (virtio_net_hdr_to_skb(skb, &hdr->hdr,
				  virtio_is_little_endian(vi->vdev))) {
		net_warn_ratelimited("%s: bad gso: type: %u, size: %u\n",
				     dev->name, hdr->hdr.gso_type,
				     hdr->hdr.gso_size);
		goto frame_err;
	}

	skb_record_rx_queue(skb, vq2rxq(rq->vq));
	skb->protocol = eth_type_trans(skb, dev);
	pr_debug("Receiving skb proto 0x%04x len %i type %i\n",
		 ntohs(skb->protocol), skb->len, skb->pkt_type);

	napi_gro_receive(&rq->napi, skb);
	return;

frame_err:
	dev->stats.rx_frame_errors++;
	dev_kfree_skb(skb);
}