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
struct irq_domain {int dummy; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_ir_reconfigure_irte (struct irq_data*,int) ; 

__attribute__((used)) static int intel_irq_remapping_activate(struct irq_domain *domain,
					struct irq_data *irq_data, bool reserve)
{
	intel_ir_reconfigure_irte(irq_data, true);
	return 0;
}