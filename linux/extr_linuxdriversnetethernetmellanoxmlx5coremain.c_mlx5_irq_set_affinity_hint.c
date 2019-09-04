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
struct mlx5_priv {TYPE_1__* irq_info; int /*<<< orphan*/  numa_node; } ;
struct mlx5_core_dev {int /*<<< orphan*/  pdev; struct mlx5_priv priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_SMP ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int MLX5_EQ_VEC_COMP_BASE ; 
 int /*<<< orphan*/  cpumask_local_spread (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ irq_set_affinity_hint (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,...) ; 
 int pci_irq_vector (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zalloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx5_irq_set_affinity_hint(struct mlx5_core_dev *mdev, int i)
{
	struct mlx5_priv *priv  = &mdev->priv;
	int vecidx = MLX5_EQ_VEC_COMP_BASE + i;
	int irq = pci_irq_vector(mdev->pdev, vecidx);

	if (!zalloc_cpumask_var(&priv->irq_info[vecidx].mask, GFP_KERNEL)) {
		mlx5_core_warn(mdev, "zalloc_cpumask_var failed");
		return -ENOMEM;
	}

	cpumask_set_cpu(cpumask_local_spread(i, priv->numa_node),
			priv->irq_info[vecidx].mask);

	if (IS_ENABLED(CONFIG_SMP) &&
	    irq_set_affinity_hint(irq, priv->irq_info[vecidx].mask))
		mlx5_core_warn(mdev, "irq_set_affinity_hint failed, irq 0x%.4x", irq);

	return 0;
}