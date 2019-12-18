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
struct irq_data {scalar_t__ hwirq; } ;
struct iproc_msi {int dummy; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 int IRQ_SET_MASK_OK ; 
 int IRQ_SET_MASK_OK_DONE ; 
 int cpumask_first (struct cpumask const*) ; 
 scalar_t__ hwirq_to_canonical_hwirq (struct iproc_msi*,scalar_t__) ; 
 int hwirq_to_cpu (struct iproc_msi*,scalar_t__) ; 
 struct iproc_msi* irq_data_get_irq_chip_data (struct irq_data*) ; 

__attribute__((used)) static int iproc_msi_irq_set_affinity(struct irq_data *data,
				      const struct cpumask *mask, bool force)
{
	struct iproc_msi *msi = irq_data_get_irq_chip_data(data);
	int target_cpu = cpumask_first(mask);
	int curr_cpu;

	curr_cpu = hwirq_to_cpu(msi, data->hwirq);
	if (curr_cpu == target_cpu)
		return IRQ_SET_MASK_OK_DONE;

	/* steer MSI to the target CPU */
	data->hwirq = hwirq_to_canonical_hwirq(msi, data->hwirq) + target_cpu;

	return IRQ_SET_MASK_OK;
}