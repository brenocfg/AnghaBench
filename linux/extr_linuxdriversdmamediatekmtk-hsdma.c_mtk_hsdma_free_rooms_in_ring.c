#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  size_t u16 ;
struct mtk_hsdma_vdesc {int /*<<< orphan*/  residue; } ;
struct TYPE_10__ {int /*<<< orphan*/  lock; } ;
struct mtk_hsdma_vchan {int issue_synchronize; TYPE_4__ vc; int /*<<< orphan*/  issue_completion; int /*<<< orphan*/  desc_hw_processing; } ;
struct mtk_hsdma_pdesc {int /*<<< orphan*/  desc2; int /*<<< orphan*/  desc1; } ;
struct TYPE_9__ {size_t cur_rptr; struct mtk_hsdma_cb* cb; struct mtk_hsdma_pdesc* rxd; } ;
struct mtk_hsdma_pchan {int /*<<< orphan*/  nr_free; TYPE_3__ ring; } ;
struct mtk_hsdma_device {int dma_requests; struct mtk_hsdma_vchan* vc; TYPE_1__* soc; struct mtk_hsdma_pchan* pc; } ;
struct mtk_hsdma_cb {TYPE_5__* vd; scalar_t__ flag; } ;
typedef  int __le32 ;
struct TYPE_8__ {int /*<<< orphan*/  chan; } ;
struct TYPE_11__ {int /*<<< orphan*/  node; TYPE_2__ tx; } ;
struct TYPE_7__ {int ddone; } ;

/* Variables and functions */
 scalar_t__ IS_MTK_HSDMA_VDESC_FINISHED (scalar_t__) ; 
 int MTK_DMA_SIZE ; 
 scalar_t__ MTK_HSDMA_DESC_PLEN_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTK_HSDMA_INT_ENABLE ; 
 int MTK_HSDMA_INT_RXDONE ; 
 int /*<<< orphan*/  MTK_HSDMA_INT_STATUS ; 
 size_t MTK_HSDMA_NEXT_DESP_IDX (size_t,int) ; 
 int /*<<< orphan*/  MTK_HSDMA_RX_CPU ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hsdma2dev (struct mtk_hsdma_device*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int mtk_dma_read (struct mtk_hsdma_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_dma_set (struct mtk_hsdma_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtk_dma_write (struct mtk_hsdma_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtk_hsdma_issue_vchan_pending (struct mtk_hsdma_device*,struct mtk_hsdma_vchan*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct mtk_hsdma_vchan* to_hsdma_vchan (int /*<<< orphan*/ ) ; 
 struct mtk_hsdma_vdesc* to_hsdma_vdesc (TYPE_5__*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vchan_cookie_complete (TYPE_5__*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void mtk_hsdma_free_rooms_in_ring(struct mtk_hsdma_device *hsdma)
{
	struct mtk_hsdma_vchan *hvc;
	struct mtk_hsdma_pdesc *rxd;
	struct mtk_hsdma_vdesc *hvd;
	struct mtk_hsdma_pchan *pc;
	struct mtk_hsdma_cb *cb;
	int i = MTK_DMA_SIZE;
	__le32 desc2;
	u32 status;
	u16 next;

	/* Read IRQ status */
	status = mtk_dma_read(hsdma, MTK_HSDMA_INT_STATUS);
	if (unlikely(!(status & MTK_HSDMA_INT_RXDONE)))
		goto rx_done;

	pc = hsdma->pc;

	/*
	 * Using a fail-safe loop with iterations of up to MTK_DMA_SIZE to
	 * reclaim these finished descriptors: The most number of PDs the ISR
	 * can handle at one time shouldn't be more than MTK_DMA_SIZE so we
	 * take it as limited count instead of just using a dangerous infinite
	 * poll.
	 */
	while (i--) {
		next = MTK_HSDMA_NEXT_DESP_IDX(pc->ring.cur_rptr,
					       MTK_DMA_SIZE);
		rxd = &pc->ring.rxd[next];

		/*
		 * If MTK_HSDMA_DESC_DDONE is no specified, that means data
		 * moving for the PD is still under going.
		 */
		desc2 = READ_ONCE(rxd->desc2);
		if (!(desc2 & hsdma->soc->ddone))
			break;

		cb = &pc->ring.cb[next];
		if (unlikely(!cb->vd)) {
			dev_err(hsdma2dev(hsdma), "cb->vd cannot be null\n");
			break;
		}

		/* Update residue of VD the associated PD belonged to */
		hvd = to_hsdma_vdesc(cb->vd);
		hvd->residue -= MTK_HSDMA_DESC_PLEN_GET(rxd->desc2);

		/* Complete VD until the relevant last PD is finished */
		if (IS_MTK_HSDMA_VDESC_FINISHED(cb->flag)) {
			hvc = to_hsdma_vchan(cb->vd->tx.chan);

			spin_lock(&hvc->vc.lock);

			/* Remove VD from list desc_hw_processing */
			list_del(&cb->vd->node);

			/* Add VD into list desc_completed */
			vchan_cookie_complete(cb->vd);

			if (hvc->issue_synchronize &&
			    list_empty(&hvc->desc_hw_processing)) {
				complete(&hvc->issue_completion);
				hvc->issue_synchronize = false;
			}
			spin_unlock(&hvc->vc.lock);

			cb->flag = 0;
		}

		cb->vd = 0;

		/*
		 * Recycle the RXD with the helper WRITE_ONCE that can ensure
		 * data written into RAM would really happens.
		 */
		WRITE_ONCE(rxd->desc1, 0);
		WRITE_ONCE(rxd->desc2, 0);
		pc->ring.cur_rptr = next;

		/* Release rooms */
		atomic_inc(&pc->nr_free);
	}

	/* Ensure all changes indeed done before we're going on */
	wmb();

	/* Update CPU pointer for those completed PDs */
	mtk_dma_write(hsdma, MTK_HSDMA_RX_CPU, pc->ring.cur_rptr);

	/*
	 * Acking the pending IRQ allows hardware no longer to keep the used
	 * IRQ line in certain trigger state when software has completed all
	 * the finished physical descriptors.
	 */
	if (atomic_read(&pc->nr_free) >= MTK_DMA_SIZE - 1)
		mtk_dma_write(hsdma, MTK_HSDMA_INT_STATUS, status);

	/* ASAP handles pending VDs in all VCs after freeing some rooms */
	for (i = 0; i < hsdma->dma_requests; i++) {
		hvc = &hsdma->vc[i];
		spin_lock(&hvc->vc.lock);
		mtk_hsdma_issue_vchan_pending(hsdma, hvc);
		spin_unlock(&hvc->vc.lock);
	}

rx_done:
	/* All completed PDs are cleaned up, so enable interrupt again */
	mtk_dma_set(hsdma, MTK_HSDMA_INT_ENABLE, MTK_HSDMA_INT_RXDONE);
}