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
struct status_block_msix {int /*<<< orphan*/  status_rx_quick_consumer_index; int /*<<< orphan*/  status_tx_quick_consumer_index; int /*<<< orphan*/  status_rx_quick_consumer_index0; int /*<<< orphan*/  status_tx_quick_consumer_index0; } ;
struct TYPE_3__ {struct status_block_msix* msix; struct status_block_msix* msi; } ;
struct bnx2_napi {int int_num; int /*<<< orphan*/ * hw_rx_cons_ptr; int /*<<< orphan*/ * hw_tx_cons_ptr; TYPE_1__ status_blk; } ;
struct bnx2 {int flags; int irq_nvecs; int ctx_pages; int /*<<< orphan*/ * ctx_blk; int /*<<< orphan*/ * ctx_blk_mapping; TYPE_2__* pdev; struct status_block_msix* status_blk; struct bnx2_napi* bnx2_napi; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ BNX2_CHIP (struct bnx2*) ; 
 scalar_t__ BNX2_CHIP_5709 ; 
 int BNX2_FLAG_MSIX_CAP ; 
 int BNX2_PAGE_SIZE ; 
 int BNX2_SBLK_MSIX_ALIGN_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int bnx2_alloc_rx_mem (struct bnx2*) ; 
 int bnx2_alloc_tx_mem (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_free_mem (struct bnx2*) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bnx2_alloc_mem(struct bnx2 *bp)
{
	int i, err;
	struct bnx2_napi *bnapi;

	bnapi = &bp->bnx2_napi[0];
	bnapi->status_blk.msi = bp->status_blk;
	bnapi->hw_tx_cons_ptr =
		&bnapi->status_blk.msi->status_tx_quick_consumer_index0;
	bnapi->hw_rx_cons_ptr =
		&bnapi->status_blk.msi->status_rx_quick_consumer_index0;
	if (bp->flags & BNX2_FLAG_MSIX_CAP) {
		for (i = 1; i < bp->irq_nvecs; i++) {
			struct status_block_msix *sblk;

			bnapi = &bp->bnx2_napi[i];

			sblk = (bp->status_blk + BNX2_SBLK_MSIX_ALIGN_SIZE * i);
			bnapi->status_blk.msix = sblk;
			bnapi->hw_tx_cons_ptr =
				&sblk->status_tx_quick_consumer_index;
			bnapi->hw_rx_cons_ptr =
				&sblk->status_rx_quick_consumer_index;
			bnapi->int_num = i << 24;
		}
	}

	if (BNX2_CHIP(bp) == BNX2_CHIP_5709) {
		bp->ctx_pages = 0x2000 / BNX2_PAGE_SIZE;
		if (bp->ctx_pages == 0)
			bp->ctx_pages = 1;
		for (i = 0; i < bp->ctx_pages; i++) {
			bp->ctx_blk[i] = dma_alloc_coherent(&bp->pdev->dev,
						BNX2_PAGE_SIZE,
						&bp->ctx_blk_mapping[i],
						GFP_KERNEL);
			if (!bp->ctx_blk[i])
				goto alloc_mem_err;
		}
	}

	err = bnx2_alloc_rx_mem(bp);
	if (err)
		goto alloc_mem_err;

	err = bnx2_alloc_tx_mem(bp);
	if (err)
		goto alloc_mem_err;

	return 0;

alloc_mem_err:
	bnx2_free_mem(bp);
	return -ENOMEM;
}