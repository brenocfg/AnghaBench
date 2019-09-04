#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_10__ {int /*<<< orphan*/  vm86_active; } ;
struct TYPE_8__ {scalar_t__ nested_run_pending; } ;
struct vcpu_vmx {TYPE_3__ rmode; scalar_t__ emulation_required; int /*<<< orphan*/  vcpu; TYPE_1__ nested; } ;
struct TYPE_11__ {scalar_t__ pending; } ;
struct TYPE_12__ {scalar_t__ halt_request; TYPE_4__ exception; } ;
struct TYPE_9__ {int /*<<< orphan*/  mmio_exits; } ;
struct kvm_vcpu {TYPE_7__* run; TYPE_5__ arch; TYPE_2__ stat; } ;
typedef  enum emulation_result { ____Placeholder_emulation_result } emulation_result ;
struct TYPE_13__ {scalar_t__ ndata; int /*<<< orphan*/  suberror; } ;
struct TYPE_14__ {TYPE_6__ internal; int /*<<< orphan*/  exit_reason; } ;

/* Variables and functions */
 int CPU_BASED_VIRTUAL_INTR_PENDING ; 
 int /*<<< orphan*/  CPU_BASED_VM_EXEC_CONTROL ; 
 int EMULATE_DONE ; 
 int EMULATE_USER_EXIT ; 
 int /*<<< orphan*/  KVM_EXIT_INTERNAL_ERROR ; 
 int /*<<< orphan*/  KVM_INTERNAL_ERROR_EMULATION ; 
 int /*<<< orphan*/  KVM_REQ_EVENT ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  current ; 
 int handle_interrupt_window (int /*<<< orphan*/ *) ; 
 int kvm_emulate_instruction (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_test_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int kvm_vcpu_halt (struct kvm_vcpu*) ; 
 scalar_t__ need_resched () ; 
 int /*<<< orphan*/  schedule () ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 int vmcs_read32 (int /*<<< orphan*/ ) ; 
 scalar_t__ vmx_interrupt_allowed (struct kvm_vcpu*) ; 

__attribute__((used)) static int handle_invalid_guest_state(struct kvm_vcpu *vcpu)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	enum emulation_result err = EMULATE_DONE;
	int ret = 1;
	u32 cpu_exec_ctrl;
	bool intr_window_requested;
	unsigned count = 130;

	/*
	 * We should never reach the point where we are emulating L2
	 * due to invalid guest state as that means we incorrectly
	 * allowed a nested VMEntry with an invalid vmcs12.
	 */
	WARN_ON_ONCE(vmx->emulation_required && vmx->nested.nested_run_pending);

	cpu_exec_ctrl = vmcs_read32(CPU_BASED_VM_EXEC_CONTROL);
	intr_window_requested = cpu_exec_ctrl & CPU_BASED_VIRTUAL_INTR_PENDING;

	while (vmx->emulation_required && count-- != 0) {
		if (intr_window_requested && vmx_interrupt_allowed(vcpu))
			return handle_interrupt_window(&vmx->vcpu);

		if (kvm_test_request(KVM_REQ_EVENT, vcpu))
			return 1;

		err = kvm_emulate_instruction(vcpu, 0);

		if (err == EMULATE_USER_EXIT) {
			++vcpu->stat.mmio_exits;
			ret = 0;
			goto out;
		}

		if (err != EMULATE_DONE)
			goto emulation_error;

		if (vmx->emulation_required && !vmx->rmode.vm86_active &&
		    vcpu->arch.exception.pending)
			goto emulation_error;

		if (vcpu->arch.halt_request) {
			vcpu->arch.halt_request = 0;
			ret = kvm_vcpu_halt(vcpu);
			goto out;
		}

		if (signal_pending(current))
			goto out;
		if (need_resched())
			schedule();
	}

out:
	return ret;

emulation_error:
	vcpu->run->exit_reason = KVM_EXIT_INTERNAL_ERROR;
	vcpu->run->internal.suberror = KVM_INTERNAL_ERROR_EMULATION;
	vcpu->run->internal.ndata = 0;
	return 0;
}