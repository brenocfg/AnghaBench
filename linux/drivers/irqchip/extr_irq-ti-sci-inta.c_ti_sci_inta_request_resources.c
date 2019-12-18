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
struct irq_data {struct ti_sci_inta_event_desc* chip_data; int /*<<< orphan*/  hwirq; int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ti_sci_inta_event_desc*) ; 
 int PTR_ERR (struct ti_sci_inta_event_desc*) ; 
 struct ti_sci_inta_event_desc* ti_sci_inta_alloc_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ti_sci_inta_request_resources(struct irq_data *data)
{
	struct ti_sci_inta_event_desc *event_desc;

	event_desc = ti_sci_inta_alloc_irq(data->domain, data->hwirq);
	if (IS_ERR(event_desc))
		return PTR_ERR(event_desc);

	data->chip_data = event_desc;

	return 0;
}