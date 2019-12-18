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
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  wq; } ;
struct mlx5_cqe64 {int op_own; int /*<<< orphan*/  wqe_counter; int /*<<< orphan*/  check_sum; int /*<<< orphan*/  byte_cnt; } ;
struct mlx5e_cq_decomp {size_t mini_arr_idx; scalar_t__ wqe_counter; struct mlx5_cqe64 title; struct mlx5_mini_cqe8* mini_arr; } ;
struct mlx5e_rq {scalar_t__ wq_type; TYPE_2__ wqe; struct mlx5e_cq_decomp cqd; } ;
struct mlx5_mini_cqe8 {int /*<<< orphan*/  checksum; int /*<<< orphan*/  byte_cnt; } ;
struct TYPE_3__ {int log_sz; } ;
struct mlx5_cqwq {TYPE_1__ fbc; } ;

/* Variables and functions */
 scalar_t__ MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ ; 
 int /*<<< orphan*/  cpu_to_be16 (scalar_t__) ; 
 scalar_t__ mlx5_wq_cyc_ctr2ix (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ mpwrq_get_cqe_consumed_strides (struct mlx5_cqe64*) ; 

__attribute__((used)) static inline void mlx5e_decompress_cqe(struct mlx5e_rq *rq,
					struct mlx5_cqwq *wq,
					u32 cqcc)
{
	struct mlx5e_cq_decomp *cqd = &rq->cqd;
	struct mlx5_mini_cqe8 *mini_cqe = &cqd->mini_arr[cqd->mini_arr_idx];
	struct mlx5_cqe64 *title = &cqd->title;

	title->byte_cnt     = mini_cqe->byte_cnt;
	title->check_sum    = mini_cqe->checksum;
	title->op_own      &= 0xf0;
	title->op_own      |= 0x01 & (cqcc >> wq->fbc.log_sz);
	title->wqe_counter  = cpu_to_be16(cqd->wqe_counter);

	if (rq->wq_type == MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ)
		cqd->wqe_counter += mpwrq_get_cqe_consumed_strides(title);
	else
		cqd->wqe_counter =
			mlx5_wq_cyc_ctr2ix(&rq->wqe.wq, cqd->wqe_counter + 1);
}