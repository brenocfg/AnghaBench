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
struct its_vm {int nr_vpes; scalar_t__ fwnode; scalar_t__ domain; TYPE_1__** vpes; } ;
struct TYPE_2__ {int idai; int irq; struct its_vm* its_vm; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 int __irq_domain_alloc_irqs (scalar_t__,int,int,int /*<<< orphan*/ ,struct its_vm*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  gic_domain ; 
 scalar_t__ irq_domain_alloc_named_id_fwnode (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ irq_domain_create_hierarchy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ,struct its_vm*) ; 
 int /*<<< orphan*/  irq_domain_free_fwnode (scalar_t__) ; 
 int /*<<< orphan*/  irq_domain_remove (scalar_t__) ; 
 int /*<<< orphan*/  task_pid_nr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpe_domain_ops ; 

int its_alloc_vcpu_irqs(struct its_vm *vm)
{
	int vpe_base_irq, i;

	vm->fwnode = irq_domain_alloc_named_id_fwnode("GICv4-vpe",
						      task_pid_nr(current));
	if (!vm->fwnode)
		goto err;

	vm->domain = irq_domain_create_hierarchy(gic_domain, 0, vm->nr_vpes,
						 vm->fwnode, vpe_domain_ops,
						 vm);
	if (!vm->domain)
		goto err;

	for (i = 0; i < vm->nr_vpes; i++) {
		vm->vpes[i]->its_vm = vm;
		vm->vpes[i]->idai = true;
	}

	vpe_base_irq = __irq_domain_alloc_irqs(vm->domain, -1, vm->nr_vpes,
					       NUMA_NO_NODE, vm,
					       false, NULL);
	if (vpe_base_irq <= 0)
		goto err;

	for (i = 0; i < vm->nr_vpes; i++)
		vm->vpes[i]->irq = vpe_base_irq + i;

	return 0;

err:
	if (vm->domain)
		irq_domain_remove(vm->domain);
	if (vm->fwnode)
		irq_domain_free_fwnode(vm->fwnode);

	return -ENOMEM;
}