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
struct mlx5_eqe {int /*<<< orphan*/  owner; } ;
struct mlx5_eq {int nent; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_EQE_OWNER_INIT_VAL ; 
 struct mlx5_eqe* get_eqe (struct mlx5_eq*,int) ; 

__attribute__((used)) static void init_eq_buf(struct mlx5_eq *eq)
{
	struct mlx5_eqe *eqe;
	int i;

	for (i = 0; i < eq->nent; i++) {
		eqe = get_eqe(eq, i);
		eqe->owner = MLX5_EQE_OWNER_INIT_VAL;
	}
}