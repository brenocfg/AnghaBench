#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  size_t u32 ;
struct rx_ring {size_t sbq_clean_idx; int sbq_free_cnt; size_t sbq_len; int sbq_prod_idx; int /*<<< orphan*/  sbq_prod_idx_db_reg; int /*<<< orphan*/  sbq_buf_size; struct bq_desc* sbq; } ;
struct ql_adapter {int /*<<< orphan*/  ndev; int /*<<< orphan*/  pdev; } ;
struct TYPE_5__ {TYPE_2__* skb; } ;
struct bq_desc {size_t index; int /*<<< orphan*/ * addr; TYPE_1__ p; } ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  QLGE_SB_PAD ; 
 int /*<<< orphan*/  SMALL_BUFFER_SIZE ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (TYPE_2__*) ; 
 int /*<<< orphan*/  dma_unmap_addr_set (struct bq_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len_set (struct bq_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  mapaddr ; 
 int /*<<< orphan*/  maplen ; 
 TYPE_2__* netdev_alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_printk (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 
 scalar_t__ pci_dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_write_db_reg (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rx_status ; 
 int /*<<< orphan*/  skb_reserve (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ql_update_sbq(struct ql_adapter *qdev, struct rx_ring *rx_ring)
{
	u32 clean_idx = rx_ring->sbq_clean_idx;
	u32 start_idx = clean_idx;
	struct bq_desc *sbq_desc;
	u64 map;
	int i;

	while (rx_ring->sbq_free_cnt > 16) {
		for (i = (rx_ring->sbq_clean_idx % 16); i < 16; i++) {
			sbq_desc = &rx_ring->sbq[clean_idx];
			netif_printk(qdev, rx_status, KERN_DEBUG, qdev->ndev,
				     "sbq: try cleaning clean_idx = %d.\n",
				     clean_idx);
			if (sbq_desc->p.skb == NULL) {
				netif_printk(qdev, rx_status, KERN_DEBUG,
					     qdev->ndev,
					     "sbq: getting new skb for index %d.\n",
					     sbq_desc->index);
				sbq_desc->p.skb =
				    netdev_alloc_skb(qdev->ndev,
						     SMALL_BUFFER_SIZE);
				if (sbq_desc->p.skb == NULL) {
					rx_ring->sbq_clean_idx = clean_idx;
					return;
				}
				skb_reserve(sbq_desc->p.skb, QLGE_SB_PAD);
				map = pci_map_single(qdev->pdev,
						     sbq_desc->p.skb->data,
						     rx_ring->sbq_buf_size,
						     PCI_DMA_FROMDEVICE);
				if (pci_dma_mapping_error(qdev->pdev, map)) {
					netif_err(qdev, ifup, qdev->ndev,
						  "PCI mapping failed.\n");
					rx_ring->sbq_clean_idx = clean_idx;
					dev_kfree_skb_any(sbq_desc->p.skb);
					sbq_desc->p.skb = NULL;
					return;
				}
				dma_unmap_addr_set(sbq_desc, mapaddr, map);
				dma_unmap_len_set(sbq_desc, maplen,
						  rx_ring->sbq_buf_size);
				*sbq_desc->addr = cpu_to_le64(map);
			}

			clean_idx++;
			if (clean_idx == rx_ring->sbq_len)
				clean_idx = 0;
		}
		rx_ring->sbq_clean_idx = clean_idx;
		rx_ring->sbq_prod_idx += 16;
		if (rx_ring->sbq_prod_idx == rx_ring->sbq_len)
			rx_ring->sbq_prod_idx = 0;
		rx_ring->sbq_free_cnt -= 16;
	}

	if (start_idx != clean_idx) {
		netif_printk(qdev, rx_status, KERN_DEBUG, qdev->ndev,
			     "sbq: updating prod idx = %d.\n",
			     rx_ring->sbq_prod_idx);
		ql_write_db_reg(rx_ring->sbq_prod_idx,
				rx_ring->sbq_prod_idx_db_reg);
	}
}