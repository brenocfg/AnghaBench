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
typedef  scalar_t__ u32 ;
struct ti_sci_inta_vint_desc {int vint_id; } ;
struct ti_sci_inta_irq_domain {scalar_t__ base; } ;
struct ti_sci_inta_event_desc {int /*<<< orphan*/  vint_bit; } ;
struct irq_data {TYPE_1__* domain; } ;
struct TYPE_2__ {struct ti_sci_inta_irq_domain* host_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 struct ti_sci_inta_event_desc* irq_data_get_irq_chip_data (struct irq_data*) ; 
 struct ti_sci_inta_vint_desc* to_vint_desc (struct ti_sci_inta_event_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeq_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ti_sci_inta_manage_event(struct irq_data *data, u32 offset)
{
	struct ti_sci_inta_event_desc *event_desc;
	struct ti_sci_inta_vint_desc *vint_desc;
	struct ti_sci_inta_irq_domain *inta;

	event_desc = irq_data_get_irq_chip_data(data);
	vint_desc = to_vint_desc(event_desc, event_desc->vint_bit);
	inta = data->domain->host_data;

	writeq_relaxed(BIT(event_desc->vint_bit),
		       inta->base + vint_desc->vint_id * 0x1000 + offset);
}