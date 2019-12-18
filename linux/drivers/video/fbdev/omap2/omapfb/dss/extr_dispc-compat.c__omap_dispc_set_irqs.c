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
typedef  int /*<<< orphan*/  u32 ;
struct omap_dispc_isr_data {int /*<<< orphan*/  mask; int /*<<< orphan*/ * isr; } ;
struct TYPE_2__ {struct omap_dispc_isr_data* registered_isr; int /*<<< orphan*/  irq_error_mask; } ;

/* Variables and functions */
 int DISPC_MAX_NR_ISRS ; 
 TYPE_1__ dispc_compat ; 
 int /*<<< orphan*/  dispc_write_irqenable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _omap_dispc_set_irqs(void)
{
	u32 mask;
	int i;
	struct omap_dispc_isr_data *isr_data;

	mask = dispc_compat.irq_error_mask;

	for (i = 0; i < DISPC_MAX_NR_ISRS; i++) {
		isr_data = &dispc_compat.registered_isr[i];

		if (isr_data->isr == NULL)
			continue;

		mask |= isr_data->mask;
	}

	dispc_write_irqenable(mask);
}