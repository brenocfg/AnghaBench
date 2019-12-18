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
struct mlx5_irq_table {int /*<<< orphan*/  rmap; } ;
struct TYPE_2__ {struct mlx5_irq_table* irq_table; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq_cpu_rmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void irq_clear_rmap(struct mlx5_core_dev *dev)
{
#ifdef CONFIG_RFS_ACCEL
	struct mlx5_irq_table *irq_table = dev->priv.irq_table;

	free_irq_cpu_rmap(irq_table->rmap);
#endif
}