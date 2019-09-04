#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_5__ {int vmxon; int guest_mode; } ;
struct TYPE_6__ {int vmxon; TYPE_2__ smm; } ;
struct vcpu_vmx {TYPE_3__ nested; } ;
struct TYPE_4__ {int /*<<< orphan*/  hflags; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  HF_SMM_MASK ; 
 int enter_vmx_non_root_mode (struct kvm_vcpu*,int /*<<< orphan*/ *) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 

__attribute__((used)) static int vmx_pre_leave_smm(struct kvm_vcpu *vcpu, u64 smbase)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	int ret;

	if (vmx->nested.smm.vmxon) {
		vmx->nested.vmxon = true;
		vmx->nested.smm.vmxon = false;
	}

	if (vmx->nested.smm.guest_mode) {
		vcpu->arch.hflags &= ~HF_SMM_MASK;
		ret = enter_vmx_non_root_mode(vcpu, NULL);
		vcpu->arch.hflags |= HF_SMM_MASK;
		if (ret)
			return ret;

		vmx->nested.smm.guest_mode = false;
	}
	return 0;
}