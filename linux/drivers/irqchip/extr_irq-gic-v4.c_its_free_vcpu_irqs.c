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
struct its_vm {int /*<<< orphan*/  fwnode; int /*<<< orphan*/  domain; int /*<<< orphan*/  nr_vpes; TYPE_1__** vpes; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_domain_free_fwnode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_free_irqs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 

void its_free_vcpu_irqs(struct its_vm *vm)
{
	irq_domain_free_irqs(vm->vpes[0]->irq, vm->nr_vpes);
	irq_domain_remove(vm->domain);
	irq_domain_free_fwnode(vm->fwnode);
}