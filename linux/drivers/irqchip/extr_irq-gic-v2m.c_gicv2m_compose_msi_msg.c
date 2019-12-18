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
struct v2m_data {int flags; scalar_t__ spi_offset; } ;
struct msi_msg {scalar_t__ data; int /*<<< orphan*/  address_lo; int /*<<< orphan*/  address_hi; } ;
struct irq_data {scalar_t__ hwirq; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int GICV2M_GRAVITON_ADDRESS_ONLY ; 
 int GICV2M_NEEDS_SPI_OFFSET ; 
 int /*<<< orphan*/  gicv2m_get_msi_addr (struct v2m_data*,scalar_t__) ; 
 int /*<<< orphan*/  iommu_dma_compose_msi_msg (int /*<<< orphan*/ ,struct msi_msg*) ; 
 struct v2m_data* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irq_data_get_msi_desc (struct irq_data*) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gicv2m_compose_msi_msg(struct irq_data *data, struct msi_msg *msg)
{
	struct v2m_data *v2m = irq_data_get_irq_chip_data(data);
	phys_addr_t addr = gicv2m_get_msi_addr(v2m, data->hwirq);

	msg->address_hi = upper_32_bits(addr);
	msg->address_lo = lower_32_bits(addr);

	if (v2m->flags & GICV2M_GRAVITON_ADDRESS_ONLY)
		msg->data = 0;
	else
		msg->data = data->hwirq;
	if (v2m->flags & GICV2M_NEEDS_SPI_OFFSET)
		msg->data -= v2m->spi_offset;

	iommu_dma_compose_msi_msg(irq_data_get_msi_desc(data), msg);
}