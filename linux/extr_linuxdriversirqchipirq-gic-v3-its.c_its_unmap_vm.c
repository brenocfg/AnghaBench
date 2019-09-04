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
struct its_vm {int nr_vpes; int /*<<< orphan*/ * vpes; int /*<<< orphan*/ * vlpi_count; } ;
struct its_node {size_t list_nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  its_list_map ; 
 int /*<<< orphan*/  its_send_vmapp (struct its_node*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vmovp_lock ; 

__attribute__((used)) static void its_unmap_vm(struct its_node *its, struct its_vm *vm)
{
	unsigned long flags;

	/* Not using the ITS list? Everything is always mapped. */
	if (!its_list_map)
		return;

	raw_spin_lock_irqsave(&vmovp_lock, flags);

	if (!--vm->vlpi_count[its->list_nr]) {
		int i;

		for (i = 0; i < vm->nr_vpes; i++)
			its_send_vmapp(its, vm->vpes[i], false);
	}

	raw_spin_unlock_irqrestore(&vmovp_lock, flags);
}