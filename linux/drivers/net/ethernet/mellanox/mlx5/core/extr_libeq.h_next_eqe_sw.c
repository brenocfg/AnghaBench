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
struct mlx5_eqe {int owner; } ;
struct mlx5_eq {int cons_index; int nent; } ;

/* Variables and functions */
 struct mlx5_eqe* get_eqe (struct mlx5_eq*,int) ; 

__attribute__((used)) static inline struct mlx5_eqe *next_eqe_sw(struct mlx5_eq *eq)
{
	struct mlx5_eqe *eqe = get_eqe(eq, eq->cons_index & (eq->nent - 1));

	return ((eqe->owner & 1) ^ !!(eq->cons_index & eq->nent)) ? NULL : eqe;
}