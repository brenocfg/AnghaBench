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
struct TYPE_2__ {scalar_t__ rss_hash_result; scalar_t__ rss_hash_type; } ;
struct mlx5e_cq_decomp {TYPE_1__ title; } ;
struct mlx5e_rq {struct mlx5e_cq_decomp cqd; } ;
struct mlx5_cqwq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_decompress_cqe (struct mlx5e_rq*,struct mlx5_cqwq*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mlx5e_decompress_cqe_no_hash(struct mlx5e_rq *rq,
						struct mlx5_cqwq *wq,
						u32 cqcc)
{
	struct mlx5e_cq_decomp *cqd = &rq->cqd;

	mlx5e_decompress_cqe(rq, wq, cqcc);
	cqd->title.rss_hash_type   = 0;
	cqd->title.rss_hash_result = 0;
}