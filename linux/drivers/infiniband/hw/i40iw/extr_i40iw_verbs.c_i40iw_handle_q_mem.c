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
typedef  void* u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct i40iw_hmc_pble {void* addr; scalar_t__ idx; } ;
struct i40iw_qp_mr {struct i40iw_hmc_pble rq_pbl; void* shadow; struct i40iw_hmc_pble sq_pbl; } ;
struct TYPE_2__ {scalar_t__ idx; scalar_t__ addr; } ;
struct i40iw_pble_alloc {scalar_t__ level; TYPE_1__ level1; } ;
struct i40iw_cq_mr {void* shadow; struct i40iw_hmc_pble cq_pbl; } ;
struct i40iw_pbl {int pbl_allocated; struct i40iw_cq_mr cq_mr; struct i40iw_qp_mr qp_mr; struct i40iw_mr* iwmr; struct i40iw_pble_alloc pble_alloc; } ;
struct i40iw_mr {void** pgaddrmem; scalar_t__ type; int /*<<< orphan*/  page_size; } ;
struct i40iw_mem_reg_req {int sq_pages; int rq_pages; int cq_pages; } ;
struct i40iw_device {int /*<<< orphan*/  pble_rsrc; } ;
typedef  void* dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ I40IW_LEVEL_1 ; 
 scalar_t__ IW_MEMREG_TYPE_QP ; 
 int i40iw_check_mem_contiguous (void**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_free_pble (int /*<<< orphan*/ ,struct i40iw_pble_alloc*) ; 
 int i40iw_setup_pbles (struct i40iw_device*,struct i40iw_mr*,int) ; 

__attribute__((used)) static int i40iw_handle_q_mem(struct i40iw_device *iwdev,
			      struct i40iw_mem_reg_req *req,
			      struct i40iw_pbl *iwpbl,
			      bool use_pbles)
{
	struct i40iw_pble_alloc *palloc = &iwpbl->pble_alloc;
	struct i40iw_mr *iwmr = iwpbl->iwmr;
	struct i40iw_qp_mr *qpmr = &iwpbl->qp_mr;
	struct i40iw_cq_mr *cqmr = &iwpbl->cq_mr;
	struct i40iw_hmc_pble *hmc_p;
	u64 *arr = iwmr->pgaddrmem;
	u32 pg_size;
	int err;
	int total;
	bool ret = true;

	total = req->sq_pages + req->rq_pages + req->cq_pages;
	pg_size = iwmr->page_size;

	err = i40iw_setup_pbles(iwdev, iwmr, use_pbles);
	if (err)
		return err;

	if (use_pbles && (palloc->level != I40IW_LEVEL_1)) {
		i40iw_free_pble(iwdev->pble_rsrc, palloc);
		iwpbl->pbl_allocated = false;
		return -ENOMEM;
	}

	if (use_pbles)
		arr = (u64 *)palloc->level1.addr;

	if (iwmr->type == IW_MEMREG_TYPE_QP) {
		hmc_p = &qpmr->sq_pbl;
		qpmr->shadow = (dma_addr_t)arr[total];

		if (use_pbles) {
			ret = i40iw_check_mem_contiguous(arr, req->sq_pages, pg_size);
			if (ret)
				ret = i40iw_check_mem_contiguous(&arr[req->sq_pages], req->rq_pages, pg_size);
		}

		if (!ret) {
			hmc_p->idx = palloc->level1.idx;
			hmc_p = &qpmr->rq_pbl;
			hmc_p->idx = palloc->level1.idx + req->sq_pages;
		} else {
			hmc_p->addr = arr[0];
			hmc_p = &qpmr->rq_pbl;
			hmc_p->addr = arr[req->sq_pages];
		}
	} else {		/* CQ */
		hmc_p = &cqmr->cq_pbl;
		cqmr->shadow = (dma_addr_t)arr[total];

		if (use_pbles)
			ret = i40iw_check_mem_contiguous(arr, req->cq_pages, pg_size);

		if (!ret)
			hmc_p->idx = palloc->level1.idx;
		else
			hmc_p->addr = arr[0];
	}

	if (use_pbles && ret) {
		i40iw_free_pble(iwdev->pble_rsrc, palloc);
		iwpbl->pbl_allocated = false;
	}

	return err;
}