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
struct notifier_block {int dummy; } ;
struct mlx5_irq_table {struct mlx5_irq* irq; } ;
struct mlx5_irq {int /*<<< orphan*/  nh; } ;

/* Variables and functions */
 int atomic_notifier_chain_register (int /*<<< orphan*/ *,struct notifier_block*) ; 

int mlx5_irq_attach_nb(struct mlx5_irq_table *irq_table, int vecidx,
		       struct notifier_block *nb)
{
	struct mlx5_irq *irq;

	irq = &irq_table->irq[vecidx];
	return atomic_notifier_chain_register(&irq->nh, nb);
}