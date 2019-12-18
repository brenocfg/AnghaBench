#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct xge_raw_desc {int /*<<< orphan*/  m0; } ;
struct TYPE_6__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct xge_pdata {TYPE_3__ stats; struct xge_desc_ring* tx_ring; TYPE_1__* pdev; } ;
struct xge_desc_ring {size_t head; TYPE_2__* pkt_info; struct xge_raw_desc* raw_desc; } ;
struct sk_buff {scalar_t__ len; } ;
struct net_device {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_5__ {void* pkt_buf; int /*<<< orphan*/  dma_addr; struct sk_buff* skb; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMATXSTATUS ; 
 int /*<<< orphan*/  E ; 
 int /*<<< orphan*/  GET_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PKT_SIZE ; 
 int SET_BITS (int /*<<< orphan*/ ,int) ; 
 int SLOT_EMPTY ; 
 int /*<<< orphan*/  TXPKTCOUNT ; 
 int XGENE_ENET_NUM_DESC ; 
 int /*<<< orphan*/  XGENE_ENET_STD_MTU ; 
 int /*<<< orphan*/  cpu_to_le64 (int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_rmb () ; 
 int /*<<< orphan*/  is_tx_hw_done (struct xge_raw_desc*) ; 
 struct xge_pdata* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  xge_rd_csr (struct xge_pdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xge_wr_csr (struct xge_pdata*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xge_txc_poll(struct net_device *ndev)
{
	struct xge_pdata *pdata = netdev_priv(ndev);
	struct device *dev = &pdata->pdev->dev;
	struct xge_desc_ring *tx_ring;
	struct xge_raw_desc *raw_desc;
	dma_addr_t dma_addr;
	struct sk_buff *skb;
	void *pkt_buf;
	u32 data;
	u8 head;

	tx_ring = pdata->tx_ring;
	head = tx_ring->head;

	data = xge_rd_csr(pdata, DMATXSTATUS);
	if (!GET_BITS(TXPKTCOUNT, data))
		return;

	while (1) {
		raw_desc = &tx_ring->raw_desc[head];

		if (!is_tx_hw_done(raw_desc))
			break;

		dma_rmb();

		skb = tx_ring->pkt_info[head].skb;
		dma_addr = tx_ring->pkt_info[head].dma_addr;
		pkt_buf = tx_ring->pkt_info[head].pkt_buf;
		pdata->stats.tx_packets++;
		pdata->stats.tx_bytes += skb->len;
		dma_free_coherent(dev, XGENE_ENET_STD_MTU, pkt_buf, dma_addr);
		dev_kfree_skb_any(skb);

		/* clear pktstart address and pktsize */
		raw_desc->m0 = cpu_to_le64(SET_BITS(E, 1) |
					   SET_BITS(PKT_SIZE, SLOT_EMPTY));
		xge_wr_csr(pdata, DMATXSTATUS, 1);

		head = (head + 1) & (XGENE_ENET_NUM_DESC - 1);
	}

	if (netif_queue_stopped(ndev))
		netif_wake_queue(ndev);

	tx_ring->head = head;
}