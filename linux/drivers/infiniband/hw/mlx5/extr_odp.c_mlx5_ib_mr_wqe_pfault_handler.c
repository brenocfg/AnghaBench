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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  wq_num; int /*<<< orphan*/  wqe_index; } ;
struct mlx5_pagefault {int type; TYPE_1__ wqe; int /*<<< orphan*/  token; } ;
struct mlx5_ib_srq {int dummy; } ;
struct mlx5_ib_qp {int dummy; } ;
struct mlx5_ib_dev {int dummy; } ;
struct mlx5_core_rsc_common {scalar_t__ res; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MLX5_PFAULT_REQUESTOR ; 
 scalar_t__ MLX5_RES_QP ; 
 scalar_t__ MLX5_RES_SRQ ; 
 scalar_t__ MLX5_RES_XSRQ ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  mlx5_core_res_put (struct mlx5_core_rsc_common*) ; 
 int /*<<< orphan*/  mlx5_ib_dbg (struct mlx5_ib_dev*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  mlx5_ib_err (struct mlx5_ib_dev*,char*,...) ; 
 int mlx5_ib_mr_initiator_pfault_handler (struct mlx5_ib_dev*,struct mlx5_pagefault*,struct mlx5_ib_qp*,void**,void**,size_t) ; 
 int mlx5_ib_mr_responder_pfault_handler_rq (struct mlx5_ib_dev*,struct mlx5_ib_qp*,void*,void**,size_t) ; 
 int mlx5_ib_mr_responder_pfault_handler_srq (struct mlx5_ib_dev*,struct mlx5_ib_srq*,void**,void**,size_t) ; 
 int /*<<< orphan*/  mlx5_ib_page_fault_resume (struct mlx5_ib_dev*,struct mlx5_pagefault*,int) ; 
 int mlx5_ib_read_user_wqe_rq (struct mlx5_ib_qp*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,size_t*) ; 
 int mlx5_ib_read_user_wqe_sq (struct mlx5_ib_qp*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,size_t*) ; 
 int mlx5_ib_read_user_wqe_srq (struct mlx5_ib_srq*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,size_t*) ; 
 struct mlx5_core_rsc_common* odp_get_rsc (struct mlx5_ib_dev*,int /*<<< orphan*/ ,int) ; 
 int pagefault_data_segments (struct mlx5_ib_dev*,struct mlx5_pagefault*,void*,void*,scalar_t__*,scalar_t__*,int) ; 
 struct mlx5_ib_qp* res_to_qp (struct mlx5_core_rsc_common*) ; 
 struct mlx5_ib_srq* res_to_srq (struct mlx5_core_rsc_common*) ; 

__attribute__((used)) static void mlx5_ib_mr_wqe_pfault_handler(struct mlx5_ib_dev *dev,
					  struct mlx5_pagefault *pfault)
{
	bool sq = pfault->type & MLX5_PFAULT_REQUESTOR;
	u16 wqe_index = pfault->wqe.wqe_index;
	void *wqe, *wqe_start = NULL, *wqe_end = NULL;
	u32 bytes_mapped, total_wqe_bytes;
	struct mlx5_core_rsc_common *res;
	int resume_with_error = 1;
	struct mlx5_ib_qp *qp;
	size_t bytes_copied;
	int ret = 0;

	res = odp_get_rsc(dev, pfault->wqe.wq_num, pfault->type);
	if (!res) {
		mlx5_ib_dbg(dev, "wqe page fault for missing resource %d\n", pfault->wqe.wq_num);
		return;
	}

	if (res->res != MLX5_RES_QP && res->res != MLX5_RES_SRQ &&
	    res->res != MLX5_RES_XSRQ) {
		mlx5_ib_err(dev, "wqe page fault for unsupported type %d\n",
			    pfault->type);
		goto resolve_page_fault;
	}

	wqe_start = (void *)__get_free_page(GFP_KERNEL);
	if (!wqe_start) {
		mlx5_ib_err(dev, "Error allocating memory for IO page fault handling.\n");
		goto resolve_page_fault;
	}

	wqe = wqe_start;
	qp = (res->res == MLX5_RES_QP) ? res_to_qp(res) : NULL;
	if (qp && sq) {
		ret = mlx5_ib_read_user_wqe_sq(qp, wqe_index, wqe, PAGE_SIZE,
					       &bytes_copied);
		if (ret)
			goto read_user;
		ret = mlx5_ib_mr_initiator_pfault_handler(
			dev, pfault, qp, &wqe, &wqe_end, bytes_copied);
	} else if (qp && !sq) {
		ret = mlx5_ib_read_user_wqe_rq(qp, wqe_index, wqe, PAGE_SIZE,
					       &bytes_copied);
		if (ret)
			goto read_user;
		ret = mlx5_ib_mr_responder_pfault_handler_rq(
			dev, qp, wqe, &wqe_end, bytes_copied);
	} else if (!qp) {
		struct mlx5_ib_srq *srq = res_to_srq(res);

		ret = mlx5_ib_read_user_wqe_srq(srq, wqe_index, wqe, PAGE_SIZE,
						&bytes_copied);
		if (ret)
			goto read_user;
		ret = mlx5_ib_mr_responder_pfault_handler_srq(
			dev, srq, &wqe, &wqe_end, bytes_copied);
	}

	if (ret < 0 || wqe >= wqe_end)
		goto resolve_page_fault;

	ret = pagefault_data_segments(dev, pfault, wqe, wqe_end, &bytes_mapped,
				      &total_wqe_bytes, !sq);
	if (ret == -EAGAIN)
		goto out;

	if (ret < 0 || total_wqe_bytes > bytes_mapped)
		goto resolve_page_fault;

out:
	ret = 0;
	resume_with_error = 0;

read_user:
	if (ret)
		mlx5_ib_err(
			dev,
			"Failed reading a WQE following page fault, error %d, wqe_index %x, qpn %x\n",
			ret, wqe_index, pfault->token);

resolve_page_fault:
	mlx5_ib_page_fault_resume(dev, pfault, resume_with_error);
	mlx5_ib_dbg(dev, "PAGE FAULT completed. QP 0x%x resume_with_error=%d, type: 0x%x\n",
		    pfault->wqe.wq_num, resume_with_error,
		    pfault->type);
	mlx5_core_res_put(res);
	free_page((unsigned long)wqe_start);
}