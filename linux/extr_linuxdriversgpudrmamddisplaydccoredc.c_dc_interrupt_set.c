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
struct dc {TYPE_1__* res_pool; } ;
typedef  enum dc_irq_source { ____Placeholder_dc_irq_source } dc_irq_source ;
struct TYPE_2__ {int /*<<< orphan*/  irqs; } ;

/* Variables and functions */
 int dal_irq_service_set (int /*<<< orphan*/ ,int,int) ; 

bool dc_interrupt_set(struct dc *dc, enum dc_irq_source src, bool enable)
{

	if (dc == NULL)
		return false;

	return dal_irq_service_set(dc->res_pool->irqs, src, enable);
}