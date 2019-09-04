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
typedef  scalar_t__ u32 ;
struct mlx5_eq {int /*<<< orphan*/  irqn; scalar_t__ cons_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_eq_int (int /*<<< orphan*/ ,struct mlx5_eq*) ; 

u32 mlx5_eq_poll_irq_disabled(struct mlx5_eq *eq)
{
	u32 count_eqe;

	disable_irq(eq->irqn);
	count_eqe = eq->cons_index;
	mlx5_eq_int(eq->irqn, eq);
	count_eqe = eq->cons_index - count_eqe;
	enable_irq(eq->irqn);

	return count_eqe;
}