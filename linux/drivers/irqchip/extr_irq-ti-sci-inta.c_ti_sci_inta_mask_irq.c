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
 int /*<<< orphan*/  VINT_ENABLE_CLR_OFFSET ; 
 int /*<<< orphan*/  ti_sci_inta_manage_event (struct irq_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ti_sci_inta_mask_irq(struct irq_data *data)
{
	ti_sci_inta_manage_event(data, VINT_ENABLE_CLR_OFFSET);
}