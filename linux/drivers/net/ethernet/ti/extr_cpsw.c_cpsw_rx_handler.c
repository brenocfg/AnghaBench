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
struct xdp_buff {void* data_hard_start; void* data; void* data_end; int /*<<< orphan*/ * rxq; } ;
struct sk_buff {int /*<<< orphan*/  protocol; struct net_device* dev; } ;
struct page_pool {int dummy; } ;
struct page {int dummy; } ;
struct TYPE_7__ {int rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; } ;
struct net_device {TYPE_3__ stats; } ;
struct cpsw_priv {scalar_t__ rx_ts_enabled; int /*<<< orphan*/ * xdp_rxq; scalar_t__ xdp_prog; } ;
struct cpsw_meta_xdp {int ch; struct net_device* ndev; } ;
struct TYPE_6__ {scalar_t__ dual_emac; } ;
struct cpsw_common {int rx_packet_max; TYPE_4__* rxv; int /*<<< orphan*/  cpts; scalar_t__ usage_count; TYPE_2__ data; struct page_pool** page_pool; TYPE_1__* slaves; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_8__ {int /*<<< orphan*/  ch; } ;
struct TYPE_5__ {struct net_device* ndev; } ;

/* Variables and functions */
 int CPDMA_RX_SOURCE_PORT (int) ; 
 int CPDMA_RX_VLAN_ENCAP ; 
 int CPSW_HEADROOM ; 
 int CPSW_RX_VLAN_ENCAP_HDR_SIZE ; 
 int CPSW_XDP_PASS ; 
 int CPSW_XMETA_OFFSET ; 
 int ENOMEM ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct sk_buff* build_skb (void*,int /*<<< orphan*/ ) ; 
 int cpdma_chan_submit_mapped (int /*<<< orphan*/ ,struct page*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int cpsw_run_xdp (struct cpsw_priv*,int,struct xdp_buff*,struct page*) ; 
 int /*<<< orphan*/  cpsw_rx_vlan_encap (struct sk_buff*) ; 
 int /*<<< orphan*/  cpsw_rxbuf_total_len (int) ; 
 int /*<<< orphan*/  cpts_rx_timestamp (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 struct cpsw_common* ndev_to_cpsw (struct net_device*) ; 
 struct cpsw_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 void* page_address (struct page*) ; 
 struct page* page_pool_dev_alloc_pages (struct page_pool*) ; 
 scalar_t__ page_pool_get_dma_addr (struct page*) ; 
 int /*<<< orphan*/  page_pool_recycle_direct (struct page_pool*,struct page*) ; 
 int /*<<< orphan*/  page_pool_release_page (struct page_pool*,struct page*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xdp_set_data_meta_invalid (struct xdp_buff*) ; 

__attribute__((used)) static void cpsw_rx_handler(void *token, int len, int status)
{
	struct page		*new_page, *page = token;
	void			*pa = page_address(page);
	struct cpsw_meta_xdp	*xmeta = pa + CPSW_XMETA_OFFSET;
	struct cpsw_common	*cpsw = ndev_to_cpsw(xmeta->ndev);
	int			pkt_size = cpsw->rx_packet_max;
	int			ret = 0, port, ch = xmeta->ch;
	int			headroom = CPSW_HEADROOM;
	struct net_device	*ndev = xmeta->ndev;
	struct cpsw_priv	*priv;
	struct page_pool	*pool;
	struct sk_buff		*skb;
	struct xdp_buff		xdp;
	dma_addr_t		dma;

	if (cpsw->data.dual_emac && status >= 0) {
		port = CPDMA_RX_SOURCE_PORT(status);
		if (port)
			ndev = cpsw->slaves[--port].ndev;
	}

	priv = netdev_priv(ndev);
	pool = cpsw->page_pool[ch];
	if (unlikely(status < 0) || unlikely(!netif_running(ndev))) {
		/* In dual emac mode check for all interfaces */
		if (cpsw->data.dual_emac && cpsw->usage_count &&
		    (status >= 0)) {
			/* The packet received is for the interface which
			 * is already down and the other interface is up
			 * and running, instead of freeing which results
			 * in reducing of the number of rx descriptor in
			 * DMA engine, requeue page back to cpdma.
			 */
			new_page = page;
			goto requeue;
		}

		/* the interface is going down, pages are purged */
		page_pool_recycle_direct(pool, page);
		return;
	}

	new_page = page_pool_dev_alloc_pages(pool);
	if (unlikely(!new_page)) {
		new_page = page;
		ndev->stats.rx_dropped++;
		goto requeue;
	}

	if (priv->xdp_prog) {
		if (status & CPDMA_RX_VLAN_ENCAP) {
			xdp.data = pa + CPSW_HEADROOM +
				   CPSW_RX_VLAN_ENCAP_HDR_SIZE;
			xdp.data_end = xdp.data + len -
				       CPSW_RX_VLAN_ENCAP_HDR_SIZE;
		} else {
			xdp.data = pa + CPSW_HEADROOM;
			xdp.data_end = xdp.data + len;
		}

		xdp_set_data_meta_invalid(&xdp);

		xdp.data_hard_start = pa;
		xdp.rxq = &priv->xdp_rxq[ch];

		ret = cpsw_run_xdp(priv, ch, &xdp, page);
		if (ret != CPSW_XDP_PASS)
			goto requeue;

		/* XDP prog might have changed packet data and boundaries */
		len = xdp.data_end - xdp.data;
		headroom = xdp.data - xdp.data_hard_start;

		/* XDP prog can modify vlan tag, so can't use encap header */
		status &= ~CPDMA_RX_VLAN_ENCAP;
	}

	/* pass skb to netstack if no XDP prog or returned XDP_PASS */
	skb = build_skb(pa, cpsw_rxbuf_total_len(pkt_size));
	if (!skb) {
		ndev->stats.rx_dropped++;
		page_pool_recycle_direct(pool, page);
		goto requeue;
	}

	skb_reserve(skb, headroom);
	skb_put(skb, len);
	skb->dev = ndev;
	if (status & CPDMA_RX_VLAN_ENCAP)
		cpsw_rx_vlan_encap(skb);
	if (priv->rx_ts_enabled)
		cpts_rx_timestamp(cpsw->cpts, skb);
	skb->protocol = eth_type_trans(skb, ndev);

	/* unmap page as no netstack skb page recycling */
	page_pool_release_page(pool, page);
	netif_receive_skb(skb);

	ndev->stats.rx_bytes += len;
	ndev->stats.rx_packets++;

requeue:
	xmeta = page_address(new_page) + CPSW_XMETA_OFFSET;
	xmeta->ndev = ndev;
	xmeta->ch = ch;

	dma = page_pool_get_dma_addr(new_page) + CPSW_HEADROOM;
	ret = cpdma_chan_submit_mapped(cpsw->rxv[ch].ch, new_page, dma,
				       pkt_size, 0);
	if (ret < 0) {
		WARN_ON(ret == -ENOMEM);
		page_pool_recycle_direct(pool, new_page);
	}
}