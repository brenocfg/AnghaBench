#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  insn_emulation_fail; } ;
struct kvm_vcpu {TYPE_3__* run; TYPE_2__ stat; } ;
struct TYPE_8__ {scalar_t__ (* get_cpl ) (struct kvm_vcpu*) ;} ;
struct TYPE_5__ {scalar_t__ ndata; int /*<<< orphan*/  suberror; } ;
struct TYPE_7__ {TYPE_1__ internal; int /*<<< orphan*/  exit_reason; } ;

/* Variables and functions */
 int EMULATE_DONE ; 
 int EMULATE_FAIL ; 
 int EMULATE_USER_EXIT ; 
 int EMULTYPE_NO_UD_ON_FAIL ; 
 int /*<<< orphan*/  KVM_EXIT_INTERNAL_ERROR ; 
 int /*<<< orphan*/  KVM_INTERNAL_ERROR_EMULATION ; 
 int /*<<< orphan*/  UD_VECTOR ; 
 int /*<<< orphan*/  is_guest_mode (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_queue_exception (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 TYPE_4__* kvm_x86_ops ; 
 scalar_t__ stub1 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  trace_kvm_emulate_insn_failed (struct kvm_vcpu*) ; 

__attribute__((used)) static int handle_emulation_failure(struct kvm_vcpu *vcpu, int emulation_type)
{
	int r = EMULATE_DONE;

	++vcpu->stat.insn_emulation_fail;
	trace_kvm_emulate_insn_failed(vcpu);

	if (emulation_type & EMULTYPE_NO_UD_ON_FAIL)
		return EMULATE_FAIL;

	if (!is_guest_mode(vcpu) && kvm_x86_ops->get_cpl(vcpu) == 0) {
		vcpu->run->exit_reason = KVM_EXIT_INTERNAL_ERROR;
		vcpu->run->internal.suberror = KVM_INTERNAL_ERROR_EMULATION;
		vcpu->run->internal.ndata = 0;
		r = EMULATE_USER_EXIT;
	}

	kvm_queue_exception(vcpu, UD_VECTOR);

	return r;
}