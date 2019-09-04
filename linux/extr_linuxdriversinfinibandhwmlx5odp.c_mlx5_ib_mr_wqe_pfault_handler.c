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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {int /*<<< orphan*/  wq_num; int /*<<< orphan*/  wqe_index; } ;
struct mlx5_pagefault {int type; TYPE_2__ wqe; int /*<<< orphan*/  token; } ;
struct TYPE_3__ {int /*<<< orphan*/  base; } ;
struct mlx5_ib_qp {TYPE_1__ trans_qp; } ;
struct mlx5_ib_dev {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MLX5_PFAULT_REQUESTOR ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  mlx5_ib_dbg (struct mlx5_ib_dev*,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mlx5_ib_err (struct mlx5_ib_dev*,char*,...) ; 
 int mlx5_ib_mr_initiator_pfault_handler (struct mlx5_ib_dev*,struct mlx5_pagefault*,struct mlx5_ib_qp*,void**,void**,int) ; 
 int mlx5_ib_mr_responder_pfault_handler (struct mlx5_ib_dev*,struct mlx5_pagefault*,struct mlx5_ib_qp*,void**,void**,int) ; 
 struct mlx5_ib_qp* mlx5_ib_odp_find_qp (struct mlx5_ib_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_ib_page_fault_resume (struct mlx5_ib_dev*,struct mlx5_pagefault*,int) ; 
 int mlx5_ib_read_user_wqe (struct mlx5_ib_qp*,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pagefault_data_segments (struct mlx5_ib_dev*,struct mlx5_pagefault*,struct mlx5_ib_qp*,void*,void*,scalar_t__*,scalar_t__*,int) ; 

__attribute__((used)) static void mlx5_ib_mr_wqe_pfault_handler(struct mlx5_ib_dev *dev,
					  struct mlx5_pagefault *pfault)
{
	int ret;
	void *wqe, *wqe_end;
	u32 bytes_mapped, total_wqe_bytes;
	char *buffer = NULL;
	int resume_with_error = 1;
	u16 wqe_index = pfault->wqe.wqe_index;
	int requestor = pfault->type & MLX5_PFAULT_REQUESTOR;
	struct mlx5_ib_qp *qp;

	buffer = (char *)__get_free_page(GFP_KERNEL);
	if (!buffer) {
		mlx5_ib_err(dev, "Error allocating memory for IO page fault handling.\n");
		goto resolve_page_fault;
	}

	qp = mlx5_ib_odp_find_qp(dev, pfault->wqe.wq_num);
	if (!qp)
		goto resolve_page_fault;

	ret = mlx5_ib_read_user_wqe(qp, requestor, wqe_index, buffer,
				    PAGE_SIZE, &qp->trans_qp.base);
	if (ret < 0) {
		mlx5_ib_err(dev, "Failed reading a WQE following page fault, error=%d, wqe_index=%x, qpn=%x\n",
			    ret, wqe_index, pfault->token);
		goto resolve_page_fault;
	}

	wqe = buffer;
	if (requestor)
		ret = mlx5_ib_mr_initiator_pfault_handler(dev, pfault, qp, &wqe,
							  &wqe_end, ret);
	else
		ret = mlx5_ib_mr_responder_pfault_handler(dev, pfault, qp, &wqe,
							  &wqe_end, ret);
	if (ret < 0)
		goto resolve_page_fault;

	if (wqe >= wqe_end) {
		mlx5_ib_err(dev, "ODP fault on invalid WQE.\n");
		goto resolve_page_fault;
	}

	ret = pagefault_data_segments(dev, pfault, qp, wqe, wqe_end,
				      &bytes_mapped, &total_wqe_bytes,
				      !requestor);
	if (ret == -EAGAIN) {
		resume_with_error = 0;
		goto resolve_page_fault;
	} else if (ret < 0 || total_wqe_bytes > bytes_mapped) {
		goto resolve_page_fault;
	}

	resume_with_error = 0;
resolve_page_fault:
	mlx5_ib_page_fault_resume(dev, pfault, resume_with_error);
	mlx5_ib_dbg(dev, "PAGE FAULT completed. QP 0x%x resume_with_error=%d, type: 0x%x\n",
		    pfault->wqe.wq_num, resume_with_error,
		    pfault->type);
	free_page((unsigned long)buffer);
}