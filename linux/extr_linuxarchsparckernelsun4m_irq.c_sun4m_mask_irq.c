#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sun4m_handler_data {scalar_t__ mask; scalar_t__ percpu; } ;
struct irq_data {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  mask_set; } ;
struct TYPE_3__ {int /*<<< orphan*/  set; } ;

/* Variables and functions */
 struct sun4m_handler_data* irq_data_get_irq_handler_data (struct irq_data*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  sbus_writel (scalar_t__,int /*<<< orphan*/ *) ; 
 int smp_processor_id () ; 
 TYPE_2__* sun4m_irq_global ; 
 TYPE_1__** sun4m_irq_percpu ; 

__attribute__((used)) static void sun4m_mask_irq(struct irq_data *data)
{
	struct sun4m_handler_data *handler_data;
	int cpu = smp_processor_id();

	handler_data = irq_data_get_irq_handler_data(data);
	if (handler_data->mask) {
		unsigned long flags;

		local_irq_save(flags);
		if (handler_data->percpu) {
			sbus_writel(handler_data->mask, &sun4m_irq_percpu[cpu]->set);
		} else {
			sbus_writel(handler_data->mask, &sun4m_irq_global->mask_set);
		}
		local_irq_restore(flags);
	}
}