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
struct TYPE_2__ {unsigned long long current_vmptr; } ;
struct vcpu_vmx {TYPE_1__ nested; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nested_vmx_failInvalid (struct kvm_vcpu*) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 

__attribute__((used)) static int nested_vmx_check_vmcs12(struct kvm_vcpu *vcpu)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	if (vmx->nested.current_vmptr == -1ull) {
		nested_vmx_failInvalid(vcpu);
		return 0;
	}
	return 1;
}