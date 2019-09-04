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
struct uv_IO_APIC_route_entry {int mask; } ;
struct irq_domain {int dummy; } ;
struct irq_data {int /*<<< orphan*/  chip_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  irqd_cfg (struct irq_data*) ; 
 int /*<<< orphan*/  uv_program_mmr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uv_domain_deactivate(struct irq_domain *domain,
				 struct irq_data *irq_data)
{
	unsigned long mmr_value;
	struct uv_IO_APIC_route_entry *entry;

	mmr_value = 0;
	entry = (struct uv_IO_APIC_route_entry *)&mmr_value;
	entry->mask = 1;
	uv_program_mmr(irqd_cfg(irq_data), irq_data->chip_data);
}