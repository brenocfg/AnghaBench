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
struct vcpu_vmx {int save_nmsrs; int guest_msrs_dirty; int /*<<< orphan*/  vcpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_EFER ; 
 int __find_msr_index (struct vcpu_vmx*,int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_has_vmx_msr_bitmap () ; 
 int /*<<< orphan*/  move_msr_up (struct vcpu_vmx*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ update_transition_efer (struct vcpu_vmx*,int) ; 
 int /*<<< orphan*/  vmx_update_msr_bitmap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void setup_msrs(struct vcpu_vmx *vmx)
{
	int save_nmsrs, index;

	save_nmsrs = 0;
#ifdef CONFIG_X86_64
	if (is_long_mode(&vmx->vcpu)) {
		index = __find_msr_index(vmx, MSR_SYSCALL_MASK);
		if (index >= 0)
			move_msr_up(vmx, index, save_nmsrs++);
		index = __find_msr_index(vmx, MSR_LSTAR);
		if (index >= 0)
			move_msr_up(vmx, index, save_nmsrs++);
		index = __find_msr_index(vmx, MSR_CSTAR);
		if (index >= 0)
			move_msr_up(vmx, index, save_nmsrs++);
		index = __find_msr_index(vmx, MSR_TSC_AUX);
		if (index >= 0 && guest_cpuid_has(&vmx->vcpu, X86_FEATURE_RDTSCP))
			move_msr_up(vmx, index, save_nmsrs++);
		/*
		 * MSR_STAR is only needed on long mode guests, and only
		 * if efer.sce is enabled.
		 */
		index = __find_msr_index(vmx, MSR_STAR);
		if ((index >= 0) && (vmx->vcpu.arch.efer & EFER_SCE))
			move_msr_up(vmx, index, save_nmsrs++);
	}
#endif
	index = __find_msr_index(vmx, MSR_EFER);
	if (index >= 0 && update_transition_efer(vmx, index))
		move_msr_up(vmx, index, save_nmsrs++);

	vmx->save_nmsrs = save_nmsrs;
	vmx->guest_msrs_dirty = true;

	if (cpu_has_vmx_msr_bitmap())
		vmx_update_msr_bitmap(&vmx->vcpu);
}