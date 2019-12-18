#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  void* u32 ;
struct TYPE_6__ {int /*<<< orphan*/  msb; int /*<<< orphan*/  lsb; } ;
struct TYPE_8__ {void* kv_qpt_ptr; int page_count; void* page_size; TYPE_1__ hw_qpt_ptr; } ;
struct TYPE_9__ {TYPE_3__ qpt; TYPE_2__* ccb; } ;
struct bna_rxp {TYPE_4__ cq; } ;
struct TYPE_10__ {int /*<<< orphan*/  msb; int /*<<< orphan*/  lsb; } ;
struct bna_mem_descr {void* kva; TYPE_5__ dma; } ;
struct bna_dma_addr {int /*<<< orphan*/  msb; int /*<<< orphan*/  lsb; } ;
struct TYPE_7__ {void** sw_qpt; void* sw_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNA_GET_DMA_ADDR (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BNA_SET_DMA_ADDR (int /*<<< orphan*/ ,struct bna_dma_addr*) ; 
 scalar_t__ PAGE_SIZE ; 

__attribute__((used)) static void
bna_rxp_cqpt_setup(struct bna_rxp *rxp,
		u32 page_count,
		u32 page_size,
		struct bna_mem_descr *qpt_mem,
		struct bna_mem_descr *swqpt_mem,
		struct bna_mem_descr *page_mem)
{
	u8 *kva;
	u64 dma;
	struct bna_dma_addr bna_dma;
	int	i;

	rxp->cq.qpt.hw_qpt_ptr.lsb = qpt_mem->dma.lsb;
	rxp->cq.qpt.hw_qpt_ptr.msb = qpt_mem->dma.msb;
	rxp->cq.qpt.kv_qpt_ptr = qpt_mem->kva;
	rxp->cq.qpt.page_count = page_count;
	rxp->cq.qpt.page_size = page_size;

	rxp->cq.ccb->sw_qpt = (void **) swqpt_mem->kva;
	rxp->cq.ccb->sw_q = page_mem->kva;

	kva = page_mem->kva;
	BNA_GET_DMA_ADDR(&page_mem->dma, dma);

	for (i = 0; i < rxp->cq.qpt.page_count; i++) {
		rxp->cq.ccb->sw_qpt[i] = kva;
		kva += PAGE_SIZE;

		BNA_SET_DMA_ADDR(dma, &bna_dma);
		((struct bna_dma_addr *)rxp->cq.qpt.kv_qpt_ptr)[i].lsb =
			bna_dma.lsb;
		((struct bna_dma_addr *)rxp->cq.qpt.kv_qpt_ptr)[i].msb =
			bna_dma.msb;
		dma += PAGE_SIZE;
	}
}