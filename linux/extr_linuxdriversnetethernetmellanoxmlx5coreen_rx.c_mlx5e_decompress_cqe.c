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
typedef  int u32 ;
struct TYPE_9__ {int /*<<< orphan*/  wq; } ;
struct mlx5e_rq {scalar_t__ wq_type; TYPE_4__ wqe; } ;
struct TYPE_10__ {int op_own; int /*<<< orphan*/  wqe_counter; int /*<<< orphan*/  check_sum; int /*<<< orphan*/  byte_cnt; } ;
struct TYPE_7__ {int log_sz; } ;
struct TYPE_8__ {TYPE_2__ fbc; } ;
struct mlx5e_cq {size_t mini_arr_idx; scalar_t__ decmprs_wqe_counter; TYPE_5__ title; TYPE_3__ wq; TYPE_1__* mini_arr; } ;
struct TYPE_6__ {int /*<<< orphan*/  checksum; int /*<<< orphan*/  byte_cnt; } ;

/* Variables and functions */
 scalar_t__ MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ ; 
 int /*<<< orphan*/  cpu_to_be16 (scalar_t__) ; 
 scalar_t__ mlx5_wq_cyc_ctr2ix (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ mpwrq_get_cqe_consumed_strides (TYPE_5__*) ; 

__attribute__((used)) static inline void mlx5e_decompress_cqe(struct mlx5e_rq *rq,
					struct mlx5e_cq *cq, u32 cqcc)
{
	cq->title.byte_cnt     = cq->mini_arr[cq->mini_arr_idx].byte_cnt;
	cq->title.check_sum    = cq->mini_arr[cq->mini_arr_idx].checksum;
	cq->title.op_own      &= 0xf0;
	cq->title.op_own      |= 0x01 & (cqcc >> cq->wq.fbc.log_sz);
	cq->title.wqe_counter  = cpu_to_be16(cq->decmprs_wqe_counter);

	if (rq->wq_type == MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ)
		cq->decmprs_wqe_counter +=
			mpwrq_get_cqe_consumed_strides(&cq->title);
	else
		cq->decmprs_wqe_counter =
			mlx5_wq_cyc_ctr2ix(&rq->wqe.wq, cq->decmprs_wqe_counter + 1);
}