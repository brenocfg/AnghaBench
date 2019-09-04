#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct its_vm {unsigned long* db_bitmap; int db_lpi_base; int nr_db_lpis; TYPE_1__** vpes; struct page* vprop_page; } ;
struct irq_domain {int dummy; } ;
struct TYPE_3__ {int vpe_db_lpi; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  irq_domain_set_hwirq_and_chip (struct irq_domain*,unsigned int,int,int /*<<< orphan*/ *,TYPE_1__*) ; 
 struct page* its_allocate_prop_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_free_prop_table (struct page*) ; 
 int its_irq_gic_domain_alloc (struct irq_domain*,unsigned int,int) ; 
 unsigned long* its_lpi_alloc (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  its_lpi_free (unsigned long*,int,int) ; 
 int its_vpe_init (TYPE_1__*) ; 
 int /*<<< orphan*/  its_vpe_irq_chip ; 
 int /*<<< orphan*/  its_vpe_irq_domain_free (struct irq_domain*,unsigned int,int) ; 
 int /*<<< orphan*/  roundup_pow_of_two (unsigned int) ; 
 int /*<<< orphan*/  set_bit (int,unsigned long*) ; 

__attribute__((used)) static int its_vpe_irq_domain_alloc(struct irq_domain *domain, unsigned int virq,
				    unsigned int nr_irqs, void *args)
{
	struct its_vm *vm = args;
	unsigned long *bitmap;
	struct page *vprop_page;
	int base, nr_ids, i, err = 0;

	BUG_ON(!vm);

	bitmap = its_lpi_alloc(roundup_pow_of_two(nr_irqs), &base, &nr_ids);
	if (!bitmap)
		return -ENOMEM;

	if (nr_ids < nr_irqs) {
		its_lpi_free(bitmap, base, nr_ids);
		return -ENOMEM;
	}

	vprop_page = its_allocate_prop_table(GFP_KERNEL);
	if (!vprop_page) {
		its_lpi_free(bitmap, base, nr_ids);
		return -ENOMEM;
	}

	vm->db_bitmap = bitmap;
	vm->db_lpi_base = base;
	vm->nr_db_lpis = nr_ids;
	vm->vprop_page = vprop_page;

	for (i = 0; i < nr_irqs; i++) {
		vm->vpes[i]->vpe_db_lpi = base + i;
		err = its_vpe_init(vm->vpes[i]);
		if (err)
			break;
		err = its_irq_gic_domain_alloc(domain, virq + i,
					       vm->vpes[i]->vpe_db_lpi);
		if (err)
			break;
		irq_domain_set_hwirq_and_chip(domain, virq + i, i,
					      &its_vpe_irq_chip, vm->vpes[i]);
		set_bit(i, bitmap);
	}

	if (err) {
		if (i > 0)
			its_vpe_irq_domain_free(domain, virq, i - 1);

		its_lpi_free(bitmap, base, nr_ids);
		its_free_prop_table(vprop_page);
	}

	return err;
}