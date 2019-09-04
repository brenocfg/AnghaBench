#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ql_rcv_buf_cb {struct ql_rcv_buf_cb* next; void* buf_phy_addr_high; void* buf_phy_addr_low; TYPE_1__* skb; } ;
struct ql3_adapter {int /*<<< orphan*/  lrg_buf_skb_check; scalar_t__ lrg_buffer_len; int /*<<< orphan*/  ndev; int /*<<< orphan*/  pdev; struct ql_rcv_buf_cb* lrg_buf_free_head; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  LS_64BITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MS_64BITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 scalar_t__ QL_HEADER_SPACE ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb (TYPE_1__*) ; 
 int /*<<< orphan*/  dma_unmap_addr_set (struct ql_rcv_buf_cb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len_set (struct ql_rcv_buf_cb*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mapaddr ; 
 int /*<<< orphan*/  maplen ; 
 TYPE_1__* netdev_alloc_skb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  netdev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int pci_dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (TYPE_1__*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ql_populate_free_queue(struct ql3_adapter *qdev)
{
	struct ql_rcv_buf_cb *lrg_buf_cb = qdev->lrg_buf_free_head;
	dma_addr_t map;
	int err;

	while (lrg_buf_cb) {
		if (!lrg_buf_cb->skb) {
			lrg_buf_cb->skb =
				netdev_alloc_skb(qdev->ndev,
						 qdev->lrg_buffer_len);
			if (unlikely(!lrg_buf_cb->skb)) {
				netdev_printk(KERN_DEBUG, qdev->ndev,
					      "Failed netdev_alloc_skb()\n");
				break;
			} else {
				/*
				 * We save some space to copy the ethhdr from
				 * first buffer
				 */
				skb_reserve(lrg_buf_cb->skb, QL_HEADER_SPACE);
				map = pci_map_single(qdev->pdev,
						     lrg_buf_cb->skb->data,
						     qdev->lrg_buffer_len -
						     QL_HEADER_SPACE,
						     PCI_DMA_FROMDEVICE);

				err = pci_dma_mapping_error(qdev->pdev, map);
				if (err) {
					netdev_err(qdev->ndev,
						   "PCI mapping failed with error: %d\n",
						   err);
					dev_kfree_skb(lrg_buf_cb->skb);
					lrg_buf_cb->skb = NULL;
					break;
				}


				lrg_buf_cb->buf_phy_addr_low =
					cpu_to_le32(LS_64BITS(map));
				lrg_buf_cb->buf_phy_addr_high =
					cpu_to_le32(MS_64BITS(map));
				dma_unmap_addr_set(lrg_buf_cb, mapaddr, map);
				dma_unmap_len_set(lrg_buf_cb, maplen,
						  qdev->lrg_buffer_len -
						  QL_HEADER_SPACE);
				--qdev->lrg_buf_skb_check;
				if (!qdev->lrg_buf_skb_check)
					return 1;
			}
		}
		lrg_buf_cb = lrg_buf_cb->next;
	}
	return 0;
}