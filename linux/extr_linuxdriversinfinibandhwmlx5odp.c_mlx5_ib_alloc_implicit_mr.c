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
struct TYPE_4__ {TYPE_1__* uobject; } ;
struct mlx5_ib_pd {TYPE_2__ ibpd; } ;
struct mlx5_ib_mr {int /*<<< orphan*/  num_leaf_free; int /*<<< orphan*/  q_leaf_free; struct mlx5_ib_mr* umem; } ;
struct ib_umem {int /*<<< orphan*/  num_leaf_free; int /*<<< orphan*/  q_leaf_free; struct ib_umem* umem; } ;
struct ib_ucontext {int dummy; } ;
struct TYPE_3__ {struct ib_ucontext* context; } ;

/* Variables and functions */
 struct mlx5_ib_mr* ERR_CAST (struct mlx5_ib_mr*) ; 
 int /*<<< orphan*/  IB_ACCESS_ON_DEMAND ; 
 scalar_t__ IS_ERR (struct mlx5_ib_mr*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mlx5_ib_mr* ib_umem_get (struct ib_ucontext*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_umem_release (struct mlx5_ib_mr*) ; 
 struct mlx5_ib_mr* implicit_mr_alloc (TYPE_2__*,struct mlx5_ib_mr*,int,int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 

struct mlx5_ib_mr *mlx5_ib_alloc_implicit_mr(struct mlx5_ib_pd *pd,
					     int access_flags)
{
	struct ib_ucontext *ctx = pd->ibpd.uobject->context;
	struct mlx5_ib_mr *imr;
	struct ib_umem *umem;

	umem = ib_umem_get(ctx, 0, 0, IB_ACCESS_ON_DEMAND, 0);
	if (IS_ERR(umem))
		return ERR_CAST(umem);

	imr = implicit_mr_alloc(&pd->ibpd, umem, 1, access_flags);
	if (IS_ERR(imr)) {
		ib_umem_release(umem);
		return ERR_CAST(imr);
	}

	imr->umem = umem;
	init_waitqueue_head(&imr->q_leaf_free);
	atomic_set(&imr->num_leaf_free, 0);

	return imr;
}