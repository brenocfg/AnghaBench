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
typedef  int /*<<< orphan*/  u32 ;
struct vcpu_svm {int /*<<< orphan*/  vcpu; scalar_t__ next_rip; } ;
struct msr_data {int host_initiated; int data; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCPU_REGS_RAX ; 
 int /*<<< orphan*/  VCPU_REGS_RCX ; 
 int /*<<< orphan*/  VCPU_REGS_RDX ; 
 int /*<<< orphan*/  kvm_inject_gp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_register_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_register_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ kvm_rip_read (int /*<<< orphan*/ *) ; 
 int kvm_skip_emulated_instruction (int /*<<< orphan*/ *) ; 
 scalar_t__ svm_get_msr (int /*<<< orphan*/ *,struct msr_data*) ; 
 int /*<<< orphan*/  trace_kvm_msr_read (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trace_kvm_msr_read_ex (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rdmsr_interception(struct vcpu_svm *svm)
{
	u32 ecx = kvm_register_read(&svm->vcpu, VCPU_REGS_RCX);
	struct msr_data msr_info;

	msr_info.index = ecx;
	msr_info.host_initiated = false;
	if (svm_get_msr(&svm->vcpu, &msr_info)) {
		trace_kvm_msr_read_ex(ecx);
		kvm_inject_gp(&svm->vcpu, 0);
		return 1;
	} else {
		trace_kvm_msr_read(ecx, msr_info.data);

		kvm_register_write(&svm->vcpu, VCPU_REGS_RAX,
				   msr_info.data & 0xffffffff);
		kvm_register_write(&svm->vcpu, VCPU_REGS_RDX,
				   msr_info.data >> 32);
		svm->next_rip = kvm_rip_read(&svm->vcpu) + 2;
		return kvm_skip_emulated_instruction(&svm->vcpu);
	}
}