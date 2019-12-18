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
struct bnx2i_hba {TYPE_1__* pcidev; } ;
struct TYPE_4__ {scalar_t__ cq_phys; int /*<<< orphan*/ * cq_virt; int /*<<< orphan*/  cq_mem_size; scalar_t__ cq_pgtbl_phys; int /*<<< orphan*/ * cq_pgtbl_virt; int /*<<< orphan*/  cq_pgtbl_size; scalar_t__ rq_phys; int /*<<< orphan*/ * rq_virt; int /*<<< orphan*/  rq_mem_size; scalar_t__ rq_pgtbl_phys; int /*<<< orphan*/ * rq_pgtbl_virt; int /*<<< orphan*/  rq_pgtbl_size; scalar_t__ sq_phys; int /*<<< orphan*/ * sq_virt; int /*<<< orphan*/  sq_mem_size; scalar_t__ sq_pgtbl_phys; int /*<<< orphan*/ * sq_pgtbl_virt; int /*<<< orphan*/  sq_pgtbl_size; int /*<<< orphan*/ * ctx_base; } ;
struct bnx2i_endpoint {TYPE_2__ qp; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 

void bnx2i_free_qp_resc(struct bnx2i_hba *hba, struct bnx2i_endpoint *ep)
{
	if (ep->qp.ctx_base) {
		iounmap(ep->qp.ctx_base);
		ep->qp.ctx_base = NULL;
	}
	/* Free SQ mem */
	if (ep->qp.sq_pgtbl_virt) {
		dma_free_coherent(&hba->pcidev->dev, ep->qp.sq_pgtbl_size,
				  ep->qp.sq_pgtbl_virt, ep->qp.sq_pgtbl_phys);
		ep->qp.sq_pgtbl_virt = NULL;
		ep->qp.sq_pgtbl_phys = 0;
	}
	if (ep->qp.sq_virt) {
		dma_free_coherent(&hba->pcidev->dev, ep->qp.sq_mem_size,
				  ep->qp.sq_virt, ep->qp.sq_phys);
		ep->qp.sq_virt = NULL;
		ep->qp.sq_phys = 0;
	}

	/* Free RQ mem */
	if (ep->qp.rq_pgtbl_virt) {
		dma_free_coherent(&hba->pcidev->dev, ep->qp.rq_pgtbl_size,
				  ep->qp.rq_pgtbl_virt, ep->qp.rq_pgtbl_phys);
		ep->qp.rq_pgtbl_virt = NULL;
		ep->qp.rq_pgtbl_phys = 0;
	}
	if (ep->qp.rq_virt) {
		dma_free_coherent(&hba->pcidev->dev, ep->qp.rq_mem_size,
				  ep->qp.rq_virt, ep->qp.rq_phys);
		ep->qp.rq_virt = NULL;
		ep->qp.rq_phys = 0;
	}

	/* Free CQ mem */
	if (ep->qp.cq_pgtbl_virt) {
		dma_free_coherent(&hba->pcidev->dev, ep->qp.cq_pgtbl_size,
				  ep->qp.cq_pgtbl_virt, ep->qp.cq_pgtbl_phys);
		ep->qp.cq_pgtbl_virt = NULL;
		ep->qp.cq_pgtbl_phys = 0;
	}
	if (ep->qp.cq_virt) {
		dma_free_coherent(&hba->pcidev->dev, ep->qp.cq_mem_size,
				  ep->qp.cq_virt, ep->qp.cq_phys);
		ep->qp.cq_virt = NULL;
		ep->qp.cq_phys = 0;
	}
}