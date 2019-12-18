#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct ti_sci_intr_irq_domain {int /*<<< orphan*/  dst_irq; int /*<<< orphan*/  dst_id; TYPE_3__* sci; } ;
struct irq_domain {struct irq_domain* parent; struct ti_sci_intr_irq_domain* host_data; } ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* free_irq ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {TYPE_1__ rm_irq_ops; } ;
struct TYPE_6__ {TYPE_2__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  HWIRQ_TO_DEVID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HWIRQ_TO_IRQID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_free_irqs_parent (struct irq_domain*,unsigned int,int) ; 
 struct irq_data* irq_domain_get_irq_data (struct irq_domain*,unsigned int) ; 
 int /*<<< orphan*/  irq_domain_reset_irq_data (struct irq_data*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_sci_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ti_sci_intr_irq_domain_free(struct irq_domain *domain,
					unsigned int virq, unsigned int nr_irqs)
{
	struct ti_sci_intr_irq_domain *intr = domain->host_data;
	struct irq_data *data, *parent_data;
	u16 dev_id, irq_index;

	parent_data = irq_domain_get_irq_data(domain->parent, virq);
	data = irq_domain_get_irq_data(domain, virq);
	irq_index = HWIRQ_TO_IRQID(data->hwirq);
	dev_id = HWIRQ_TO_DEVID(data->hwirq);

	intr->sci->ops.rm_irq_ops.free_irq(intr->sci, dev_id, irq_index,
					   intr->dst_id, parent_data->hwirq);
	ti_sci_release_resource(intr->dst_irq, parent_data->hwirq);
	irq_domain_free_irqs_parent(domain, virq, 1);
	irq_domain_reset_irq_data(data);
}