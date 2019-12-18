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
struct mlx5_cqe64 {int /*<<< orphan*/  wqe_counter; int /*<<< orphan*/  byte_cnt; } ;
struct mlx5e_cq_decomp {int /*<<< orphan*/  wqe_counter; int /*<<< orphan*/  left; struct mlx5_cqe64 title; } ;
struct mlx5e_rq {TYPE_1__* stats; struct mlx5e_cq_decomp cqd; } ;
struct mlx5_cqwq {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cqe_compress_blks; } ;

/* Variables and functions */
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_read_cqe_slot (struct mlx5_cqwq*,int /*<<< orphan*/ ,struct mlx5_cqe64*) ; 

__attribute__((used)) static inline void mlx5e_read_title_slot(struct mlx5e_rq *rq,
					 struct mlx5_cqwq *wq,
					 u32 cqcc)
{
	struct mlx5e_cq_decomp *cqd = &rq->cqd;
	struct mlx5_cqe64 *title = &cqd->title;

	mlx5e_read_cqe_slot(wq, cqcc, title);
	cqd->left        = be32_to_cpu(title->byte_cnt);
	cqd->wqe_counter = be16_to_cpu(title->wqe_counter);
	rq->stats->cqe_compress_blks++;
}