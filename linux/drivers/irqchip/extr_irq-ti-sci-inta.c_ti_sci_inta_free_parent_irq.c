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
struct ti_sci_inta_vint_desc {int /*<<< orphan*/  parent_virq; int /*<<< orphan*/  vint_id; int /*<<< orphan*/  list; int /*<<< orphan*/  event_map; } ;
struct ti_sci_inta_irq_domain {int /*<<< orphan*/  vint; } ;

/* Variables and functions */
 scalar_t__ MAX_EVENTS_PER_VINT ; 
 scalar_t__ find_first_bit (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  irq_dispose_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ti_sci_inta_vint_desc*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ti_sci_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ti_sci_inta_free_parent_irq(struct ti_sci_inta_irq_domain *inta,
					struct ti_sci_inta_vint_desc *vint_desc)
{
	if (find_first_bit(vint_desc->event_map, MAX_EVENTS_PER_VINT) == MAX_EVENTS_PER_VINT) {
		list_del(&vint_desc->list);
		ti_sci_release_resource(inta->vint, vint_desc->vint_id);
		irq_dispose_mapping(vint_desc->parent_virq);
		kfree(vint_desc);
	}
}