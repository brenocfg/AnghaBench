#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  addr; } ;
union Vmxnet3_GenericDesc {int /*<<< orphan*/ * dword; TYPE_3__ rxd; } ;
typedef  size_t u32 ;
struct TYPE_7__ {int /*<<< orphan*/  rx_buf_alloc_failure; } ;
struct vmxnet3_rx_queue {TYPE_2__ stats; struct vmxnet3_cmd_ring* rx_ring; struct vmxnet3_rx_buf_info** buf_info; } ;
struct vmxnet3_rx_buf_info {scalar_t__ buf_type; int len; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/ * page; TYPE_4__* skb; } ;
struct vmxnet3_cmd_ring {int next2fill; int gen; scalar_t__ next2comp; union Vmxnet3_GenericDesc* base; } ;
struct vmxnet3_adapter {int /*<<< orphan*/  netdev; TYPE_1__* pdev; } ;
struct TYPE_9__ {int /*<<< orphan*/  data; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 size_t VMXNET3_RXD_BTYPE_BODY ; 
 size_t VMXNET3_RXD_BTYPE_HEAD ; 
 size_t VMXNET3_RXD_BTYPE_SHIFT ; 
 int VMXNET3_RXD_GEN_SHIFT ; 
 scalar_t__ VMXNET3_RX_BUF_PAGE ; 
 scalar_t__ VMXNET3_RX_BUF_SKB ; 
 TYPE_4__* __netdev_alloc_skb_ip_align (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (TYPE_4__*) ; 
 int /*<<< orphan*/  dma_map_page (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int,int,scalar_t__) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmxnet3_cmd_ring_adv_next2fill (struct vmxnet3_cmd_ring*) ; 

__attribute__((used)) static int
vmxnet3_rq_alloc_rx_buf(struct vmxnet3_rx_queue *rq, u32 ring_idx,
			int num_to_alloc, struct vmxnet3_adapter *adapter)
{
	int num_allocated = 0;
	struct vmxnet3_rx_buf_info *rbi_base = rq->buf_info[ring_idx];
	struct vmxnet3_cmd_ring *ring = &rq->rx_ring[ring_idx];
	u32 val;

	while (num_allocated <= num_to_alloc) {
		struct vmxnet3_rx_buf_info *rbi;
		union Vmxnet3_GenericDesc *gd;

		rbi = rbi_base + ring->next2fill;
		gd = ring->base + ring->next2fill;

		if (rbi->buf_type == VMXNET3_RX_BUF_SKB) {
			if (rbi->skb == NULL) {
				rbi->skb = __netdev_alloc_skb_ip_align(adapter->netdev,
								       rbi->len,
								       GFP_KERNEL);
				if (unlikely(rbi->skb == NULL)) {
					rq->stats.rx_buf_alloc_failure++;
					break;
				}

				rbi->dma_addr = dma_map_single(
						&adapter->pdev->dev,
						rbi->skb->data, rbi->len,
						PCI_DMA_FROMDEVICE);
				if (dma_mapping_error(&adapter->pdev->dev,
						      rbi->dma_addr)) {
					dev_kfree_skb_any(rbi->skb);
					rq->stats.rx_buf_alloc_failure++;
					break;
				}
			} else {
				/* rx buffer skipped by the device */
			}
			val = VMXNET3_RXD_BTYPE_HEAD << VMXNET3_RXD_BTYPE_SHIFT;
		} else {
			BUG_ON(rbi->buf_type != VMXNET3_RX_BUF_PAGE ||
			       rbi->len  != PAGE_SIZE);

			if (rbi->page == NULL) {
				rbi->page = alloc_page(GFP_ATOMIC);
				if (unlikely(rbi->page == NULL)) {
					rq->stats.rx_buf_alloc_failure++;
					break;
				}
				rbi->dma_addr = dma_map_page(
						&adapter->pdev->dev,
						rbi->page, 0, PAGE_SIZE,
						PCI_DMA_FROMDEVICE);
				if (dma_mapping_error(&adapter->pdev->dev,
						      rbi->dma_addr)) {
					put_page(rbi->page);
					rq->stats.rx_buf_alloc_failure++;
					break;
				}
			} else {
				/* rx buffers skipped by the device */
			}
			val = VMXNET3_RXD_BTYPE_BODY << VMXNET3_RXD_BTYPE_SHIFT;
		}

		gd->rxd.addr = cpu_to_le64(rbi->dma_addr);
		gd->dword[2] = cpu_to_le32((!ring->gen << VMXNET3_RXD_GEN_SHIFT)
					   | val | rbi->len);

		/* Fill the last buffer but dont mark it ready, or else the
		 * device will think that the queue is full */
		if (num_allocated == num_to_alloc)
			break;

		gd->dword[2] |= cpu_to_le32(ring->gen << VMXNET3_RXD_GEN_SHIFT);
		num_allocated++;
		vmxnet3_cmd_ring_adv_next2fill(ring);
	}

	netdev_dbg(adapter->netdev,
		"alloc_rx_buf: %d allocated, next2fill %u, next2comp %u\n",
		num_allocated, ring->next2fill, ring->next2comp);

	/* so that the device can distinguish a full ring and an empty ring */
	BUG_ON(num_allocated != 0 && ring->next2fill == ring->next2comp);

	return num_allocated;
}