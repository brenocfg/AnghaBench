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
typedef  size_t u16 ;
struct bnx2_sw_bd {int /*<<< orphan*/ * data; } ;
struct bnx2_rx_ring_info {struct bnx2_rx_bd** rx_desc_ring; int /*<<< orphan*/  rx_prod_bseq; struct bnx2_sw_bd* rx_buf_ring; } ;
struct bnx2_rx_bd {int /*<<< orphan*/  rx_bd_haddr_lo; int /*<<< orphan*/  rx_bd_haddr_hi; } ;
struct bnx2 {scalar_t__ rx_buf_use_size; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ BNX2_RX_COPY_THRESH ; 
 size_t BNX2_RX_IDX (size_t) ; 
 scalar_t__ BNX2_RX_OFFSET ; 
 size_t BNX2_RX_RING (size_t) ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_addr (struct bnx2_sw_bd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_addr_set (struct bnx2_sw_bd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapping ; 

__attribute__((used)) static inline void
bnx2_reuse_rx_data(struct bnx2 *bp, struct bnx2_rx_ring_info *rxr,
		   u8 *data, u16 cons, u16 prod)
{
	struct bnx2_sw_bd *cons_rx_buf, *prod_rx_buf;
	struct bnx2_rx_bd *cons_bd, *prod_bd;

	cons_rx_buf = &rxr->rx_buf_ring[cons];
	prod_rx_buf = &rxr->rx_buf_ring[prod];

	dma_sync_single_for_device(&bp->pdev->dev,
		dma_unmap_addr(cons_rx_buf, mapping),
		BNX2_RX_OFFSET + BNX2_RX_COPY_THRESH, PCI_DMA_FROMDEVICE);

	rxr->rx_prod_bseq += bp->rx_buf_use_size;

	prod_rx_buf->data = data;

	if (cons == prod)
		return;

	dma_unmap_addr_set(prod_rx_buf, mapping,
			dma_unmap_addr(cons_rx_buf, mapping));

	cons_bd = &rxr->rx_desc_ring[BNX2_RX_RING(cons)][BNX2_RX_IDX(cons)];
	prod_bd = &rxr->rx_desc_ring[BNX2_RX_RING(prod)][BNX2_RX_IDX(prod)];
	prod_bd->rx_bd_haddr_hi = cons_bd->rx_bd_haddr_hi;
	prod_bd->rx_bd_haddr_lo = cons_bd->rx_bd_haddr_lo;
}