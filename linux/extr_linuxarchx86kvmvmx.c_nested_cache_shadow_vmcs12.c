#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vmcs12 {unsigned long long vmcs_link_pointer; } ;
struct page {int dummy; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMCS12_SIZE ; 
 struct vmcs12* get_shadow_vmcs12 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  kvm_release_page_clean (struct page*) ; 
 struct page* kvm_vcpu_gpa_to_page (struct kvm_vcpu*,unsigned long long) ; 
 int /*<<< orphan*/  memcpy (struct vmcs12*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nested_cpu_has_shadow_vmcs (struct vmcs12*) ; 

__attribute__((used)) static void nested_cache_shadow_vmcs12(struct kvm_vcpu *vcpu,
				       struct vmcs12 *vmcs12)
{
	struct vmcs12 *shadow;
	struct page *page;

	if (!nested_cpu_has_shadow_vmcs(vmcs12) ||
	    vmcs12->vmcs_link_pointer == -1ull)
		return;

	shadow = get_shadow_vmcs12(vcpu);
	page = kvm_vcpu_gpa_to_page(vcpu, vmcs12->vmcs_link_pointer);

	memcpy(shadow, kmap(page), VMCS12_SIZE);

	kunmap(page);
	kvm_release_page_clean(page);
}