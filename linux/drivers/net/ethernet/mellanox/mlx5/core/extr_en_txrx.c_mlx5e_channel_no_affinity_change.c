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
struct mlx5e_channel {int /*<<< orphan*/  irq_desc; } ;
struct irq_data {int dummy; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 int cpumask_test_cpu (int,struct cpumask const*) ; 
 struct cpumask* irq_data_get_affinity_mask (struct irq_data*) ; 
 struct irq_data* irq_desc_get_irq_data (int /*<<< orphan*/ ) ; 
 int smp_processor_id () ; 

__attribute__((used)) static inline bool mlx5e_channel_no_affinity_change(struct mlx5e_channel *c)
{
	int current_cpu = smp_processor_id();
	const struct cpumask *aff;
	struct irq_data *idata;

	idata = irq_desc_get_irq_data(c->irq_desc);
	aff = irq_data_get_affinity_mask(idata);
	return cpumask_test_cpu(current_cpu, aff);
}