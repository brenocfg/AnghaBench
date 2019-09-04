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
 unsigned long NUM_TIMER_REGS ; 
 unsigned long kvm_arm_get_fw_num_regs (struct kvm_vcpu*) ; 
 unsigned long kvm_arm_num_coproc_regs (struct kvm_vcpu*) ; 
 unsigned long num_core_regs () ; 

unsigned long kvm_arm_num_regs(struct kvm_vcpu *vcpu)
{
	return num_core_regs() + kvm_arm_num_coproc_regs(vcpu)
		+ kvm_arm_get_fw_num_regs(vcpu)
		+ NUM_TIMER_REGS;
}