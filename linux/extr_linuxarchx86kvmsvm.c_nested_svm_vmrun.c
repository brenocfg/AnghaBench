#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_14__ {int /*<<< orphan*/  cr3; int /*<<< orphan*/  rax; int /*<<< orphan*/  rsp; int /*<<< orphan*/  rip; int /*<<< orphan*/  rflags; int /*<<< orphan*/  cr4; int /*<<< orphan*/  cr0; int /*<<< orphan*/  efer; int /*<<< orphan*/  idtr; int /*<<< orphan*/  gdtr; int /*<<< orphan*/  ds; int /*<<< orphan*/  ss; int /*<<< orphan*/  cs; int /*<<< orphan*/  es; } ;
struct TYPE_12__ {int intercept_cr; int /*<<< orphan*/  intercept; int /*<<< orphan*/  intercept_exceptions; int /*<<< orphan*/  nested_ctl; int /*<<< orphan*/  event_inj; int /*<<< orphan*/  int_ctl; scalar_t__ exit_info_2; scalar_t__ exit_info_1; scalar_t__ exit_code_hi; int /*<<< orphan*/  exit_code; } ;
struct vmcb {TYPE_4__ save; TYPE_2__ control; } ;
struct TYPE_13__ {int /*<<< orphan*/  cr4; int /*<<< orphan*/  efer; } ;
struct TYPE_15__ {TYPE_3__ arch; } ;
struct TYPE_11__ {struct vmcb* hsave; } ;
struct vcpu_svm {TYPE_5__ vcpu; struct vmcb* vmcb; TYPE_1__ nested; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVM_EXIT_ERR ; 
 int /*<<< orphan*/  copy_vmcb_control_area (struct vmcb*,struct vmcb*) ; 
 int /*<<< orphan*/  enter_svm_guest_mode (struct vcpu_svm*,int /*<<< orphan*/ ,struct vmcb*,struct page*) ; 
 int /*<<< orphan*/  kvm_clear_exception_queue (TYPE_5__*) ; 
 int /*<<< orphan*/  kvm_clear_interrupt_queue (TYPE_5__*) ; 
 int /*<<< orphan*/  kvm_get_rflags (TYPE_5__*) ; 
 int /*<<< orphan*/  kvm_read_cr0 (TYPE_5__*) ; 
 int /*<<< orphan*/  kvm_read_cr3 (TYPE_5__*) ; 
 int /*<<< orphan*/  kvm_rip_read (TYPE_5__*) ; 
 struct vmcb* nested_svm_map (struct vcpu_svm*,int /*<<< orphan*/ ,struct page**) ; 
 int /*<<< orphan*/  nested_svm_unmap (struct page*) ; 
 int /*<<< orphan*/  nested_vmcb_checks (struct vmcb*) ; 
 scalar_t__ npt_enabled ; 
 int /*<<< orphan*/  trace_kvm_nested_intercepts (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_kvm_nested_vmrun (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool nested_svm_vmrun(struct vcpu_svm *svm)
{
	struct vmcb *nested_vmcb;
	struct vmcb *hsave = svm->nested.hsave;
	struct vmcb *vmcb = svm->vmcb;
	struct page *page;
	u64 vmcb_gpa;

	vmcb_gpa = svm->vmcb->save.rax;

	nested_vmcb = nested_svm_map(svm, svm->vmcb->save.rax, &page);
	if (!nested_vmcb)
		return false;

	if (!nested_vmcb_checks(nested_vmcb)) {
		nested_vmcb->control.exit_code    = SVM_EXIT_ERR;
		nested_vmcb->control.exit_code_hi = 0;
		nested_vmcb->control.exit_info_1  = 0;
		nested_vmcb->control.exit_info_2  = 0;

		nested_svm_unmap(page);

		return false;
	}

	trace_kvm_nested_vmrun(svm->vmcb->save.rip, vmcb_gpa,
			       nested_vmcb->save.rip,
			       nested_vmcb->control.int_ctl,
			       nested_vmcb->control.event_inj,
			       nested_vmcb->control.nested_ctl);

	trace_kvm_nested_intercepts(nested_vmcb->control.intercept_cr & 0xffff,
				    nested_vmcb->control.intercept_cr >> 16,
				    nested_vmcb->control.intercept_exceptions,
				    nested_vmcb->control.intercept);

	/* Clear internal status */
	kvm_clear_exception_queue(&svm->vcpu);
	kvm_clear_interrupt_queue(&svm->vcpu);

	/*
	 * Save the old vmcb, so we don't need to pick what we save, but can
	 * restore everything when a VMEXIT occurs
	 */
	hsave->save.es     = vmcb->save.es;
	hsave->save.cs     = vmcb->save.cs;
	hsave->save.ss     = vmcb->save.ss;
	hsave->save.ds     = vmcb->save.ds;
	hsave->save.gdtr   = vmcb->save.gdtr;
	hsave->save.idtr   = vmcb->save.idtr;
	hsave->save.efer   = svm->vcpu.arch.efer;
	hsave->save.cr0    = kvm_read_cr0(&svm->vcpu);
	hsave->save.cr4    = svm->vcpu.arch.cr4;
	hsave->save.rflags = kvm_get_rflags(&svm->vcpu);
	hsave->save.rip    = kvm_rip_read(&svm->vcpu);
	hsave->save.rsp    = vmcb->save.rsp;
	hsave->save.rax    = vmcb->save.rax;
	if (npt_enabled)
		hsave->save.cr3    = vmcb->save.cr3;
	else
		hsave->save.cr3    = kvm_read_cr3(&svm->vcpu);

	copy_vmcb_control_area(hsave, vmcb);

	enter_svm_guest_mode(svm, vmcb_gpa, nested_vmcb, page);

	return true;
}