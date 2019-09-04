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
struct TYPE_2__ {int /*<<< orphan*/  hpt; int /*<<< orphan*/  lpid; int /*<<< orphan*/  threads_indep; int /*<<< orphan*/  debugfs_dir; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_hv_vm_deactivated () ; 
 scalar_t__ kvm_is_radix (struct kvm*) ; 
 int /*<<< orphan*/  kvmppc_free_hpt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvmppc_free_lpid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_free_pimap (struct kvm*) ; 
 int /*<<< orphan*/  kvmppc_free_radix (struct kvm*) ; 
 int /*<<< orphan*/  kvmppc_free_vcores (struct kvm*) ; 

__attribute__((used)) static void kvmppc_core_destroy_vm_hv(struct kvm *kvm)
{
	debugfs_remove_recursive(kvm->arch.debugfs_dir);

	if (!kvm->arch.threads_indep)
		kvm_hv_vm_deactivated();

	kvmppc_free_vcores(kvm);

	kvmppc_free_lpid(kvm->arch.lpid);

	if (kvm_is_radix(kvm))
		kvmppc_free_radix(kvm);
	else
		kvmppc_free_hpt(&kvm->arch.hpt);

	kvmppc_free_pimap(kvm);
}