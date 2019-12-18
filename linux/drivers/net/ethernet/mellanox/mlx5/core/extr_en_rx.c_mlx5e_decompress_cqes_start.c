#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;
struct mlx5e_cq_decomp {int /*<<< orphan*/  mini_arr_idx; int /*<<< orphan*/  title; } ;
struct mlx5e_rq {int /*<<< orphan*/  (* handle_rx_cqe ) (struct mlx5e_rq*,int /*<<< orphan*/ *) ;struct mlx5e_cq_decomp cqd; } ;
struct mlx5_cqwq {scalar_t__ cc; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_decompress_cqe (struct mlx5e_rq*,struct mlx5_cqwq*,scalar_t__) ; 
 scalar_t__ mlx5e_decompress_cqes_cont (struct mlx5e_rq*,struct mlx5_cqwq*,int,int) ; 
 int /*<<< orphan*/  mlx5e_read_mini_arr_slot (struct mlx5_cqwq*,struct mlx5e_cq_decomp*,scalar_t__) ; 
 int /*<<< orphan*/  mlx5e_read_title_slot (struct mlx5e_rq*,struct mlx5_cqwq*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct mlx5e_rq*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline u32 mlx5e_decompress_cqes_start(struct mlx5e_rq *rq,
					      struct mlx5_cqwq *wq,
					      int budget_rem)
{
	struct mlx5e_cq_decomp *cqd = &rq->cqd;
	u32 cc = wq->cc;

	mlx5e_read_title_slot(rq, wq, cc);
	mlx5e_read_mini_arr_slot(wq, cqd, cc + 1);
	mlx5e_decompress_cqe(rq, wq, cc);
	rq->handle_rx_cqe(rq, &cqd->title);
	cqd->mini_arr_idx++;

	return mlx5e_decompress_cqes_cont(rq, wq, 1, budget_rem) - 1;
}