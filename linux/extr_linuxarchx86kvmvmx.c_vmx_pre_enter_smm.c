#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int vmxon; scalar_t__ guest_mode; } ;
struct TYPE_3__ {int vmxon; TYPE_2__ smm; } ;
struct vcpu_vmx {TYPE_1__ nested; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 scalar_t__ is_guest_mode (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  nested_vmx_vmexit (struct kvm_vcpu*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmx_clear_hlt (struct kvm_vcpu*) ; 

__attribute__((used)) static int vmx_pre_enter_smm(struct kvm_vcpu *vcpu, char *smstate)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);

	vmx->nested.smm.guest_mode = is_guest_mode(vcpu);
	if (vmx->nested.smm.guest_mode)
		nested_vmx_vmexit(vcpu, -1, 0, 0);

	vmx->nested.smm.vmxon = vmx->nested.vmxon;
	vmx->nested.vmxon = false;
	vmx_clear_hlt(vcpu);
	return 0;
}