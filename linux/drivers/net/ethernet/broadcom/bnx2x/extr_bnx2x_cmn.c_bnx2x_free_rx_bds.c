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
struct sw_rx_bd {int /*<<< orphan*/ * data; } ;
struct bnx2x_fastpath {int /*<<< orphan*/  rx_buf_size; struct sw_rx_bd* rx_buf_ring; struct bnx2x* bp; } ;
struct bnx2x {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int NUM_RX_BD ; 
 int /*<<< orphan*/  bnx2x_frag_free (struct bnx2x_fastpath*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_addr (struct sw_rx_bd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapping ; 

__attribute__((used)) static void bnx2x_free_rx_bds(struct bnx2x_fastpath *fp)
{
	struct bnx2x *bp = fp->bp;
	int i;

	/* ring wasn't allocated */
	if (fp->rx_buf_ring == NULL)
		return;

	for (i = 0; i < NUM_RX_BD; i++) {
		struct sw_rx_bd *rx_buf = &fp->rx_buf_ring[i];
		u8 *data = rx_buf->data;

		if (data == NULL)
			continue;
		dma_unmap_single(&bp->pdev->dev,
				 dma_unmap_addr(rx_buf, mapping),
				 fp->rx_buf_size, DMA_FROM_DEVICE);

		rx_buf->data = NULL;
		bnx2x_frag_free(fp, data);
	}
}