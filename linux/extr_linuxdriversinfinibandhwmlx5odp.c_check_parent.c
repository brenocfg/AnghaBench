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
struct mlx5_ib_mr {struct mlx5_ib_mr* parent; } ;
struct ib_umem_odp {int /*<<< orphan*/  dying; struct mlx5_ib_mr* private; } ;

/* Variables and functions */

__attribute__((used)) static int check_parent(struct ib_umem_odp *odp,
			       struct mlx5_ib_mr *parent)
{
	struct mlx5_ib_mr *mr = odp->private;

	return mr && mr->parent == parent && !odp->dying;
}