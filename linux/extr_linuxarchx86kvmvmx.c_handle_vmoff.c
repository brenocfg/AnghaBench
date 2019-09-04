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
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_nested (int /*<<< orphan*/ ) ; 
 int kvm_skip_emulated_instruction (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  nested_vmx_check_permission (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  nested_vmx_succeed (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  to_vmx (struct kvm_vcpu*) ; 

__attribute__((used)) static int handle_vmoff(struct kvm_vcpu *vcpu)
{
	if (!nested_vmx_check_permission(vcpu))
		return 1;
	free_nested(to_vmx(vcpu));
	nested_vmx_succeed(vcpu);
	return kvm_skip_emulated_instruction(vcpu);
}