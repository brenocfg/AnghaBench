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
struct TYPE_3__ {scalar_t__ revision_id; scalar_t__ shadow_vmcs; } ;
struct vmcs12 {TYPE_1__ hdr; } ;
struct TYPE_4__ {int vmxon_ptr; int current_vmptr; int /*<<< orphan*/  cached_vmcs12; } ;
struct vcpu_vmx {TYPE_2__ nested; } ;
struct page {int dummy; } ;
struct kvm_vcpu {int dummy; } ;
typedef  int gpa_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_ALIGNED (int) ; 
 scalar_t__ VMCS12_REVISION ; 
 int /*<<< orphan*/  VMCS12_SIZE ; 
 int /*<<< orphan*/  VMXERR_VMPTRLD_INCORRECT_VMCS_REVISION_ID ; 
 int /*<<< orphan*/  VMXERR_VMPTRLD_INVALID_ADDRESS ; 
 int /*<<< orphan*/  VMXERR_VMPTRLD_VMXON_POINTER ; 
 int cpuid_maxphyaddr (struct kvm_vcpu*) ; 
 scalar_t__ is_error_page (struct page*) ; 
 struct vmcs12* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  kvm_release_page_clean (struct page*) ; 
 int kvm_skip_emulated_instruction (struct kvm_vcpu*) ; 
 struct page* kvm_vcpu_gpa_to_page (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct vmcs12*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nested_cpu_has_vmx_shadow_vmcs (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  nested_release_vmcs12 (struct vcpu_vmx*) ; 
 int /*<<< orphan*/  nested_vmx_check_permission (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  nested_vmx_failInvalid (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  nested_vmx_failValid (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 scalar_t__ nested_vmx_get_vmptr (struct kvm_vcpu*,int*) ; 
 int /*<<< orphan*/  nested_vmx_succeed (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  set_current_vmptr (struct vcpu_vmx*,int) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 

__attribute__((used)) static int handle_vmptrld(struct kvm_vcpu *vcpu)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	gpa_t vmptr;

	if (!nested_vmx_check_permission(vcpu))
		return 1;

	if (nested_vmx_get_vmptr(vcpu, &vmptr))
		return 1;

	if (!PAGE_ALIGNED(vmptr) || (vmptr >> cpuid_maxphyaddr(vcpu))) {
		nested_vmx_failValid(vcpu, VMXERR_VMPTRLD_INVALID_ADDRESS);
		return kvm_skip_emulated_instruction(vcpu);
	}

	if (vmptr == vmx->nested.vmxon_ptr) {
		nested_vmx_failValid(vcpu, VMXERR_VMPTRLD_VMXON_POINTER);
		return kvm_skip_emulated_instruction(vcpu);
	}

	if (vmx->nested.current_vmptr != vmptr) {
		struct vmcs12 *new_vmcs12;
		struct page *page;
		page = kvm_vcpu_gpa_to_page(vcpu, vmptr);
		if (is_error_page(page)) {
			nested_vmx_failInvalid(vcpu);
			return kvm_skip_emulated_instruction(vcpu);
		}
		new_vmcs12 = kmap(page);
		if (new_vmcs12->hdr.revision_id != VMCS12_REVISION ||
		    (new_vmcs12->hdr.shadow_vmcs &&
		     !nested_cpu_has_vmx_shadow_vmcs(vcpu))) {
			kunmap(page);
			kvm_release_page_clean(page);
			nested_vmx_failValid(vcpu,
				VMXERR_VMPTRLD_INCORRECT_VMCS_REVISION_ID);
			return kvm_skip_emulated_instruction(vcpu);
		}

		nested_release_vmcs12(vmx);
		/*
		 * Load VMCS12 from guest memory since it is not already
		 * cached.
		 */
		memcpy(vmx->nested.cached_vmcs12, new_vmcs12, VMCS12_SIZE);
		kunmap(page);
		kvm_release_page_clean(page);

		set_current_vmptr(vmx, vmptr);
	}

	nested_vmx_succeed(vcpu);
	return kvm_skip_emulated_instruction(vcpu);
}