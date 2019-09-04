#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct vmcs12 {scalar_t__ guest_pml_index; int /*<<< orphan*/  pml_address; } ;
struct TYPE_2__ {int pml_full; } ;
struct vcpu_vmx {TYPE_1__ nested; } ;
struct page {int dummy; } ;
struct kvm_vcpu {int dummy; } ;
typedef  int gpa_t ;

/* Variables and functions */
 int /*<<< orphan*/  GUEST_PHYSICAL_ADDRESS ; 
 scalar_t__ PML_ENTITY_NUM ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct vmcs12* get_vmcs12 (struct kvm_vcpu*) ; 
 scalar_t__ is_error_page (struct page*) ; 
 scalar_t__ is_guest_mode (struct kvm_vcpu*) ; 
 int* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  kvm_release_page_clean (struct page*) ; 
 struct page* kvm_vcpu_gpa_to_page (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nested_cpu_has_pml (struct vmcs12*) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 int vmcs_read64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vmx_write_pml_buffer(struct kvm_vcpu *vcpu)
{
	struct vmcs12 *vmcs12;
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	gpa_t gpa;
	struct page *page = NULL;
	u64 *pml_address;

	if (is_guest_mode(vcpu)) {
		WARN_ON_ONCE(vmx->nested.pml_full);

		/*
		 * Check if PML is enabled for the nested guest.
		 * Whether eptp bit 6 is set is already checked
		 * as part of A/D emulation.
		 */
		vmcs12 = get_vmcs12(vcpu);
		if (!nested_cpu_has_pml(vmcs12))
			return 0;

		if (vmcs12->guest_pml_index >= PML_ENTITY_NUM) {
			vmx->nested.pml_full = true;
			return 1;
		}

		gpa = vmcs_read64(GUEST_PHYSICAL_ADDRESS) & ~0xFFFull;

		page = kvm_vcpu_gpa_to_page(vcpu, vmcs12->pml_address);
		if (is_error_page(page))
			return 0;

		pml_address = kmap(page);
		pml_address[vmcs12->guest_pml_index--] = gpa;
		kunmap(page);
		kvm_release_page_clean(page);
	}

	return 0;
}