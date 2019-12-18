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
struct mlx5_irq_table {TYPE_1__* irq; } ;
struct cpumask {int dummy; } ;
struct TYPE_2__ {struct cpumask* mask; } ;

/* Variables and functions */

struct cpumask *
mlx5_irq_get_affinity_mask(struct mlx5_irq_table *irq_table, int vecidx)
{
	return irq_table->irq[vecidx].mask;
}