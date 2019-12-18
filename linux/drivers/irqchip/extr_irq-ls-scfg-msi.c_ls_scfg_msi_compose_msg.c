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
struct msi_msg {int /*<<< orphan*/  data; int /*<<< orphan*/  address_lo; int /*<<< orphan*/  address_hi; } ;
struct ls_scfg_msi {int /*<<< orphan*/  msiir_addr; } ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpumask_first (struct cpumask const*) ; 
 int /*<<< orphan*/  iommu_dma_compose_msi_msg (int /*<<< orphan*/ ,struct msi_msg*) ; 
 struct cpumask* irq_data_get_effective_affinity_mask (struct irq_data*) ; 
 struct ls_scfg_msi* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irq_data_get_msi_desc (struct irq_data*) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 scalar_t__ msi_affinity_flag ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ls_scfg_msi_compose_msg(struct irq_data *data, struct msi_msg *msg)
{
	struct ls_scfg_msi *msi_data = irq_data_get_irq_chip_data(data);

	msg->address_hi = upper_32_bits(msi_data->msiir_addr);
	msg->address_lo = lower_32_bits(msi_data->msiir_addr);
	msg->data = data->hwirq;

	if (msi_affinity_flag) {
		const struct cpumask *mask;

		mask = irq_data_get_effective_affinity_mask(data);
		msg->data |= cpumask_first(mask);
	}

	iommu_dma_compose_msi_msg(irq_data_get_msi_desc(data), msg);
}