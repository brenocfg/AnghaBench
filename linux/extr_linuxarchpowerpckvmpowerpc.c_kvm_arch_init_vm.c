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
struct kvmppc_ops {scalar_t__ owner; } ;
struct TYPE_2__ {struct kvmppc_ops* kvm_ops; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 unsigned long KVM_VM_PPC_HV ; 
 unsigned long KVM_VM_PPC_PR ; 
 int kvmppc_core_init_vm (struct kvm*) ; 
 struct kvmppc_ops* kvmppc_hv_ops ; 
 struct kvmppc_ops* kvmppc_pr_ops ; 
 int /*<<< orphan*/  try_module_get (scalar_t__) ; 

int kvm_arch_init_vm(struct kvm *kvm, unsigned long type)
{
	struct kvmppc_ops *kvm_ops = NULL;
	/*
	 * if we have both HV and PR enabled, default is HV
	 */
	if (type == 0) {
		if (kvmppc_hv_ops)
			kvm_ops = kvmppc_hv_ops;
		else
			kvm_ops = kvmppc_pr_ops;
		if (!kvm_ops)
			goto err_out;
	} else	if (type == KVM_VM_PPC_HV) {
		if (!kvmppc_hv_ops)
			goto err_out;
		kvm_ops = kvmppc_hv_ops;
	} else if (type == KVM_VM_PPC_PR) {
		if (!kvmppc_pr_ops)
			goto err_out;
		kvm_ops = kvmppc_pr_ops;
	} else
		goto err_out;

	if (kvm_ops->owner && !try_module_get(kvm_ops->owner))
		return -ENOENT;

	kvm->arch.kvm_ops = kvm_ops;
	return kvmppc_core_init_vm(kvm);
err_out:
	return -EINVAL;
}