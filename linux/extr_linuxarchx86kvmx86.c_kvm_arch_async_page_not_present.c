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
struct x86_exception {int error_code_valid; int nested_page_fault; int async_page_fault; int /*<<< orphan*/  address; scalar_t__ error_code; int /*<<< orphan*/  vector; } ;
struct TYPE_5__ {int msr_val; scalar_t__ send_user_only; } ;
struct TYPE_6__ {TYPE_1__ apf; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_7__ {int /*<<< orphan*/  token; int /*<<< orphan*/  gfn; } ;
struct kvm_async_pf {TYPE_3__ arch; int /*<<< orphan*/  gva; } ;
struct TYPE_8__ {scalar_t__ (* get_cpl ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 int KVM_ASYNC_PF_ENABLED ; 
 int /*<<< orphan*/  KVM_PV_REASON_PAGE_NOT_PRESENT ; 
 int /*<<< orphan*/  KVM_REQ_APF_HALT ; 
 int /*<<< orphan*/  PF_VECTOR ; 
 int /*<<< orphan*/  apf_put_user (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_add_async_pf_gfn (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_inject_page_fault (struct kvm_vcpu*,struct x86_exception*) ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 TYPE_4__* kvm_x86_ops ; 
 scalar_t__ stub1 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  trace_kvm_async_pf_not_present (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void kvm_arch_async_page_not_present(struct kvm_vcpu *vcpu,
				     struct kvm_async_pf *work)
{
	struct x86_exception fault;

	trace_kvm_async_pf_not_present(work->arch.token, work->gva);
	kvm_add_async_pf_gfn(vcpu, work->arch.gfn);

	if (!(vcpu->arch.apf.msr_val & KVM_ASYNC_PF_ENABLED) ||
	    (vcpu->arch.apf.send_user_only &&
	     kvm_x86_ops->get_cpl(vcpu) == 0))
		kvm_make_request(KVM_REQ_APF_HALT, vcpu);
	else if (!apf_put_user(vcpu, KVM_PV_REASON_PAGE_NOT_PRESENT)) {
		fault.vector = PF_VECTOR;
		fault.error_code_valid = true;
		fault.error_code = 0;
		fault.nested_page_fault = false;
		fault.address = work->arch.token;
		fault.async_page_fault = true;
		kvm_inject_page_fault(vcpu, &fault);
	}
}