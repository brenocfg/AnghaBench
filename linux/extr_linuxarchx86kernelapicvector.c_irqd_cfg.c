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
struct irq_data {int dummy; } ;
struct irq_cfg {int dummy; } ;
struct apic_chip_data {struct irq_cfg hw_irq_cfg; } ;

/* Variables and functions */
 struct apic_chip_data* apic_chip_data (struct irq_data*) ; 

struct irq_cfg *irqd_cfg(struct irq_data *irqd)
{
	struct apic_chip_data *apicd = apic_chip_data(irqd);

	return apicd ? &apicd->hw_irq_cfg : NULL;
}