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
struct TYPE_2__ {scalar_t__ revision_id; scalar_t__ shadow_vmcs; } ;
struct vmcs12 {unsigned long long vmcs_link_pointer; TYPE_1__ hdr; } ;
struct page {int dummy; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ VMCS12_REVISION ; 
 scalar_t__ is_error_page (struct page*) ; 
 struct vmcs12* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  kvm_release_page_clean (struct page*) ; 
 struct page* kvm_vcpu_gpa_to_page (struct kvm_vcpu*,unsigned long long) ; 
 scalar_t__ nested_cpu_has_shadow_vmcs (struct vmcs12*) ; 
 int /*<<< orphan*/  page_address_valid (struct kvm_vcpu*,unsigned long long) ; 

__attribute__((used)) static int nested_vmx_check_vmcs_link_ptr(struct kvm_vcpu *vcpu,
					  struct vmcs12 *vmcs12)
{
	int r;
	struct page *page;
	struct vmcs12 *shadow;

	if (vmcs12->vmcs_link_pointer == -1ull)
		return 0;

	if (!page_address_valid(vcpu, vmcs12->vmcs_link_pointer))
		return -EINVAL;

	page = kvm_vcpu_gpa_to_page(vcpu, vmcs12->vmcs_link_pointer);
	if (is_error_page(page))
		return -EINVAL;

	r = 0;
	shadow = kmap(page);
	if (shadow->hdr.revision_id != VMCS12_REVISION ||
	    shadow->hdr.shadow_vmcs != nested_cpu_has_shadow_vmcs(vmcs12))
		r = -EINVAL;
	kunmap(page);
	kvm_release_page_clean(page);
	return r;
}