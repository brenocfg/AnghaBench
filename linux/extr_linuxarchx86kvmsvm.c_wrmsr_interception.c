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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct vcpu_svm {int /*<<< orphan*/  vcpu; scalar_t__ next_rip; } ;
struct msr_data {int host_initiated; int /*<<< orphan*/  index; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCPU_REGS_RCX ; 
 int /*<<< orphan*/  kvm_inject_gp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_read_edx_eax (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_register_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_rip_read (int /*<<< orphan*/ *) ; 
 scalar_t__ kvm_set_msr (int /*<<< orphan*/ *,struct msr_data*) ; 
 int kvm_skip_emulated_instruction (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_kvm_msr_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_kvm_msr_write_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wrmsr_interception(struct vcpu_svm *svm)
{
	struct msr_data msr;
	u32 ecx = kvm_register_read(&svm->vcpu, VCPU_REGS_RCX);
	u64 data = kvm_read_edx_eax(&svm->vcpu);

	msr.data = data;
	msr.index = ecx;
	msr.host_initiated = false;

	svm->next_rip = kvm_rip_read(&svm->vcpu) + 2;
	if (kvm_set_msr(&svm->vcpu, &msr)) {
		trace_kvm_msr_write_ex(ecx, data);
		kvm_inject_gp(&svm->vcpu, 0);
		return 1;
	} else {
		trace_kvm_msr_write(ecx, data);
		return kvm_skip_emulated_instruction(&svm->vcpu);
	}
}