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
struct mlx5e_params {scalar_t__ num_channels; } ;
struct mlx5e_channel {int ix; int /*<<< orphan*/  xps_cpumask; int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int cpumask_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_comp_irq_get_affinity_mask (int /*<<< orphan*/ ,int) ; 
 int mlx5_comp_vectors_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zalloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx5e_alloc_xps_cpumask(struct mlx5e_channel *c,
				   struct mlx5e_params *params)
{
	int num_comp_vectors = mlx5_comp_vectors_count(c->mdev);
	int irq;

	if (!zalloc_cpumask_var(&c->xps_cpumask, GFP_KERNEL))
		return -ENOMEM;

	for (irq = c->ix; irq < num_comp_vectors; irq += params->num_channels) {
		int cpu = cpumask_first(mlx5_comp_irq_get_affinity_mask(c->mdev, irq));

		cpumask_set_cpu(cpu, c->xps_cpumask);
	}

	return 0;
}