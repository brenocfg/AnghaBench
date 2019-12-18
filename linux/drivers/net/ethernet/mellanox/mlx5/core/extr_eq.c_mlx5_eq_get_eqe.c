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
typedef  int u32 ;
struct mlx5_eqe {int owner; } ;
struct mlx5_eq {int cons_index; int nent; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_rmb () ; 
 struct mlx5_eqe* get_eqe (struct mlx5_eq*,int) ; 

struct mlx5_eqe *mlx5_eq_get_eqe(struct mlx5_eq *eq, u32 cc)
{
	u32 ci = eq->cons_index + cc;
	struct mlx5_eqe *eqe;

	eqe = get_eqe(eq, ci & (eq->nent - 1));
	eqe = ((eqe->owner & 1) ^ !!(ci & eq->nent)) ? NULL : eqe;
	/* Make sure we read EQ entry contents after we've
	 * checked the ownership bit.
	 */
	if (eqe)
		dma_rmb();

	return eqe;
}