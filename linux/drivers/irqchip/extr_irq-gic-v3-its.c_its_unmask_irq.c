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

/* Variables and functions */
 int /*<<< orphan*/  LPI_PROP_ENABLED ; 
 scalar_t__ irqd_is_forwarded_to_vcpu (struct irq_data*) ; 
 int /*<<< orphan*/  its_vlpi_set_doorbell (struct irq_data*,int) ; 
 int /*<<< orphan*/  lpi_update_config (struct irq_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void its_unmask_irq(struct irq_data *d)
{
	if (irqd_is_forwarded_to_vcpu(d))
		its_vlpi_set_doorbell(d, true);

	lpi_update_config(d, 0, LPI_PROP_ENABLED);
}