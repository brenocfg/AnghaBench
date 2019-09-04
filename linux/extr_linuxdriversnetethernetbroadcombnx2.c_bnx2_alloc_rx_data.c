#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  size_t u16 ;
struct bnx2_sw_bd {int /*<<< orphan*/ * data; } ;
struct bnx2_rx_ring_info {int /*<<< orphan*/  rx_prod_bseq; struct bnx2_rx_bd** rx_desc_ring; struct bnx2_sw_bd* rx_buf_ring; } ;
struct bnx2_rx_bd {int rx_bd_haddr_hi; int rx_bd_haddr_lo; } ;
struct bnx2 {int /*<<< orphan*/  rx_buf_use_size; TYPE_1__* pdev; int /*<<< orphan*/  rx_buf_size; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t BNX2_RX_IDX (size_t) ; 
 size_t BNX2_RX_RING (size_t) ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  dma_unmap_addr_set (struct bnx2_sw_bd*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  get_l2_fhdr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
bnx2_alloc_rx_data(struct bnx2 *bp, struct bnx2_rx_ring_info *rxr, u16 index, gfp_t gfp)
{
	u8 *data;
	struct bnx2_sw_bd *rx_buf = &rxr->rx_buf_ring[index];
	dma_addr_t mapping;
	struct bnx2_rx_bd *rxbd =
		&rxr->rx_desc_ring[BNX2_RX_RING(index)][BNX2_RX_IDX(index)];

	data = kmalloc(bp->rx_buf_size, gfp);
	if (!data)
		return -ENOMEM;

	mapping = dma_map_single(&bp->pdev->dev,
				 get_l2_fhdr(data),
				 bp->rx_buf_use_size,
				 PCI_DMA_FROMDEVICE);
	if (dma_mapping_error(&bp->pdev->dev, mapping)) {
		kfree(data);
		return -EIO;
	}

	rx_buf->data = data;
	dma_unmap_addr_set(rx_buf, mapping, mapping);

	rxbd->rx_bd_haddr_hi = (u64) mapping >> 32;
	rxbd->rx_bd_haddr_lo = (u64) mapping & 0xffffffff;

	rxr->rx_prod_bseq += bp->rx_buf_use_size;

	return 0;
}