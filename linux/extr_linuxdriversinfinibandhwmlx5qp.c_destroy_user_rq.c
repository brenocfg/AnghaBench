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
struct mlx5_ib_ucontext {int dummy; } ;
struct mlx5_ib_rwq {int create_flags; scalar_t__ umem; int /*<<< orphan*/  db; } ;
struct TYPE_3__ {int /*<<< orphan*/  rqs_cnt; } ;
struct mlx5_ib_dev {TYPE_1__ delay_drop; } ;
struct ib_pd {TYPE_2__* uobject; } ;
struct TYPE_4__ {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int MLX5_IB_WQ_FLAGS_DELAY_DROP ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_umem_release (scalar_t__) ; 
 int /*<<< orphan*/  mlx5_ib_db_unmap_user (struct mlx5_ib_ucontext*,int /*<<< orphan*/ *) ; 
 struct mlx5_ib_ucontext* to_mucontext (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void destroy_user_rq(struct mlx5_ib_dev *dev, struct ib_pd *pd,
			    struct mlx5_ib_rwq *rwq)
{
	struct mlx5_ib_ucontext *context;

	if (rwq->create_flags & MLX5_IB_WQ_FLAGS_DELAY_DROP)
		atomic_dec(&dev->delay_drop.rqs_cnt);

	context = to_mucontext(pd->uobject->context);
	mlx5_ib_db_unmap_user(context, &rwq->db);
	if (rwq->umem)
		ib_umem_release(rwq->umem);
}