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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int pending; int injected; int has_error_code; unsigned int nr; scalar_t__ error_code; } ;
struct TYPE_4__ {TYPE_1__ exception; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;

/* Variables and functions */
 scalar_t__ DF_VECTOR ; 
 int EXCPT_BENIGN ; 
 int EXCPT_CONTRIBUTORY ; 
 int EXCPT_PF ; 
 int /*<<< orphan*/  KVM_REQ_EVENT ; 
 int /*<<< orphan*/  KVM_REQ_TRIPLE_FAULT ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int exception_class (unsigned int) ; 
 int /*<<< orphan*/  is_protmode (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 

__attribute__((used)) static void kvm_multiple_exception(struct kvm_vcpu *vcpu,
		unsigned nr, bool has_error, u32 error_code,
		bool reinject)
{
	u32 prev_nr;
	int class1, class2;

	kvm_make_request(KVM_REQ_EVENT, vcpu);

	if (!vcpu->arch.exception.pending && !vcpu->arch.exception.injected) {
	queue:
		if (has_error && !is_protmode(vcpu))
			has_error = false;
		if (reinject) {
			/*
			 * On vmentry, vcpu->arch.exception.pending is only
			 * true if an event injection was blocked by
			 * nested_run_pending.  In that case, however,
			 * vcpu_enter_guest requests an immediate exit,
			 * and the guest shouldn't proceed far enough to
			 * need reinjection.
			 */
			WARN_ON_ONCE(vcpu->arch.exception.pending);
			vcpu->arch.exception.injected = true;
		} else {
			vcpu->arch.exception.pending = true;
			vcpu->arch.exception.injected = false;
		}
		vcpu->arch.exception.has_error_code = has_error;
		vcpu->arch.exception.nr = nr;
		vcpu->arch.exception.error_code = error_code;
		return;
	}

	/* to check exception */
	prev_nr = vcpu->arch.exception.nr;
	if (prev_nr == DF_VECTOR) {
		/* triple fault -> shutdown */
		kvm_make_request(KVM_REQ_TRIPLE_FAULT, vcpu);
		return;
	}
	class1 = exception_class(prev_nr);
	class2 = exception_class(nr);
	if ((class1 == EXCPT_CONTRIBUTORY && class2 == EXCPT_CONTRIBUTORY)
		|| (class1 == EXCPT_PF && class2 != EXCPT_BENIGN)) {
		/*
		 * Generate double fault per SDM Table 5-5.  Set
		 * exception.pending = true so that the double fault
		 * can trigger a nested vmexit.
		 */
		vcpu->arch.exception.pending = true;
		vcpu->arch.exception.injected = false;
		vcpu->arch.exception.has_error_code = true;
		vcpu->arch.exception.nr = DF_VECTOR;
		vcpu->arch.exception.error_code = 0;
	} else
		/* replace previous exception with a new one in a hope
		   that instruction re-execution will regenerate lost
		   exception */
		goto queue;
}