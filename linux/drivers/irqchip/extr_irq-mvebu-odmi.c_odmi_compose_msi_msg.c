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
struct odmi_data {TYPE_1__ res; } ;
struct msi_msg {unsigned int data; int /*<<< orphan*/  address_lo; int /*<<< orphan*/  address_hi; } ;
struct irq_data {int hwirq; } ;
typedef  scalar_t__ phys_addr_t ;

/* Variables and functions */
 scalar_t__ GICP_ODMIN_SET ; 
 unsigned int GICP_ODMI_INT_NUM_SHIFT ; 
 unsigned int NODMIS_MASK ; 
 int NODMIS_PER_FRAME ; 
 size_t NODMIS_SHIFT ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  lower_32_bits (scalar_t__) ; 
 struct odmi_data* odmis ; 
 int odmis_count ; 
 int /*<<< orphan*/  upper_32_bits (scalar_t__) ; 

__attribute__((used)) static void odmi_compose_msi_msg(struct irq_data *d, struct msi_msg *msg)
{
	struct odmi_data *odmi;
	phys_addr_t addr;
	unsigned int odmin;

	if (WARN_ON(d->hwirq >= odmis_count * NODMIS_PER_FRAME))
		return;

	odmi = &odmis[d->hwirq >> NODMIS_SHIFT];
	odmin = d->hwirq & NODMIS_MASK;

	addr = odmi->res.start + GICP_ODMIN_SET;

	msg->address_hi = upper_32_bits(addr);
	msg->address_lo = lower_32_bits(addr);
	msg->data = odmin << GICP_ODMI_INT_NUM_SHIFT;
}