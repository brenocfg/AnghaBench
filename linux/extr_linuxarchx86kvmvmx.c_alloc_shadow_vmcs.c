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
struct vmcs {int dummy; } ;
struct loaded_vmcs {struct vmcs* shadow_vmcs; } ;
struct vcpu_vmx {struct loaded_vmcs vmcs01; struct loaded_vmcs* loaded_vmcs; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct vmcs* alloc_vmcs (int) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmcs_clear (struct vmcs*) ; 

__attribute__((used)) static struct vmcs *alloc_shadow_vmcs(struct kvm_vcpu *vcpu)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	struct loaded_vmcs *loaded_vmcs = vmx->loaded_vmcs;

	/*
	 * We should allocate a shadow vmcs for vmcs01 only when L1
	 * executes VMXON and free it when L1 executes VMXOFF.
	 * As it is invalid to execute VMXON twice, we shouldn't reach
	 * here when vmcs01 already have an allocated shadow vmcs.
	 */
	WARN_ON(loaded_vmcs == &vmx->vmcs01 && loaded_vmcs->shadow_vmcs);

	if (!loaded_vmcs->shadow_vmcs) {
		loaded_vmcs->shadow_vmcs = alloc_vmcs(true);
		if (loaded_vmcs->shadow_vmcs)
			vmcs_clear(loaded_vmcs->shadow_vmcs);
	}
	return loaded_vmcs->shadow_vmcs;
}