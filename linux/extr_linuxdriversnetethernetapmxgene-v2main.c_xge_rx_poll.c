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
typedef  void* u16 ;
struct xge_raw_desc {int /*<<< orphan*/  m2; int /*<<< orphan*/  m0; } ;
struct TYPE_6__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_errors; } ;
struct xge_pdata {int /*<<< orphan*/  napi; TYPE_3__ stats; struct xge_desc_ring* rx_ring; TYPE_1__* pdev; } ;
struct xge_desc_ring {size_t head; TYPE_2__* pkt_info; struct xge_raw_desc* raw_desc; } ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct net_device {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_5__ {int /*<<< orphan*/  dma_addr; struct sk_buff* skb; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  D ; 
 int /*<<< orphan*/  DMARXCTRL ; 
 int /*<<< orphan*/  DMARXSTATUS ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  E ; 
 void* GET_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PKT_SIZE ; 
 int /*<<< orphan*/  RXPKTCOUNT ; 
 int XGENE_ENET_NUM_DESC ; 
 int /*<<< orphan*/  XGENE_ENET_STD_MTU ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_rmb () ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 struct xge_pdata* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,void*) ; 
 scalar_t__ unlikely (size_t) ; 
 int /*<<< orphan*/  xge_rd_csr (struct xge_pdata*,int /*<<< orphan*/ ) ; 
 int xge_refill_buffers (struct net_device*,int) ; 
 int /*<<< orphan*/  xge_wr_csr (struct xge_pdata*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int xge_rx_poll(struct net_device *ndev, unsigned int budget)
{
	struct xge_pdata *pdata = netdev_priv(ndev);
	struct device *dev = &pdata->pdev->dev;
	struct xge_desc_ring *rx_ring;
	struct xge_raw_desc *raw_desc;
	struct sk_buff *skb;
	dma_addr_t dma_addr;
	int processed = 0;
	u8 head, rx_error;
	int i, ret;
	u32 data;
	u16 len;

	rx_ring = pdata->rx_ring;
	head = rx_ring->head;

	data = xge_rd_csr(pdata, DMARXSTATUS);
	if (!GET_BITS(RXPKTCOUNT, data))
		return 0;

	for (i = 0; i < budget; i++) {
		raw_desc = &rx_ring->raw_desc[head];

		if (GET_BITS(E, le64_to_cpu(raw_desc->m0)))
			break;

		dma_rmb();

		skb = rx_ring->pkt_info[head].skb;
		rx_ring->pkt_info[head].skb = NULL;
		dma_addr = rx_ring->pkt_info[head].dma_addr;
		len = GET_BITS(PKT_SIZE, le64_to_cpu(raw_desc->m0));
		dma_unmap_single(dev, dma_addr, XGENE_ENET_STD_MTU,
				 DMA_FROM_DEVICE);

		rx_error = GET_BITS(D, le64_to_cpu(raw_desc->m2));
		if (unlikely(rx_error)) {
			pdata->stats.rx_errors++;
			dev_kfree_skb_any(skb);
			goto out;
		}

		skb_put(skb, len);
		skb->protocol = eth_type_trans(skb, ndev);

		pdata->stats.rx_packets++;
		pdata->stats.rx_bytes += len;
		napi_gro_receive(&pdata->napi, skb);
out:
		ret = xge_refill_buffers(ndev, 1);
		xge_wr_csr(pdata, DMARXSTATUS, 1);
		xge_wr_csr(pdata, DMARXCTRL, 1);

		if (ret)
			break;

		head = (head + 1) & (XGENE_ENET_NUM_DESC - 1);
		processed++;
	}

	rx_ring->head = head;

	return processed;
}