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
struct TYPE_2__ {scalar_t__ start; } ;
struct v2m_data {int flags; scalar_t__ spi_offset; TYPE_1__ res; } ;
struct msi_msg {int /*<<< orphan*/  data; int /*<<< orphan*/  address_lo; int /*<<< orphan*/  address_hi; } ;
struct irq_data {int /*<<< orphan*/  irq; int /*<<< orphan*/  hwirq; } ;
typedef  scalar_t__ phys_addr_t ;

/* Variables and functions */
 int GICV2M_NEEDS_SPI_OFFSET ; 
 scalar_t__ V2M_MSI_SETSPI_NS ; 
 int /*<<< orphan*/  iommu_dma_map_msi_msg (int /*<<< orphan*/ ,struct msi_msg*) ; 
 struct v2m_data* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  lower_32_bits (scalar_t__) ; 
 int /*<<< orphan*/  upper_32_bits (scalar_t__) ; 

__attribute__((used)) static void gicv2m_compose_msi_msg(struct irq_data *data, struct msi_msg *msg)
{
	struct v2m_data *v2m = irq_data_get_irq_chip_data(data);
	phys_addr_t addr = v2m->res.start + V2M_MSI_SETSPI_NS;

	msg->address_hi = upper_32_bits(addr);
	msg->address_lo = lower_32_bits(addr);
	msg->data = data->hwirq;

	if (v2m->flags & GICV2M_NEEDS_SPI_OFFSET)
		msg->data -= v2m->spi_offset;

	iommu_dma_map_msi_msg(data->irq, msg);
}