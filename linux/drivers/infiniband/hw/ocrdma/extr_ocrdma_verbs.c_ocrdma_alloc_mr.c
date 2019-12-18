#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct ocrdma_pd {int /*<<< orphan*/  id; } ;
struct TYPE_6__ {int fr_mr; int lkey; scalar_t__ mw_bind; scalar_t__ local_wr; scalar_t__ local_rd; scalar_t__ remote_wr; scalar_t__ remote_rd; } ;
struct ib_mr {int rkey; int lkey; } ;
struct ocrdma_mr {struct ocrdma_mr* pages; TYPE_2__ hwmr; struct ib_mr ibmr; } ;
struct TYPE_5__ {scalar_t__ max_pages_per_frmr; } ;
struct ocrdma_dev {unsigned long* stag_arr; TYPE_1__ attr; } ;
struct ib_udata {int dummy; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;
typedef  enum ib_mr_type { ____Placeholder_ib_mr_type } ib_mr_type ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct ib_mr* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IB_MR_TYPE_MEM_REG ; 
 int OCRDMA_MAX_STAG ; 
 struct ocrdma_dev* get_ocrdma_dev (int /*<<< orphan*/ ) ; 
 struct ocrdma_pd* get_ocrdma_pd (struct ib_pd*) ; 
 struct ocrdma_mr* kcalloc (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ocrdma_mr*) ; 
 struct ocrdma_mr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int ocrdma_build_pbl_tbl (struct ocrdma_dev*,TYPE_2__*) ; 
 int /*<<< orphan*/  ocrdma_free_mr_pbl_tbl (struct ocrdma_dev*,TYPE_2__*) ; 
 int ocrdma_get_pbl_info (struct ocrdma_dev*,struct ocrdma_mr*,scalar_t__) ; 
 int ocrdma_reg_mr (struct ocrdma_dev*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct ib_mr *ocrdma_alloc_mr(struct ib_pd *ibpd, enum ib_mr_type mr_type,
			      u32 max_num_sg, struct ib_udata *udata)
{
	int status;
	struct ocrdma_mr *mr;
	struct ocrdma_pd *pd = get_ocrdma_pd(ibpd);
	struct ocrdma_dev *dev = get_ocrdma_dev(ibpd->device);

	if (mr_type != IB_MR_TYPE_MEM_REG)
		return ERR_PTR(-EINVAL);

	if (max_num_sg > dev->attr.max_pages_per_frmr)
		return ERR_PTR(-EINVAL);

	mr = kzalloc(sizeof(*mr), GFP_KERNEL);
	if (!mr)
		return ERR_PTR(-ENOMEM);

	mr->pages = kcalloc(max_num_sg, sizeof(u64), GFP_KERNEL);
	if (!mr->pages) {
		status = -ENOMEM;
		goto pl_err;
	}

	status = ocrdma_get_pbl_info(dev, mr, max_num_sg);
	if (status)
		goto pbl_err;
	mr->hwmr.fr_mr = 1;
	mr->hwmr.remote_rd = 0;
	mr->hwmr.remote_wr = 0;
	mr->hwmr.local_rd = 0;
	mr->hwmr.local_wr = 0;
	mr->hwmr.mw_bind = 0;
	status = ocrdma_build_pbl_tbl(dev, &mr->hwmr);
	if (status)
		goto pbl_err;
	status = ocrdma_reg_mr(dev, &mr->hwmr, pd->id, 0);
	if (status)
		goto mbx_err;
	mr->ibmr.rkey = mr->hwmr.lkey;
	mr->ibmr.lkey = mr->hwmr.lkey;
	dev->stag_arr[(mr->hwmr.lkey >> 8) & (OCRDMA_MAX_STAG - 1)] =
		(unsigned long) mr;
	return &mr->ibmr;
mbx_err:
	ocrdma_free_mr_pbl_tbl(dev, &mr->hwmr);
pbl_err:
	kfree(mr->pages);
pl_err:
	kfree(mr);
	return ERR_PTR(-ENOMEM);
}