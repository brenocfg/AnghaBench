#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct x86_instruction_info {scalar_t__ intercept; } ;
struct TYPE_4__ {int error_code_valid; int /*<<< orphan*/  vector; } ;
struct x86_emulate_ctxt {TYPE_2__ exception; } ;
struct vmcs12 {int dummy; } ;
struct TYPE_3__ {struct x86_emulate_ctxt emulate_ctxt; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
typedef  enum x86_intercept_stage { ____Placeholder_x86_intercept_stage } x86_intercept_stage ;

/* Variables and functions */
 int /*<<< orphan*/  SECONDARY_EXEC_RDTSCP ; 
 int /*<<< orphan*/  UD_VECTOR ; 
 int X86EMUL_CONTINUE ; 
 int X86EMUL_PROPAGATE_FAULT ; 
 struct vmcs12* get_vmcs12 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  nested_cpu_has2 (struct vmcs12*,int /*<<< orphan*/ ) ; 
 scalar_t__ x86_intercept_rdtscp ; 

__attribute__((used)) static int vmx_check_intercept(struct kvm_vcpu *vcpu,
			       struct x86_instruction_info *info,
			       enum x86_intercept_stage stage)
{
	struct vmcs12 *vmcs12 = get_vmcs12(vcpu);
	struct x86_emulate_ctxt *ctxt = &vcpu->arch.emulate_ctxt;

	/*
	 * RDPID causes #UD if disabled through secondary execution controls.
	 * Because it is marked as EmulateOnUD, we need to intercept it here.
	 */
	if (info->intercept == x86_intercept_rdtscp &&
	    !nested_cpu_has2(vmcs12, SECONDARY_EXEC_RDTSCP)) {
		ctxt->exception.vector = UD_VECTOR;
		ctxt->exception.error_code_valid = false;
		return X86EMUL_PROPAGATE_FAULT;
	}

	/* TODO: check more intercepts... */
	return X86EMUL_CONTINUE;
}