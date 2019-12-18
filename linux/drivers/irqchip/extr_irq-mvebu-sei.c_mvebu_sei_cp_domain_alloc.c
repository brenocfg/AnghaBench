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
struct mvebu_sei {TYPE_3__* caps; int /*<<< orphan*/  cp_msi_lock; int /*<<< orphan*/  cp_msi_bitmap; } ;
struct irq_fwspec {int param_count; scalar_t__* param; int /*<<< orphan*/  fwnode; } ;
struct irq_domain {TYPE_1__* parent; struct mvebu_sei* host_data; } ;
struct TYPE_5__ {unsigned long size; scalar_t__ first; } ;
struct TYPE_6__ {TYPE_2__ cp_range; } ;
struct TYPE_4__ {int /*<<< orphan*/  fwnode; } ;

/* Variables and functions */
 int ENOSPC ; 
 int ENOTSUPP ; 
 unsigned long find_first_zero_bit (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int irq_domain_alloc_irqs_parent (struct irq_domain*,unsigned int,int,struct irq_fwspec*) ; 
 int /*<<< orphan*/  irq_domain_set_info (struct irq_domain*,unsigned int,unsigned long,int /*<<< orphan*/ *,struct mvebu_sei*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mvebu_sei_cp_irq_chip ; 
 int /*<<< orphan*/  mvebu_sei_cp_release_irq (struct mvebu_sei*,unsigned long) ; 
 int /*<<< orphan*/  set_bit (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mvebu_sei_cp_domain_alloc(struct irq_domain *domain,
				     unsigned int virq, unsigned int nr_irqs,
				     void *args)
{
	struct mvebu_sei *sei = domain->host_data;
	struct irq_fwspec fwspec;
	unsigned long hwirq;
	int ret;

	/* The software only supports single allocations for now */
	if (nr_irqs != 1)
		return -ENOTSUPP;

	mutex_lock(&sei->cp_msi_lock);
	hwirq = find_first_zero_bit(sei->cp_msi_bitmap,
				    sei->caps->cp_range.size);
	if (hwirq < sei->caps->cp_range.size)
		set_bit(hwirq, sei->cp_msi_bitmap);
	mutex_unlock(&sei->cp_msi_lock);

	if (hwirq == sei->caps->cp_range.size)
		return -ENOSPC;

	fwspec.fwnode = domain->parent->fwnode;
	fwspec.param_count = 1;
	fwspec.param[0] = hwirq + sei->caps->cp_range.first;

	ret = irq_domain_alloc_irqs_parent(domain, virq, 1, &fwspec);
	if (ret)
		goto free_irq;

	irq_domain_set_info(domain, virq, hwirq,
			    &mvebu_sei_cp_irq_chip, sei,
			    handle_edge_irq, NULL, NULL);

	return 0;

free_irq:
	mvebu_sei_cp_release_irq(sei, hwirq);
	return ret;
}