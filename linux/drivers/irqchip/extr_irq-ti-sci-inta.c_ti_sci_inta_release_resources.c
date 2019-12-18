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
struct ti_sci_inta_event_desc {int dummy; } ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;

/* Variables and functions */
 struct ti_sci_inta_event_desc* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  ti_sci_inta_free_irq (struct ti_sci_inta_event_desc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ti_sci_inta_release_resources(struct irq_data *data)
{
	struct ti_sci_inta_event_desc *event_desc;

	event_desc = irq_data_get_irq_chip_data(data);
	ti_sci_inta_free_irq(event_desc, data->hwirq);
}