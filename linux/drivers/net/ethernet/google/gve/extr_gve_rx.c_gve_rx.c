#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
typedef  scalar_t__ u16 ;
struct sk_buff {int /*<<< orphan*/  csum; int /*<<< orphan*/  ip_summed; } ;
struct net_device {int dummy; } ;
struct napi_struct {int dummy; } ;
struct gve_rx_slot_page_info {int /*<<< orphan*/  page; } ;
struct TYPE_8__ {int /*<<< orphan*/ * data_ring; TYPE_3__* qpl; struct gve_rx_slot_page_info* page_info; } ;
struct gve_rx_ring {size_t ntfy_id; TYPE_4__ data; struct gve_priv* gve; } ;
struct gve_rx_desc {int flags_seq; int /*<<< orphan*/  rss_hash; scalar_t__ csum; int /*<<< orphan*/  len; } ;
struct gve_priv {scalar_t__ rx_copybreak; TYPE_2__* pdev; struct net_device* dev; TYPE_1__* ntfy_blocks; } ;
typedef  int netdev_features_t ;
struct TYPE_7__ {int /*<<< orphan*/ * page_buses; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {struct napi_struct napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_COMPLETE ; 
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int GVE_RXF_ERR ; 
 scalar_t__ GVE_RX_PAD ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_RXHASH ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csum_unfold (scalar_t__) ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gve_can_recycle_pages (struct net_device*) ; 
 scalar_t__ gve_needs_rss (int) ; 
 int /*<<< orphan*/  gve_rss_type (int) ; 
 struct sk_buff* gve_rx_add_frags (struct net_device*,struct napi_struct*,struct gve_rx_slot_page_info*,scalar_t__) ; 
 struct sk_buff* gve_rx_copy (struct net_device*,struct napi_struct*,struct gve_rx_slot_page_info*,scalar_t__) ; 
 int /*<<< orphan*/  gve_rx_flip_buff (struct gve_rx_slot_page_info*,int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  napi_gro_frags (struct napi_struct*) ; 
 int /*<<< orphan*/  napi_gro_receive (struct napi_struct*,struct sk_buff*) ; 
 int page_count (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_is_nonlinear (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_hash (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool gve_rx(struct gve_rx_ring *rx, struct gve_rx_desc *rx_desc,
		   netdev_features_t feat, u32 idx)
{
	struct gve_rx_slot_page_info *page_info;
	struct gve_priv *priv = rx->gve;
	struct napi_struct *napi = &priv->ntfy_blocks[rx->ntfy_id].napi;
	struct net_device *dev = priv->dev;
	struct sk_buff *skb;
	int pagecount;
	u16 len;

	/* drop this packet */
	if (unlikely(rx_desc->flags_seq & GVE_RXF_ERR))
		return true;

	len = be16_to_cpu(rx_desc->len) - GVE_RX_PAD;
	page_info = &rx->data.page_info[idx];
	dma_sync_single_for_cpu(&priv->pdev->dev, rx->data.qpl->page_buses[idx],
				PAGE_SIZE, DMA_FROM_DEVICE);

	/* gvnic can only receive into registered segments. If the buffer
	 * can't be recycled, our only choice is to copy the data out of
	 * it so that we can return it to the device.
	 */

	if (PAGE_SIZE == 4096) {
		if (len <= priv->rx_copybreak) {
			/* Just copy small packets */
			skb = gve_rx_copy(dev, napi, page_info, len);
			goto have_skb;
		}
		if (unlikely(!gve_can_recycle_pages(dev))) {
			skb = gve_rx_copy(dev, napi, page_info, len);
			goto have_skb;
		}
		pagecount = page_count(page_info->page);
		if (pagecount == 1) {
			/* No part of this page is used by any SKBs; we attach
			 * the page fragment to a new SKB and pass it up the
			 * stack.
			 */
			skb = gve_rx_add_frags(dev, napi, page_info, len);
			if (!skb)
				return true;
			/* Make sure the kernel stack can't release the page */
			get_page(page_info->page);
			/* "flip" to other packet buffer on this page */
			gve_rx_flip_buff(page_info, &rx->data.data_ring[idx]);
		} else if (pagecount >= 2) {
			/* We have previously passed the other half of this
			 * page up the stack, but it has not yet been freed.
			 */
			skb = gve_rx_copy(dev, napi, page_info, len);
		} else {
			WARN(pagecount < 1, "Pagecount should never be < 1");
			return false;
		}
	} else {
		skb = gve_rx_copy(dev, napi, page_info, len);
	}

have_skb:
	/* We didn't manage to allocate an skb but we haven't had any
	 * reset worthy failures.
	 */
	if (!skb)
		return true;

	if (likely(feat & NETIF_F_RXCSUM)) {
		/* NIC passes up the partial sum */
		if (rx_desc->csum)
			skb->ip_summed = CHECKSUM_COMPLETE;
		else
			skb->ip_summed = CHECKSUM_NONE;
		skb->csum = csum_unfold(rx_desc->csum);
	}

	/* parse flags & pass relevant info up */
	if (likely(feat & NETIF_F_RXHASH) &&
	    gve_needs_rss(rx_desc->flags_seq))
		skb_set_hash(skb, be32_to_cpu(rx_desc->rss_hash),
			     gve_rss_type(rx_desc->flags_seq));

	if (skb_is_nonlinear(skb))
		napi_gro_frags(napi);
	else
		napi_gro_receive(napi, skb);
	return true;
}