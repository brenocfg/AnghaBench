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
struct partition_desc {TYPE_2__* parts; int /*<<< orphan*/  chained_desc; int /*<<< orphan*/  bitmap; } ;
struct irq_fwspec {int dummy; } ;
struct irq_domain {struct partition_desc* host_data; TYPE_1__* ops; } ;
typedef  size_t irq_hw_number_t ;
struct TYPE_4__ {int /*<<< orphan*/  mask; } ;
struct TYPE_3__ {int (* translate ) (struct irq_domain*,struct irq_fwspec*,size_t*,unsigned int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  IRQ_NOAUTOEN ; 
 int /*<<< orphan*/  handle_percpu_devid_irq ; 
 int /*<<< orphan*/  irq_desc_get_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_set_info (struct irq_domain*,unsigned int,size_t,int /*<<< orphan*/ *,struct partition_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_chained_handler_and_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct partition_desc*) ; 
 int /*<<< orphan*/  irq_set_percpu_devid_partition (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_status_flags (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  partition_handle_irq ; 
 int /*<<< orphan*/  partition_irq_chip ; 
 int /*<<< orphan*/  set_bit (size_t,int /*<<< orphan*/ ) ; 
 int stub1 (struct irq_domain*,struct irq_fwspec*,size_t*,unsigned int*) ; 

__attribute__((used)) static int partition_domain_alloc(struct irq_domain *domain, unsigned int virq,
				  unsigned int nr_irqs, void *arg)
{
	int ret;
	irq_hw_number_t hwirq;
	unsigned int type;
	struct irq_fwspec *fwspec = arg;
	struct partition_desc *part;

	BUG_ON(nr_irqs != 1);
	ret = domain->ops->translate(domain, fwspec, &hwirq, &type);
	if (ret)
		return ret;

	part = domain->host_data;

	set_bit(hwirq, part->bitmap);
	irq_set_chained_handler_and_data(irq_desc_get_irq(part->chained_desc),
					 partition_handle_irq, part);
	irq_set_percpu_devid_partition(virq, &part->parts[hwirq].mask);
	irq_domain_set_info(domain, virq, hwirq, &partition_irq_chip, part,
			    handle_percpu_devid_irq, NULL, NULL);
	irq_set_status_flags(virq, IRQ_NOAUTOEN);

	return 0;
}