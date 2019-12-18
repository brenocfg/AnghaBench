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
struct mlx5_ib_mr {int /*<<< orphan*/  umem; } ;
struct ib_ucontext_per_mm {int dummy; } ;
struct TYPE_2__ {struct ib_ucontext_per_mm* per_mm; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  is_odp_mr (struct mlx5_ib_mr*) ; 
 TYPE_1__* to_ib_umem_odp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ib_ucontext_per_mm *mr_to_per_mm(struct mlx5_ib_mr *mr)
{
	if (WARN_ON(!mr || !is_odp_mr(mr)))
		return NULL;

	return to_ib_umem_odp(mr->umem)->per_mm;
}