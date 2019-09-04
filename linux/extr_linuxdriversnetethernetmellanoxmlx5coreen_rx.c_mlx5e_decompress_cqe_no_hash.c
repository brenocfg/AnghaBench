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
struct mlx5e_rq {int dummy; } ;
struct TYPE_2__ {scalar_t__ rss_hash_result; scalar_t__ rss_hash_type; } ;
struct mlx5e_cq {TYPE_1__ title; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_decompress_cqe (struct mlx5e_rq*,struct mlx5e_cq*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mlx5e_decompress_cqe_no_hash(struct mlx5e_rq *rq,
						struct mlx5e_cq *cq, u32 cqcc)
{
	mlx5e_decompress_cqe(rq, cq, cqcc);
	cq->title.rss_hash_type   = 0;
	cq->title.rss_hash_result = 0;
}