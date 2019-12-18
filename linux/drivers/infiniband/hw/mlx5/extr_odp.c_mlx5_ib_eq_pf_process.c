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
struct TYPE_10__ {int wq_num; void* wqe_index; void* packet_size; } ;
struct TYPE_8__ {int r_key; int rdma_op_len; int /*<<< orphan*/  rdma_va; void* packet_size; } ;
struct mlx5_pagefault {int event_subtype; int bytes_committed; int type; int token; int /*<<< orphan*/  work; struct mlx5_ib_pf_eq* eq; TYPE_5__ wqe; TYPE_3__ rdma; } ;
struct mlx5_ib_pf_eq {int /*<<< orphan*/  core; int /*<<< orphan*/  wq; int /*<<< orphan*/  dev; int /*<<< orphan*/  work; int /*<<< orphan*/  pool; } ;
struct TYPE_9__ {int /*<<< orphan*/  packet_length; int /*<<< orphan*/  wqe_index; int /*<<< orphan*/  pftype_wq; int /*<<< orphan*/  token; } ;
struct TYPE_7__ {int /*<<< orphan*/  rdma_va; int /*<<< orphan*/  rdma_op_len; int /*<<< orphan*/  packet_length; int /*<<< orphan*/  r_key; int /*<<< orphan*/  pftype_token; } ;
struct mlx5_eqe_page_fault {TYPE_4__ wqe; TYPE_2__ rdma; int /*<<< orphan*/  bytes_committed; } ;
struct TYPE_6__ {struct mlx5_eqe_page_fault page_fault; } ;
struct mlx5_eqe {int sub_type; TYPE_1__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MLX5_24BIT_MASK ; 
#define  MLX5_PFAULT_SUBTYPE_RDMA 129 
#define  MLX5_PFAULT_SUBTYPE_WQE 128 
 void* be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 struct mlx5_pagefault* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx5_eqe* mlx5_eq_get_eqe (int /*<<< orphan*/ ,int) ; 
 int mlx5_eq_update_cc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5_eq_update_ci (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mlx5_ib_dbg (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  mlx5_ib_eqe_pf_action ; 
 int /*<<< orphan*/  mlx5_ib_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx5_ib_eq_pf_process(struct mlx5_ib_pf_eq *eq)
{
	struct mlx5_eqe_page_fault *pf_eqe;
	struct mlx5_pagefault *pfault;
	struct mlx5_eqe *eqe;
	int cc = 0;

	while ((eqe = mlx5_eq_get_eqe(eq->core, cc))) {
		pfault = mempool_alloc(eq->pool, GFP_ATOMIC);
		if (!pfault) {
			schedule_work(&eq->work);
			break;
		}

		pf_eqe = &eqe->data.page_fault;
		pfault->event_subtype = eqe->sub_type;
		pfault->bytes_committed = be32_to_cpu(pf_eqe->bytes_committed);

		mlx5_ib_dbg(eq->dev,
			    "PAGE_FAULT: subtype: 0x%02x, bytes_committed: 0x%06x\n",
			    eqe->sub_type, pfault->bytes_committed);

		switch (eqe->sub_type) {
		case MLX5_PFAULT_SUBTYPE_RDMA:
			/* RDMA based event */
			pfault->type =
				be32_to_cpu(pf_eqe->rdma.pftype_token) >> 24;
			pfault->token =
				be32_to_cpu(pf_eqe->rdma.pftype_token) &
				MLX5_24BIT_MASK;
			pfault->rdma.r_key =
				be32_to_cpu(pf_eqe->rdma.r_key);
			pfault->rdma.packet_size =
				be16_to_cpu(pf_eqe->rdma.packet_length);
			pfault->rdma.rdma_op_len =
				be32_to_cpu(pf_eqe->rdma.rdma_op_len);
			pfault->rdma.rdma_va =
				be64_to_cpu(pf_eqe->rdma.rdma_va);
			mlx5_ib_dbg(eq->dev,
				    "PAGE_FAULT: type:0x%x, token: 0x%06x, r_key: 0x%08x\n",
				    pfault->type, pfault->token,
				    pfault->rdma.r_key);
			mlx5_ib_dbg(eq->dev,
				    "PAGE_FAULT: rdma_op_len: 0x%08x, rdma_va: 0x%016llx\n",
				    pfault->rdma.rdma_op_len,
				    pfault->rdma.rdma_va);
			break;

		case MLX5_PFAULT_SUBTYPE_WQE:
			/* WQE based event */
			pfault->type =
				(be32_to_cpu(pf_eqe->wqe.pftype_wq) >> 24) & 0x7;
			pfault->token =
				be32_to_cpu(pf_eqe->wqe.token);
			pfault->wqe.wq_num =
				be32_to_cpu(pf_eqe->wqe.pftype_wq) &
				MLX5_24BIT_MASK;
			pfault->wqe.wqe_index =
				be16_to_cpu(pf_eqe->wqe.wqe_index);
			pfault->wqe.packet_size =
				be16_to_cpu(pf_eqe->wqe.packet_length);
			mlx5_ib_dbg(eq->dev,
				    "PAGE_FAULT: type:0x%x, token: 0x%06x, wq_num: 0x%06x, wqe_index: 0x%04x\n",
				    pfault->type, pfault->token,
				    pfault->wqe.wq_num,
				    pfault->wqe.wqe_index);
			break;

		default:
			mlx5_ib_warn(eq->dev,
				     "Unsupported page fault event sub-type: 0x%02hhx\n",
				     eqe->sub_type);
			/* Unsupported page faults should still be
			 * resolved by the page fault handler
			 */
		}

		pfault->eq = eq;
		INIT_WORK(&pfault->work, mlx5_ib_eqe_pf_action);
		queue_work(eq->wq, &pfault->work);

		cc = mlx5_eq_update_cc(eq->core, ++cc);
	}

	mlx5_eq_update_ci(eq->core, cc, 1);
}