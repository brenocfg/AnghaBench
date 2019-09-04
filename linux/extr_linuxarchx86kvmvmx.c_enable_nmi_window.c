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
 int /*<<< orphan*/  CPU_BASED_VIRTUAL_NMI_PENDING ; 
 int /*<<< orphan*/  CPU_BASED_VM_EXEC_CONTROL ; 
 int /*<<< orphan*/  GUEST_INTERRUPTIBILITY_INFO ; 
 int GUEST_INTR_STATE_STI ; 
 int /*<<< orphan*/  enable_irq_window (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  enable_vnmi ; 
 int vmcs_read32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enable_nmi_window(struct kvm_vcpu *vcpu)
{
	if (!enable_vnmi ||
	    vmcs_read32(GUEST_INTERRUPTIBILITY_INFO) & GUEST_INTR_STATE_STI) {
		enable_irq_window(vcpu);
		return;
	}

	vmcs_set_bits(CPU_BASED_VM_EXEC_CONTROL,
		      CPU_BASED_VIRTUAL_NMI_PENDING);
}