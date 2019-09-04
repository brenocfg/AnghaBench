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
struct vcpu_vmx {int /*<<< orphan*/  guest_msrs; int /*<<< orphan*/  loaded_vmcs; int /*<<< orphan*/  vpid; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 scalar_t__ enable_pml ; 
 int /*<<< orphan*/  free_loaded_vmcs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_vpid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct vcpu_vmx*) ; 
 int /*<<< orphan*/  kvm_vcpu_cache ; 
 int /*<<< orphan*/  kvm_vcpu_uninit (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  leave_guest_mode (struct kvm_vcpu*) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmx_destroy_pml_buffer (struct vcpu_vmx*) ; 
 int /*<<< orphan*/  vmx_free_vcpu_nested (struct kvm_vcpu*) ; 

__attribute__((used)) static void vmx_free_vcpu(struct kvm_vcpu *vcpu)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);

	if (enable_pml)
		vmx_destroy_pml_buffer(vmx);
	free_vpid(vmx->vpid);
	leave_guest_mode(vcpu);
	vmx_free_vcpu_nested(vcpu);
	free_loaded_vmcs(vmx->loaded_vmcs);
	kfree(vmx->guest_msrs);
	kvm_vcpu_uninit(vcpu);
	kmem_cache_free(kvm_vcpu_cache, vmx);
}