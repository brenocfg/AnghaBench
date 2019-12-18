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
struct its_vpe {int /*<<< orphan*/  col_idx; int /*<<< orphan*/  irq; } ;
struct its_vm {int* vlpi_count; int nr_vpes; struct its_vpe** vpes; } ;
struct its_node {size_t list_nr; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/  cpumask_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_of (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_data_update_effective_affinity (struct irq_data*,int /*<<< orphan*/ ) ; 
 struct irq_data* irq_get_irq_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_list_map ; 
 int /*<<< orphan*/  its_send_vinvall (struct its_node*,struct its_vpe*) ; 
 int /*<<< orphan*/  its_send_vmapp (struct its_node*,struct its_vpe*,int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vmovp_lock ; 

__attribute__((used)) static void its_map_vm(struct its_node *its, struct its_vm *vm)
{
	unsigned long flags;

	/* Not using the ITS list? Everything is always mapped. */
	if (!its_list_map)
		return;

	raw_spin_lock_irqsave(&vmovp_lock, flags);

	/*
	 * If the VM wasn't mapped yet, iterate over the vpes and get
	 * them mapped now.
	 */
	vm->vlpi_count[its->list_nr]++;

	if (vm->vlpi_count[its->list_nr] == 1) {
		int i;

		for (i = 0; i < vm->nr_vpes; i++) {
			struct its_vpe *vpe = vm->vpes[i];
			struct irq_data *d = irq_get_irq_data(vpe->irq);

			/* Map the VPE to the first possible CPU */
			vpe->col_idx = cpumask_first(cpu_online_mask);
			its_send_vmapp(its, vpe, true);
			its_send_vinvall(its, vpe);
			irq_data_update_effective_affinity(d, cpumask_of(vpe->col_idx));
		}
	}

	raw_spin_unlock_irqrestore(&vmovp_lock, flags);
}