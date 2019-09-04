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
 int /*<<< orphan*/  VM_EXIT_INSTRUCTION_LEN ; 
 unsigned long kvm_rip_read (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_rip_write (struct kvm_vcpu*,unsigned long) ; 
 scalar_t__ vmcs_read32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmx_set_interrupt_shadow (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void skip_emulated_instruction(struct kvm_vcpu *vcpu)
{
	unsigned long rip;

	rip = kvm_rip_read(vcpu);
	rip += vmcs_read32(VM_EXIT_INSTRUCTION_LEN);
	kvm_rip_write(vcpu, rip);

	/* skipping an emulated instruction also counts */
	vmx_set_interrupt_shadow(vcpu, 0);
}