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
struct msi_msg {scalar_t__ data; int /*<<< orphan*/  address_lo; int /*<<< orphan*/  address_hi; } ;
struct irq_data {int hwirq; } ;
struct alpine_msix_data {int addr; } ;
typedef  int phys_addr_t ;

/* Variables and functions */
 struct alpine_msix_data* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  lower_32_bits (int) ; 
 int /*<<< orphan*/  upper_32_bits (int) ; 

__attribute__((used)) static void alpine_msix_compose_msi_msg(struct irq_data *data,
					struct msi_msg *msg)
{
	struct alpine_msix_data *priv = irq_data_get_irq_chip_data(data);
	phys_addr_t msg_addr = priv->addr;

	msg_addr |= (data->hwirq << 3);

	msg->address_hi = upper_32_bits(msg_addr);
	msg->address_lo = lower_32_bits(msg_addr);
	msg->data = 0;
}