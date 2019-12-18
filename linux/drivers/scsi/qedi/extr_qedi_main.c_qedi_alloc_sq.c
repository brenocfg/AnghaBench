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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct qedi_endpoint {int sq_mem_size; int sq_pbl_size; scalar_t__ sq_dma; void* sq; void* sq_pbl; scalar_t__ sq_pbl_dma; } ;
struct qedi_ctx {TYPE_1__* pdev; int /*<<< orphan*/  dbg_ctx; } ;
struct iscsi_wqe {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int QEDI_PAGE_SIZE ; 
 int QEDI_SQ_SIZE ; 
 int /*<<< orphan*/  QEDI_WARN (int /*<<< orphan*/ *,char*) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,void*,scalar_t__) ; 

int qedi_alloc_sq(struct qedi_ctx *qedi, struct qedi_endpoint *ep)
{
	int rval = 0;
	u32 *pbl;
	dma_addr_t page;
	int num_pages;

	if (!ep)
		return -EIO;

	/* Calculate appropriate queue and PBL sizes */
	ep->sq_mem_size = QEDI_SQ_SIZE * sizeof(struct iscsi_wqe);
	ep->sq_mem_size += QEDI_PAGE_SIZE - 1;

	ep->sq_pbl_size = (ep->sq_mem_size / QEDI_PAGE_SIZE) * sizeof(void *);
	ep->sq_pbl_size = ep->sq_pbl_size + QEDI_PAGE_SIZE;

	ep->sq = dma_alloc_coherent(&qedi->pdev->dev, ep->sq_mem_size,
				    &ep->sq_dma, GFP_KERNEL);
	if (!ep->sq) {
		QEDI_WARN(&qedi->dbg_ctx,
			  "Could not allocate send queue.\n");
		rval = -ENOMEM;
		goto out;
	}
	ep->sq_pbl = dma_alloc_coherent(&qedi->pdev->dev, ep->sq_pbl_size,
					&ep->sq_pbl_dma, GFP_KERNEL);
	if (!ep->sq_pbl) {
		QEDI_WARN(&qedi->dbg_ctx,
			  "Could not allocate send queue PBL.\n");
		rval = -ENOMEM;
		goto out_free_sq;
	}

	/* Create PBL */
	num_pages = ep->sq_mem_size / QEDI_PAGE_SIZE;
	page = ep->sq_dma;
	pbl = (u32 *)ep->sq_pbl;

	while (num_pages--) {
		*pbl = (u32)page;
		pbl++;
		*pbl = (u32)((u64)page >> 32);
		pbl++;
		page += QEDI_PAGE_SIZE;
	}

	return rval;

out_free_sq:
	dma_free_coherent(&qedi->pdev->dev, ep->sq_mem_size, ep->sq,
			  ep->sq_dma);
out:
	return rval;
}