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
struct kvm_hpt_info {int dummy; } ;
struct kvm_resize_hpt {struct kvm_hpt_info hpt; struct kvm* kvm; } ;
struct TYPE_2__ {struct kvm_hpt_info hpt; } ;
struct kvm {int /*<<< orphan*/  srcu; int /*<<< orphan*/  mmu_lock; TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_ARCH_300 ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_set_hpt (struct kvm*,struct kvm_hpt_info*) ; 
 int /*<<< orphan*/  kvmppc_setup_partition_table (struct kvm*) ; 
 int /*<<< orphan*/  resize_hpt_debug (struct kvm_resize_hpt*,char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_srcu_expedited (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void resize_hpt_pivot(struct kvm_resize_hpt *resize)
{
	struct kvm *kvm = resize->kvm;
	struct kvm_hpt_info hpt_tmp;

	/* Exchange the pending tables in the resize structure with
	 * the active tables */

	resize_hpt_debug(resize, "resize_hpt_pivot()\n");

	spin_lock(&kvm->mmu_lock);
	asm volatile("ptesync" : : : "memory");

	hpt_tmp = kvm->arch.hpt;
	kvmppc_set_hpt(kvm, &resize->hpt);
	resize->hpt = hpt_tmp;

	spin_unlock(&kvm->mmu_lock);

	synchronize_srcu_expedited(&kvm->srcu);

	if (cpu_has_feature(CPU_FTR_ARCH_300))
		kvmppc_setup_partition_table(kvm);

	resize_hpt_debug(resize, "resize_hpt_pivot() done\n");
}