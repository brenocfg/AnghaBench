#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_5__ {int /*<<< orphan*/  host_apf_reason; } ;
struct TYPE_6__ {TYPE_1__ apf; } ;
struct TYPE_7__ {TYPE_2__ arch; } ;
struct vcpu_vmx {int exit_reason; TYPE_3__ vcpu; int /*<<< orphan*/  exit_intr_info; } ;

/* Variables and functions */
 scalar_t__ EXIT_REASON_EXCEPTION_NMI ; 
 scalar_t__ EXIT_REASON_MCE_DURING_VMENTRY ; 
 int VMX_EXIT_REASONS_FAILED_VMENTRY ; 
 int /*<<< orphan*/  VM_EXIT_INTR_INFO ; 
 scalar_t__ is_machine_check (int /*<<< orphan*/ ) ; 
 scalar_t__ is_nmi (int /*<<< orphan*/ ) ; 
 scalar_t__ is_page_fault (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_after_interrupt (TYPE_3__*) ; 
 int /*<<< orphan*/  kvm_before_interrupt (TYPE_3__*) ; 
 int /*<<< orphan*/  kvm_machine_check () ; 
 int /*<<< orphan*/  kvm_read_and_reset_pf_reason () ; 
 int /*<<< orphan*/  vmcs_read32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vmx_complete_atomic_exit(struct vcpu_vmx *vmx)
{
	u32 exit_intr_info = 0;
	u16 basic_exit_reason = (u16)vmx->exit_reason;

	if (!(basic_exit_reason == EXIT_REASON_MCE_DURING_VMENTRY
	      || basic_exit_reason == EXIT_REASON_EXCEPTION_NMI))
		return;

	if (!(vmx->exit_reason & VMX_EXIT_REASONS_FAILED_VMENTRY))
		exit_intr_info = vmcs_read32(VM_EXIT_INTR_INFO);
	vmx->exit_intr_info = exit_intr_info;

	/* if exit due to PF check for async PF */
	if (is_page_fault(exit_intr_info))
		vmx->vcpu.arch.apf.host_apf_reason = kvm_read_and_reset_pf_reason();

	/* Handle machine checks before interrupts are enabled */
	if (basic_exit_reason == EXIT_REASON_MCE_DURING_VMENTRY ||
	    is_machine_check(exit_intr_info))
		kvm_machine_check();

	/* We need to handle NMIs before interrupts are enabled */
	if (is_nmi(exit_intr_info)) {
		kvm_before_interrupt(&vmx->vcpu);
		asm("int $2");
		kvm_after_interrupt(&vmx->vcpu);
	}
}