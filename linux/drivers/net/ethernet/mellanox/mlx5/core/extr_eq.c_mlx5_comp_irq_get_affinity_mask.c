#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* eq_table; } ;
struct mlx5_core_dev {TYPE_2__ priv; } ;
struct cpumask {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq_table; } ;

/* Variables and functions */
 int MLX5_IRQ_VEC_COMP_BASE ; 
 struct cpumask* mlx5_irq_get_affinity_mask (int /*<<< orphan*/ ,int) ; 

struct cpumask *
mlx5_comp_irq_get_affinity_mask(struct mlx5_core_dev *dev, int vector)
{
	int vecidx = vector + MLX5_IRQ_VEC_COMP_BASE;

	return mlx5_irq_get_affinity_mask(dev->priv.eq_table->irq_table,
					  vecidx);
}