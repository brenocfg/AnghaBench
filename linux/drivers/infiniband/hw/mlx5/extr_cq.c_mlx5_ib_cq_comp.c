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
struct mlx5_eqe {int dummy; } ;
struct mlx5_core_cq {int dummy; } ;
struct ib_cq {int /*<<< orphan*/  cq_context; int /*<<< orphan*/  (* comp_handler ) (struct ib_cq*,int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {struct ib_cq ibcq; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ib_cq*,int /*<<< orphan*/ ) ; 
 TYPE_1__* to_mibcq (struct mlx5_core_cq*) ; 

__attribute__((used)) static void mlx5_ib_cq_comp(struct mlx5_core_cq *cq, struct mlx5_eqe *eqe)
{
	struct ib_cq *ibcq = &to_mibcq(cq)->ibcq;

	ibcq->comp_handler(ibcq, ibcq->cq_context);
}