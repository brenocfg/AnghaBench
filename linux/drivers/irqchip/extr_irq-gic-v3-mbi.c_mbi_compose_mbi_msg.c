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
struct msi_msg {int /*<<< orphan*/  data; int /*<<< orphan*/  address_lo; int /*<<< orphan*/  address_hi; } ;
struct irq_data {TYPE_1__* parent_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  hwirq; } ;

/* Variables and functions */
 scalar_t__ GICD_CLRSPI_NSR ; 
 int /*<<< orphan*/  iommu_dma_compose_msi_msg (int /*<<< orphan*/ ,struct msi_msg*) ; 
 int /*<<< orphan*/  irq_data_get_msi_desc (struct irq_data*) ; 
 int /*<<< orphan*/  lower_32_bits (scalar_t__) ; 
 int /*<<< orphan*/  mbi_compose_msi_msg (struct irq_data*,struct msi_msg*) ; 
 scalar_t__ mbi_phys_base ; 
 int /*<<< orphan*/  upper_32_bits (scalar_t__) ; 

__attribute__((used)) static void mbi_compose_mbi_msg(struct irq_data *data, struct msi_msg *msg)
{
	mbi_compose_msi_msg(data, msg);

	msg[1].address_hi = upper_32_bits(mbi_phys_base + GICD_CLRSPI_NSR);
	msg[1].address_lo = lower_32_bits(mbi_phys_base + GICD_CLRSPI_NSR);
	msg[1].data = data->parent_data->hwirq;

	iommu_dma_compose_msi_msg(irq_data_get_msi_desc(data), &msg[1]);
}