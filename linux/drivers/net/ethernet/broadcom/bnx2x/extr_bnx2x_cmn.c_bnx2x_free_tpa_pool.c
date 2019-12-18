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
struct bnx2x_fastpath {int /*<<< orphan*/  rx_buf_size; struct bnx2x_agg_info* tpa_info; } ;
struct bnx2x_agg_info {scalar_t__ tpa_state; struct sw_rx_bd first_buf; } ;
struct bnx2x {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ BNX2X_TPA_START ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  NETIF_MSG_IFDOWN ; 
 int /*<<< orphan*/  bnx2x_frag_free (struct bnx2x_fastpath*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_addr (struct sw_rx_bd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapping ; 

__attribute__((used)) static void bnx2x_free_tpa_pool(struct bnx2x *bp,
				struct bnx2x_fastpath *fp, int last)
{
	int i;

	for (i = 0; i < last; i++) {
		struct bnx2x_agg_info *tpa_info = &fp->tpa_info[i];
		struct sw_rx_bd *first_buf = &tpa_info->first_buf;
		u8 *data = first_buf->data;

		if (data == NULL) {
			DP(NETIF_MSG_IFDOWN, "tpa bin %d empty on free\n", i);
			continue;
		}
		if (tpa_info->tpa_state == BNX2X_TPA_START)
			dma_unmap_single(&bp->pdev->dev,
					 dma_unmap_addr(first_buf, mapping),
					 fp->rx_buf_size, DMA_FROM_DEVICE);
		bnx2x_frag_free(fp, data);
		first_buf->data = NULL;
	}
}