#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* pd; } ;
struct mlx5_ib_mr {int /*<<< orphan*/  num_leaf_free; int /*<<< orphan*/  q_leaf_free; TYPE_3__ ibmr; } ;
struct ib_ucontext {int /*<<< orphan*/  umem_rwsem; int /*<<< orphan*/  umem_tree; } ;
struct TYPE_5__ {TYPE_1__* uobject; } ;
struct TYPE_4__ {struct ib_ucontext* context; } ;

/* Variables and functions */
 int /*<<< orphan*/  ULLONG_MAX ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mr_leaf_free ; 
 int /*<<< orphan*/  rbt_ib_umem_for_each_in_range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct mlx5_ib_mr*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

void mlx5_ib_free_implicit_mr(struct mlx5_ib_mr *imr)
{
	struct ib_ucontext *ctx = imr->ibmr.pd->uobject->context;

	down_read(&ctx->umem_rwsem);
	rbt_ib_umem_for_each_in_range(&ctx->umem_tree, 0, ULLONG_MAX,
				      mr_leaf_free, true, imr);
	up_read(&ctx->umem_rwsem);

	wait_event(imr->q_leaf_free, !atomic_read(&imr->num_leaf_free));
}