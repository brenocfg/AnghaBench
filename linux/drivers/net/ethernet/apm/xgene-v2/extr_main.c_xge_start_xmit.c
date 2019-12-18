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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct xge_raw_desc {void* m0; void* m1; } ;
struct xge_pdata {struct xge_desc_ring* tx_ring; TYPE_1__* pdev; } ;
struct xge_desc_ring {size_t tail; TYPE_2__* pkt_info; struct xge_raw_desc* raw_desc; } ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct net_device {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {void* pkt_buf; int /*<<< orphan*/  dma_addr; struct sk_buff* skb; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMATXCTRL ; 
 int /*<<< orphan*/  E ; 
 int /*<<< orphan*/  GET_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  NEXT_DESC_ADDRH ; 
 int /*<<< orphan*/  NEXT_DESC_ADDRL ; 
 int /*<<< orphan*/  PKT_ADDRH ; 
 int /*<<< orphan*/  PKT_ADDRL ; 
 int /*<<< orphan*/  PKT_SIZE ; 
 int SET_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int XGENE_ENET_NUM_DESC ; 
 int /*<<< orphan*/  XGENE_ENET_STD_MTU ; 
 void* cpu_to_le64 (int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 void* dma_alloc_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_wmb () ; 
 int /*<<< orphan*/  is_tx_slot_available (struct xge_raw_desc*) ; 
 int /*<<< orphan*/  le64_to_cpu (void*) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xge_pdata* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  skb_headlen (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_tx_timestamp (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xge_wr_csr (struct xge_pdata*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static netdev_tx_t xge_start_xmit(struct sk_buff *skb, struct net_device *ndev)
{
	struct xge_pdata *pdata = netdev_priv(ndev);
	struct device *dev = &pdata->pdev->dev;
	struct xge_desc_ring *tx_ring;
	struct xge_raw_desc *raw_desc;
	static dma_addr_t dma_addr;
	u64 addr_lo, addr_hi;
	void *pkt_buf;
	u8 tail;
	u16 len;

	tx_ring = pdata->tx_ring;
	tail = tx_ring->tail;
	len = skb_headlen(skb);
	raw_desc = &tx_ring->raw_desc[tail];

	if (!is_tx_slot_available(raw_desc)) {
		netif_stop_queue(ndev);
		return NETDEV_TX_BUSY;
	}

	/* Packet buffers should be 64B aligned */
	pkt_buf = dma_alloc_coherent(dev, XGENE_ENET_STD_MTU, &dma_addr,
				     GFP_ATOMIC);
	if (unlikely(!pkt_buf)) {
		dev_kfree_skb_any(skb);
		return NETDEV_TX_OK;
	}
	memcpy(pkt_buf, skb->data, len);

	addr_hi = GET_BITS(NEXT_DESC_ADDRH, le64_to_cpu(raw_desc->m1));
	addr_lo = GET_BITS(NEXT_DESC_ADDRL, le64_to_cpu(raw_desc->m1));
	raw_desc->m1 = cpu_to_le64(SET_BITS(NEXT_DESC_ADDRL, addr_lo) |
				   SET_BITS(NEXT_DESC_ADDRH, addr_hi) |
				   SET_BITS(PKT_ADDRH,
					    upper_32_bits(dma_addr)));

	tx_ring->pkt_info[tail].skb = skb;
	tx_ring->pkt_info[tail].dma_addr = dma_addr;
	tx_ring->pkt_info[tail].pkt_buf = pkt_buf;

	dma_wmb();

	raw_desc->m0 = cpu_to_le64(SET_BITS(PKT_ADDRL, dma_addr) |
				   SET_BITS(PKT_SIZE, len) |
				   SET_BITS(E, 0));
	skb_tx_timestamp(skb);
	xge_wr_csr(pdata, DMATXCTRL, 1);

	tx_ring->tail = (tail + 1) & (XGENE_ENET_NUM_DESC - 1);

	return NETDEV_TX_OK;
}