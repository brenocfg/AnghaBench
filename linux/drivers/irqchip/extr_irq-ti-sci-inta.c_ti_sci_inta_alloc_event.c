#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct ti_sci_inta_vint_desc {int /*<<< orphan*/  vint_id; struct ti_sci_inta_event_desc* events; TYPE_1__* domain; } ;
struct ti_sci_inta_irq_domain {int /*<<< orphan*/  global_event; TYPE_4__* pdev; TYPE_5__* sci; } ;
struct ti_sci_inta_event_desc {size_t vint_bit; scalar_t__ global_event; int /*<<< orphan*/  hwirq; } ;
struct TYPE_7__ {int (* set_event_map ) (TYPE_5__*,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,size_t) ;} ;
struct TYPE_8__ {TYPE_2__ rm_irq_ops; } ;
struct TYPE_10__ {TYPE_3__ ops; } ;
struct TYPE_9__ {int /*<<< orphan*/  id; } ;
struct TYPE_6__ {struct ti_sci_inta_irq_domain* host_data; } ;

/* Variables and functions */
 int EINVAL ; 
 struct ti_sci_inta_event_desc* ERR_PTR (int) ; 
 size_t HWIRQ_TO_DEVID (int /*<<< orphan*/ ) ; 
 size_t HWIRQ_TO_IRQID (int /*<<< orphan*/ ) ; 
 scalar_t__ TI_SCI_RESOURCE_NULL ; 
 int stub1 (TYPE_5__*,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,size_t) ; 
 scalar_t__ ti_sci_get_free_resource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_sci_release_resource (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static struct ti_sci_inta_event_desc *ti_sci_inta_alloc_event(struct ti_sci_inta_vint_desc *vint_desc,
							      u16 free_bit,
							      u32 hwirq)
{
	struct ti_sci_inta_irq_domain *inta = vint_desc->domain->host_data;
	struct ti_sci_inta_event_desc *event_desc;
	u16 dev_id, dev_index;
	int err;

	dev_id = HWIRQ_TO_DEVID(hwirq);
	dev_index = HWIRQ_TO_IRQID(hwirq);

	event_desc = &vint_desc->events[free_bit];
	event_desc->hwirq = hwirq;
	event_desc->vint_bit = free_bit;
	event_desc->global_event = ti_sci_get_free_resource(inta->global_event);
	if (event_desc->global_event == TI_SCI_RESOURCE_NULL)
		return ERR_PTR(-EINVAL);

	err = inta->sci->ops.rm_irq_ops.set_event_map(inta->sci,
						      dev_id, dev_index,
						      inta->pdev->id,
						      vint_desc->vint_id,
						      event_desc->global_event,
						      free_bit);
	if (err)
		goto free_global_event;

	return event_desc;
free_global_event:
	ti_sci_release_resource(inta->global_event, event_desc->global_event);
	return ERR_PTR(err);
}