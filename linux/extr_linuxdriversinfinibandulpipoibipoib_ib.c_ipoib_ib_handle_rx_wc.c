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
struct TYPE_9__ {scalar_t__ interface_id; } ;
union ib_gid {int* raw; TYPE_3__ global; } ;
typedef  int /*<<< orphan*/  u64 ;
struct sk_buff {scalar_t__ pkt_type; int /*<<< orphan*/  ip_summed; struct net_device* dev; scalar_t__ len; scalar_t__ data; int /*<<< orphan*/  protocol; } ;
struct TYPE_12__ {int /*<<< orphan*/  multicast; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; } ;
struct net_device {int features; TYPE_6__ stats; scalar_t__ broadcast; } ;
struct ipoib_header {int /*<<< orphan*/  proto; } ;
struct TYPE_10__ {scalar_t__ interface_id; } ;
struct TYPE_11__ {TYPE_4__ global; } ;
struct ipoib_dev_priv {scalar_t__ local_lid; int /*<<< orphan*/  recv_napi; TYPE_5__ local_gid; TYPE_2__* qp; TYPE_1__* rx_ring; } ;
struct ib_wc {unsigned int wr_id; scalar_t__ status; unsigned int byte_len; scalar_t__ slid; int wc_flags; scalar_t__ src_qp; int /*<<< orphan*/  vendor_err; } ;
struct ib_grh {union ib_gid sgid; union ib_gid dgid; } ;
struct TYPE_8__ {scalar_t__ qp_num; } ;
struct TYPE_7__ {int /*<<< orphan*/ * mapping; struct sk_buff* skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  IB_GRH_BYTES ; 
 int IB_WC_GRH ; 
 int IB_WC_IP_CSUM_OK ; 
 scalar_t__ IB_WC_SUCCESS ; 
 scalar_t__ IB_WC_WR_FLUSH_ERR ; 
 unsigned int IPOIB_OP_RECV ; 
 int IPOIB_UD_RX_SG ; 
 int NETIF_F_RXCSUM ; 
 scalar_t__ PACKET_BROADCAST ; 
 scalar_t__ PACKET_HOST ; 
 scalar_t__ PACKET_MULTICAST ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  ipoib_alloc_rx_skb (struct net_device*,unsigned int) ; 
 int /*<<< orphan*/  ipoib_dbg_data (struct ipoib_dev_priv*,char*,unsigned int,scalar_t__) ; 
 int ipoib_ib_post_receive (struct net_device*,unsigned int) ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 unsigned int ipoib_recvq_size ; 
 int /*<<< orphan*/  ipoib_ud_dma_unmap_rx (struct ipoib_dev_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*,unsigned int,...) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ memcmp (union ib_gid*,scalar_t__,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_add_pseudo_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void ipoib_ib_handle_rx_wc(struct net_device *dev, struct ib_wc *wc)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);
	unsigned int wr_id = wc->wr_id & ~IPOIB_OP_RECV;
	struct sk_buff *skb;
	u64 mapping[IPOIB_UD_RX_SG];
	union ib_gid *dgid;
	union ib_gid *sgid;

	ipoib_dbg_data(priv, "recv completion: id %d, status: %d\n",
		       wr_id, wc->status);

	if (unlikely(wr_id >= ipoib_recvq_size)) {
		ipoib_warn(priv, "recv completion event with wrid %d (> %d)\n",
			   wr_id, ipoib_recvq_size);
		return;
	}

	skb  = priv->rx_ring[wr_id].skb;

	if (unlikely(wc->status != IB_WC_SUCCESS)) {
		if (wc->status != IB_WC_WR_FLUSH_ERR)
			ipoib_warn(priv,
				   "failed recv event (status=%d, wrid=%d vend_err %#x)\n",
				   wc->status, wr_id, wc->vendor_err);
		ipoib_ud_dma_unmap_rx(priv, priv->rx_ring[wr_id].mapping);
		dev_kfree_skb_any(skb);
		priv->rx_ring[wr_id].skb = NULL;
		return;
	}

	memcpy(mapping, priv->rx_ring[wr_id].mapping,
	       IPOIB_UD_RX_SG * sizeof(*mapping));

	/*
	 * If we can't allocate a new RX buffer, dump
	 * this packet and reuse the old buffer.
	 */
	if (unlikely(!ipoib_alloc_rx_skb(dev, wr_id))) {
		++dev->stats.rx_dropped;
		goto repost;
	}

	ipoib_dbg_data(priv, "received %d bytes, SLID 0x%04x\n",
		       wc->byte_len, wc->slid);

	ipoib_ud_dma_unmap_rx(priv, mapping);

	skb_put(skb, wc->byte_len);

	/* First byte of dgid signals multicast when 0xff */
	dgid = &((struct ib_grh *)skb->data)->dgid;

	if (!(wc->wc_flags & IB_WC_GRH) || dgid->raw[0] != 0xff)
		skb->pkt_type = PACKET_HOST;
	else if (memcmp(dgid, dev->broadcast + 4, sizeof(union ib_gid)) == 0)
		skb->pkt_type = PACKET_BROADCAST;
	else
		skb->pkt_type = PACKET_MULTICAST;

	sgid = &((struct ib_grh *)skb->data)->sgid;

	/*
	 * Drop packets that this interface sent, ie multicast packets
	 * that the HCA has replicated.
	 */
	if (wc->slid == priv->local_lid && wc->src_qp == priv->qp->qp_num) {
		int need_repost = 1;

		if ((wc->wc_flags & IB_WC_GRH) &&
		    sgid->global.interface_id != priv->local_gid.global.interface_id)
			need_repost = 0;

		if (need_repost) {
			dev_kfree_skb_any(skb);
			goto repost;
		}
	}

	skb_pull(skb, IB_GRH_BYTES);

	skb->protocol = ((struct ipoib_header *) skb->data)->proto;
	skb_add_pseudo_hdr(skb);

	++dev->stats.rx_packets;
	dev->stats.rx_bytes += skb->len;
	if (skb->pkt_type == PACKET_MULTICAST)
		dev->stats.multicast++;

	skb->dev = dev;
	if ((dev->features & NETIF_F_RXCSUM) &&
			likely(wc->wc_flags & IB_WC_IP_CSUM_OK))
		skb->ip_summed = CHECKSUM_UNNECESSARY;

	napi_gro_receive(&priv->recv_napi, skb);

repost:
	if (unlikely(ipoib_ib_post_receive(dev, wr_id)))
		ipoib_warn(priv, "ipoib_ib_post_receive failed "
			   "for buf %d\n", wr_id);
}