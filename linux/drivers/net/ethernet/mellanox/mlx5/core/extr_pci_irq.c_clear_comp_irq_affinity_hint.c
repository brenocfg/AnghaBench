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
struct mlx5_irq {int /*<<< orphan*/  mask; } ;
struct mlx5_core_dev {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int MLX5_IRQ_VEC_COMP_BASE ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int,int /*<<< orphan*/ *) ; 
 struct mlx5_irq* mlx5_irq_get (struct mlx5_core_dev*,int) ; 
 int pci_irq_vector (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void clear_comp_irq_affinity_hint(struct mlx5_core_dev *mdev, int i)
{
	int vecidx = MLX5_IRQ_VEC_COMP_BASE + i;
	struct mlx5_irq *irq;
	int irqn;

	irq = mlx5_irq_get(mdev, vecidx);
	irqn = pci_irq_vector(mdev->pdev, vecidx);
	irq_set_affinity_hint(irqn, NULL);
	free_cpumask_var(irq->mask);
}