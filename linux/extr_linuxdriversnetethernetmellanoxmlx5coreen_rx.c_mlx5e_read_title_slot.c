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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5e_rq {TYPE_1__* stats; } ;
struct TYPE_4__ {int /*<<< orphan*/  wqe_counter; int /*<<< orphan*/  byte_cnt; } ;
struct mlx5e_cq {TYPE_2__ title; int /*<<< orphan*/  decmprs_wqe_counter; int /*<<< orphan*/  decmprs_left; } ;
struct TYPE_3__ {int /*<<< orphan*/  cqe_compress_blks; } ;

/* Variables and functions */
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_read_cqe_slot (struct mlx5e_cq*,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static inline void mlx5e_read_title_slot(struct mlx5e_rq *rq,
					 struct mlx5e_cq *cq, u32 cqcc)
{
	mlx5e_read_cqe_slot(cq, cqcc, &cq->title);
	cq->decmprs_left        = be32_to_cpu(cq->title.byte_cnt);
	cq->decmprs_wqe_counter = be16_to_cpu(cq->title.wqe_counter);
	rq->stats->cqe_compress_blks++;
}