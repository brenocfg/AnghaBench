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
struct mlx5_ib_ucontext {int /*<<< orphan*/  bfregi; } ;
struct TYPE_4__ {scalar_t__ umem; } ;
struct mlx5_ib_qp_base {TYPE_2__ ubuffer; } ;
struct mlx5_ib_qp {int /*<<< orphan*/  bfregn; int /*<<< orphan*/  db; } ;
struct mlx5_ib_dev {int dummy; } ;
struct ib_pd {TYPE_1__* uobject; } ;
struct TYPE_3__ {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_IB_INVALID_BFREG ; 
 int /*<<< orphan*/  ib_umem_release (scalar_t__) ; 
 int /*<<< orphan*/  mlx5_ib_db_unmap_user (struct mlx5_ib_ucontext*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_ib_free_bfreg (struct mlx5_ib_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mlx5_ib_ucontext* to_mucontext (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void destroy_qp_user(struct mlx5_ib_dev *dev, struct ib_pd *pd,
			    struct mlx5_ib_qp *qp, struct mlx5_ib_qp_base *base)
{
	struct mlx5_ib_ucontext *context;

	context = to_mucontext(pd->uobject->context);
	mlx5_ib_db_unmap_user(context, &qp->db);
	if (base->ubuffer.umem)
		ib_umem_release(base->ubuffer.umem);

	/*
	 * Free only the BFREGs which are handled by the kernel.
	 * BFREGs of UARs allocated dynamically are handled by user.
	 */
	if (qp->bfregn != MLX5_IB_INVALID_BFREG)
		mlx5_ib_free_bfreg(dev, &context->bfregi, qp->bfregn);
}