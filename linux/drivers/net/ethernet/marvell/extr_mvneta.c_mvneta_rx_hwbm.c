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
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
struct sk_buff {void* protocol; } ;
struct TYPE_5__ {int /*<<< orphan*/  rx_errors; } ;
struct net_device {TYPE_1__ stats; } ;
struct napi_struct {int dummy; } ;
struct mvneta_rx_queue {int /*<<< orphan*/  refill_err; } ;
struct mvneta_rx_desc {scalar_t__ status; int data_size; int /*<<< orphan*/  buf_phys_addr; scalar_t__ buf_cookie; } ;
struct mvneta_port {int /*<<< orphan*/  stats; TYPE_3__* bm_priv; struct net_device* dev; } ;
struct mvneta_pcpu_stats {int /*<<< orphan*/  syncp; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct TYPE_8__ {scalar_t__ frag_size; } ;
struct mvneta_bm_pool {int /*<<< orphan*/  buf_size; TYPE_4__ hwbm_pool; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_7__ {TYPE_2__* pdev; struct mvneta_bm_pool* bm_pools; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ETH_FCS_LEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int MVNETA_MH_SIZE ; 
 scalar_t__ MVNETA_RXD_ERR_SUMMARY ; 
 size_t MVNETA_RX_GET_BM_POOL_ID (struct mvneta_rx_desc*) ; 
 int NET_SKB_PAD ; 
 scalar_t__ PAGE_SIZE ; 
 struct sk_buff* build_skb (unsigned char*,scalar_t__) ; 
 int /*<<< orphan*/  dma_sync_single_range_for_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int hwbm_pool_refill (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvneta_bm_pool_put_bp (TYPE_3__*,struct mvneta_bm_pool*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvneta_rx_csum (struct mvneta_port*,scalar_t__,struct sk_buff*) ; 
 int /*<<< orphan*/  mvneta_rx_error (struct mvneta_port*,struct mvneta_rx_desc*) ; 
 int mvneta_rxq_busy_desc_num_get (struct mvneta_port*,struct mvneta_rx_queue*) ; 
 int /*<<< orphan*/  mvneta_rxq_desc_is_first_last (scalar_t__) ; 
 int /*<<< orphan*/  mvneta_rxq_desc_num_update (struct mvneta_port*,struct mvneta_rx_queue*,int,int) ; 
 struct mvneta_rx_desc* mvneta_rxq_next_desc_get (struct mvneta_rx_queue*) ; 
 int /*<<< orphan*/  napi_gro_receive (struct napi_struct*,struct sk_buff*) ; 
 struct sk_buff* netdev_alloc_skb_ip_align (struct net_device*,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int rx_copybreak ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,unsigned char*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 struct mvneta_pcpu_stats* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int mvneta_rx_hwbm(struct napi_struct *napi,
			  struct mvneta_port *pp, int rx_todo,
			  struct mvneta_rx_queue *rxq)
{
	struct net_device *dev = pp->dev;
	int rx_done;
	u32 rcvd_pkts = 0;
	u32 rcvd_bytes = 0;

	/* Get number of received packets */
	rx_done = mvneta_rxq_busy_desc_num_get(pp, rxq);

	if (rx_todo > rx_done)
		rx_todo = rx_done;

	rx_done = 0;

	/* Fairness NAPI loop */
	while (rx_done < rx_todo) {
		struct mvneta_rx_desc *rx_desc = mvneta_rxq_next_desc_get(rxq);
		struct mvneta_bm_pool *bm_pool = NULL;
		struct sk_buff *skb;
		unsigned char *data;
		dma_addr_t phys_addr;
		u32 rx_status, frag_size;
		int rx_bytes, err;
		u8 pool_id;

		rx_done++;
		rx_status = rx_desc->status;
		rx_bytes = rx_desc->data_size - (ETH_FCS_LEN + MVNETA_MH_SIZE);
		data = (u8 *)(uintptr_t)rx_desc->buf_cookie;
		phys_addr = rx_desc->buf_phys_addr;
		pool_id = MVNETA_RX_GET_BM_POOL_ID(rx_desc);
		bm_pool = &pp->bm_priv->bm_pools[pool_id];

		if (!mvneta_rxq_desc_is_first_last(rx_status) ||
		    (rx_status & MVNETA_RXD_ERR_SUMMARY)) {
err_drop_frame_ret_pool:
			/* Return the buffer to the pool */
			mvneta_bm_pool_put_bp(pp->bm_priv, bm_pool,
					      rx_desc->buf_phys_addr);
err_drop_frame:
			dev->stats.rx_errors++;
			mvneta_rx_error(pp, rx_desc);
			/* leave the descriptor untouched */
			continue;
		}

		if (rx_bytes <= rx_copybreak) {
			/* better copy a small frame and not unmap the DMA region */
			skb = netdev_alloc_skb_ip_align(dev, rx_bytes);
			if (unlikely(!skb))
				goto err_drop_frame_ret_pool;

			dma_sync_single_range_for_cpu(&pp->bm_priv->pdev->dev,
			                              rx_desc->buf_phys_addr,
			                              MVNETA_MH_SIZE + NET_SKB_PAD,
			                              rx_bytes,
			                              DMA_FROM_DEVICE);
			skb_put_data(skb, data + MVNETA_MH_SIZE + NET_SKB_PAD,
				     rx_bytes);

			skb->protocol = eth_type_trans(skb, dev);
			mvneta_rx_csum(pp, rx_status, skb);
			napi_gro_receive(napi, skb);

			rcvd_pkts++;
			rcvd_bytes += rx_bytes;

			/* Return the buffer to the pool */
			mvneta_bm_pool_put_bp(pp->bm_priv, bm_pool,
					      rx_desc->buf_phys_addr);

			/* leave the descriptor and buffer untouched */
			continue;
		}

		/* Refill processing */
		err = hwbm_pool_refill(&bm_pool->hwbm_pool, GFP_ATOMIC);
		if (err) {
			netdev_err(dev, "Linux processing - Can't refill\n");
			rxq->refill_err++;
			goto err_drop_frame_ret_pool;
		}

		frag_size = bm_pool->hwbm_pool.frag_size;

		skb = build_skb(data, frag_size > PAGE_SIZE ? 0 : frag_size);

		/* After refill old buffer has to be unmapped regardless
		 * the skb is successfully built or not.
		 */
		dma_unmap_single(&pp->bm_priv->pdev->dev, phys_addr,
				 bm_pool->buf_size, DMA_FROM_DEVICE);
		if (!skb)
			goto err_drop_frame;

		rcvd_pkts++;
		rcvd_bytes += rx_bytes;

		/* Linux processing */
		skb_reserve(skb, MVNETA_MH_SIZE + NET_SKB_PAD);
		skb_put(skb, rx_bytes);

		skb->protocol = eth_type_trans(skb, dev);

		mvneta_rx_csum(pp, rx_status, skb);

		napi_gro_receive(napi, skb);
	}

	if (rcvd_pkts) {
		struct mvneta_pcpu_stats *stats = this_cpu_ptr(pp->stats);

		u64_stats_update_begin(&stats->syncp);
		stats->rx_packets += rcvd_pkts;
		stats->rx_bytes   += rcvd_bytes;
		u64_stats_update_end(&stats->syncp);
	}

	/* Update rxq management counters */
	mvneta_rxq_desc_num_update(pp, rxq, rx_done, rx_done);

	return rx_done;
}