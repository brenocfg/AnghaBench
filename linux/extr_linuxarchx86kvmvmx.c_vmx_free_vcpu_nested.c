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
struct vcpu_vmx {int /*<<< orphan*/  vmcs01; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_nested (struct vcpu_vmx*) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_load (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_put (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmx_switch_vmcs (struct kvm_vcpu*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vmx_free_vcpu_nested(struct kvm_vcpu *vcpu)
{
       struct vcpu_vmx *vmx = to_vmx(vcpu);

       vcpu_load(vcpu);
       vmx_switch_vmcs(vcpu, &vmx->vmcs01);
       free_nested(vmx);
       vcpu_put(vcpu);
}