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
typedef  int /*<<< orphan*/  u32 ;
struct qedf_ctx {int num_queues; TYPE_2__** global_queues; scalar_t__ p_cpuq; int /*<<< orphan*/  dbg_ctx; TYPE_1__* pdev; } ;
struct global_queue {int dummy; } ;
struct fcoe_cqe {int dummy; } ;
typedef  int dma_addr_t ;
struct TYPE_4__ {int cq_mem_size; int cq_pbl_size; int cq_dma; int cq_pbl_dma; scalar_t__ cq_cons_idx; void* cq_pbl; void* cq; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 void* ALIGN (int,int) ; 
 int ENOMEM ; 
 int FCOE_PARAMS_CQ_NUM_ENTRIES ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  QEDF_ERR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  QEDF_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,TYPE_2__**) ; 
 int /*<<< orphan*/  QEDF_LOG_DISC ; 
 int QEDF_PAGE_SIZE ; 
 int /*<<< orphan*/  QEDF_WARN (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  U64_HI (int) ; 
 int /*<<< orphan*/  U64_LO (int) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int qedf_alloc_bdq (struct qedf_ctx*) ; 
 int /*<<< orphan*/  qedf_free_global_queues (struct qedf_ctx*) ; 

__attribute__((used)) static int qedf_alloc_global_queues(struct qedf_ctx *qedf)
{
	u32 *list;
	int i;
	int status = 0, rc;
	u32 *pbl;
	dma_addr_t page;
	int num_pages;

	/* Allocate and map CQs, RQs */
	/*
	 * Number of global queues (CQ / RQ). This should
	 * be <= number of available MSIX vectors for the PF
	 */
	if (!qedf->num_queues) {
		QEDF_ERR(&(qedf->dbg_ctx), "No MSI-X vectors available!\n");
		return 1;
	}

	/*
	 * Make sure we allocated the PBL that will contain the physical
	 * addresses of our queues
	 */
	if (!qedf->p_cpuq) {
		status = 1;
		QEDF_ERR(&qedf->dbg_ctx, "p_cpuq is NULL.\n");
		goto mem_alloc_failure;
	}

	qedf->global_queues = kzalloc((sizeof(struct global_queue *)
	    * qedf->num_queues), GFP_KERNEL);
	if (!qedf->global_queues) {
		QEDF_ERR(&(qedf->dbg_ctx), "Unable to allocate global "
			  "queues array ptr memory\n");
		return -ENOMEM;
	}
	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC,
		   "qedf->global_queues=%p.\n", qedf->global_queues);

	/* Allocate DMA coherent buffers for BDQ */
	rc = qedf_alloc_bdq(qedf);
	if (rc) {
		QEDF_ERR(&qedf->dbg_ctx, "Unable to allocate bdq.\n");
		goto mem_alloc_failure;
	}

	/* Allocate a CQ and an associated PBL for each MSI-X vector */
	for (i = 0; i < qedf->num_queues; i++) {
		qedf->global_queues[i] = kzalloc(sizeof(struct global_queue),
		    GFP_KERNEL);
		if (!qedf->global_queues[i]) {
			QEDF_WARN(&(qedf->dbg_ctx), "Unable to allocate "
				   "global queue %d.\n", i);
			status = -ENOMEM;
			goto mem_alloc_failure;
		}

		qedf->global_queues[i]->cq_mem_size =
		    FCOE_PARAMS_CQ_NUM_ENTRIES * sizeof(struct fcoe_cqe);
		qedf->global_queues[i]->cq_mem_size =
		    ALIGN(qedf->global_queues[i]->cq_mem_size, QEDF_PAGE_SIZE);

		qedf->global_queues[i]->cq_pbl_size =
		    (qedf->global_queues[i]->cq_mem_size /
		    PAGE_SIZE) * sizeof(void *);
		qedf->global_queues[i]->cq_pbl_size =
		    ALIGN(qedf->global_queues[i]->cq_pbl_size, QEDF_PAGE_SIZE);

		qedf->global_queues[i]->cq =
		    dma_alloc_coherent(&qedf->pdev->dev,
				       qedf->global_queues[i]->cq_mem_size,
				       &qedf->global_queues[i]->cq_dma,
				       GFP_KERNEL);

		if (!qedf->global_queues[i]->cq) {
			QEDF_WARN(&(qedf->dbg_ctx), "Could not allocate cq.\n");
			status = -ENOMEM;
			goto mem_alloc_failure;
		}

		qedf->global_queues[i]->cq_pbl =
		    dma_alloc_coherent(&qedf->pdev->dev,
				       qedf->global_queues[i]->cq_pbl_size,
				       &qedf->global_queues[i]->cq_pbl_dma,
				       GFP_KERNEL);

		if (!qedf->global_queues[i]->cq_pbl) {
			QEDF_WARN(&(qedf->dbg_ctx), "Could not allocate cq PBL.\n");
			status = -ENOMEM;
			goto mem_alloc_failure;
		}

		/* Create PBL */
		num_pages = qedf->global_queues[i]->cq_mem_size /
		    QEDF_PAGE_SIZE;
		page = qedf->global_queues[i]->cq_dma;
		pbl = (u32 *)qedf->global_queues[i]->cq_pbl;

		while (num_pages--) {
			*pbl = U64_LO(page);
			pbl++;
			*pbl = U64_HI(page);
			pbl++;
			page += QEDF_PAGE_SIZE;
		}
		/* Set the initial consumer index for cq */
		qedf->global_queues[i]->cq_cons_idx = 0;
	}

	list = (u32 *)qedf->p_cpuq;

	/*
	 * The list is built as follows: CQ#0 PBL pointer, RQ#0 PBL pointer,
	 * CQ#1 PBL pointer, RQ#1 PBL pointer, etc.  Each PBL pointer points
	 * to the physical address which contains an array of pointers to
	 * the physical addresses of the specific queue pages.
	 */
	for (i = 0; i < qedf->num_queues; i++) {
		*list = U64_LO(qedf->global_queues[i]->cq_pbl_dma);
		list++;
		*list = U64_HI(qedf->global_queues[i]->cq_pbl_dma);
		list++;
		*list = U64_LO(0);
		list++;
		*list = U64_HI(0);
		list++;
	}

	return 0;

mem_alloc_failure:
	qedf_free_global_queues(qedf);
	return status;
}