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
struct mlx5_irq_table {int nvec; int /*<<< orphan*/  rmap; } ;
struct TYPE_2__ {struct mlx5_irq_table* irq_table; } ;
struct mlx5_core_dev {int /*<<< orphan*/  pdev; TYPE_1__ priv; } ;

/* Variables and functions */
 int ENOMEM ; 
 int MLX5_IRQ_VEC_COMP_BASE ; 
 int /*<<< orphan*/  alloc_irq_cpu_rmap (int) ; 
 int /*<<< orphan*/  irq_clear_rmap (struct mlx5_core_dev*) ; 
 int irq_cpu_rmap_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*,int) ; 
 int mlx5_irq_get_num_comp (struct mlx5_irq_table*) ; 
 int /*<<< orphan*/  pci_irq_vector (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int irq_set_rmap(struct mlx5_core_dev *mdev)
{
	int err = 0;
#ifdef CONFIG_RFS_ACCEL
	struct mlx5_irq_table *irq_table = mdev->priv.irq_table;
	int num_affinity_vec;
	int vecidx;

	num_affinity_vec = mlx5_irq_get_num_comp(irq_table);
	irq_table->rmap = alloc_irq_cpu_rmap(num_affinity_vec);
	if (!irq_table->rmap) {
		err = -ENOMEM;
		mlx5_core_err(mdev, "Failed to allocate cpu_rmap. err %d", err);
		goto err_out;
	}

	vecidx = MLX5_IRQ_VEC_COMP_BASE;
	for (; vecidx < irq_table->nvec; vecidx++) {
		err = irq_cpu_rmap_add(irq_table->rmap,
				       pci_irq_vector(mdev->pdev, vecidx));
		if (err) {
			mlx5_core_err(mdev, "irq_cpu_rmap_add failed. err %d",
				      err);
			goto err_irq_cpu_rmap_add;
		}
	}
	return 0;

err_irq_cpu_rmap_add:
	irq_clear_rmap(mdev);
err_out:
#endif
	return err;
}