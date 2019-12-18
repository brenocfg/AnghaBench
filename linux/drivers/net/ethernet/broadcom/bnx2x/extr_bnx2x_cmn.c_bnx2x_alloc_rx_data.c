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
struct sw_rx_bd {int /*<<< orphan*/ * data; } ;
struct eth_rx_bd {void* addr_lo; void* addr_hi; } ;
struct bnx2x_fastpath {int /*<<< orphan*/  rx_buf_size; struct eth_rx_bd* rx_desc_ring; struct sw_rx_bd* rx_buf_ring; } ;
struct bnx2x {TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 int NET_SKB_PAD ; 
 int /*<<< orphan*/  U64_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U64_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bnx2x_frag_alloc (struct bnx2x_fastpath*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_frag_free (struct bnx2x_fastpath*,int /*<<< orphan*/ *) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_addr_set (struct sw_rx_bd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnx2x_alloc_rx_data(struct bnx2x *bp, struct bnx2x_fastpath *fp,
			       u16 index, gfp_t gfp_mask)
{
	u8 *data;
	struct sw_rx_bd *rx_buf = &fp->rx_buf_ring[index];
	struct eth_rx_bd *rx_bd = &fp->rx_desc_ring[index];
	dma_addr_t mapping;

	data = bnx2x_frag_alloc(fp, gfp_mask);
	if (unlikely(data == NULL))
		return -ENOMEM;

	mapping = dma_map_single(&bp->pdev->dev, data + NET_SKB_PAD,
				 fp->rx_buf_size,
				 DMA_FROM_DEVICE);
	if (unlikely(dma_mapping_error(&bp->pdev->dev, mapping))) {
		bnx2x_frag_free(fp, data);
		BNX2X_ERR("Can't map rx data\n");
		return -ENOMEM;
	}

	rx_buf->data = data;
	dma_unmap_addr_set(rx_buf, mapping, mapping);

	rx_bd->addr_hi = cpu_to_le32(U64_HI(mapping));
	rx_bd->addr_lo = cpu_to_le32(U64_LO(mapping));

	return 0;
}