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
typedef  int /*<<< orphan*/  u32 ;
struct qedf_rport {int sq_mem_size; int sq_pbl_size; int sq_dma; int sq_pbl_dma; void* sq; void* sq_pbl; } ;
struct qedf_ctx {TYPE_1__* pdev; int /*<<< orphan*/  dbg_ctx; } ;
struct fcoe_wqe {int dummy; } ;
typedef  int dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int QEDF_PAGE_SIZE ; 
 int /*<<< orphan*/  QEDF_WARN (int /*<<< orphan*/ *,char*) ; 
 int SQ_NUM_ENTRIES ; 
 int /*<<< orphan*/  U64_HI (int) ; 
 int /*<<< orphan*/  U64_LO (int) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,void*,int) ; 

__attribute__((used)) static int qedf_alloc_sq(struct qedf_ctx *qedf, struct qedf_rport *fcport)
{
	int rval = 0;
	u32 *pbl;
	dma_addr_t page;
	int num_pages;

	/* Calculate appropriate queue and PBL sizes */
	fcport->sq_mem_size = SQ_NUM_ENTRIES * sizeof(struct fcoe_wqe);
	fcport->sq_mem_size = ALIGN(fcport->sq_mem_size, QEDF_PAGE_SIZE);
	fcport->sq_pbl_size = (fcport->sq_mem_size / QEDF_PAGE_SIZE) *
	    sizeof(void *);
	fcport->sq_pbl_size = fcport->sq_pbl_size + QEDF_PAGE_SIZE;

	fcport->sq = dma_alloc_coherent(&qedf->pdev->dev, fcport->sq_mem_size,
					&fcport->sq_dma, GFP_KERNEL);
	if (!fcport->sq) {
		QEDF_WARN(&(qedf->dbg_ctx), "Could not allocate send queue.\n");
		rval = 1;
		goto out;
	}

	fcport->sq_pbl = dma_alloc_coherent(&qedf->pdev->dev,
					    fcport->sq_pbl_size,
					    &fcport->sq_pbl_dma, GFP_KERNEL);
	if (!fcport->sq_pbl) {
		QEDF_WARN(&(qedf->dbg_ctx), "Could not allocate send queue PBL.\n");
		rval = 1;
		goto out_free_sq;
	}

	/* Create PBL */
	num_pages = fcport->sq_mem_size / QEDF_PAGE_SIZE;
	page = fcport->sq_dma;
	pbl = (u32 *)fcport->sq_pbl;

	while (num_pages--) {
		*pbl = U64_LO(page);
		pbl++;
		*pbl = U64_HI(page);
		pbl++;
		page += QEDF_PAGE_SIZE;
	}

	return rval;

out_free_sq:
	dma_free_coherent(&qedf->pdev->dev, fcport->sq_mem_size, fcport->sq,
	    fcport->sq_dma);
out:
	return rval;
}