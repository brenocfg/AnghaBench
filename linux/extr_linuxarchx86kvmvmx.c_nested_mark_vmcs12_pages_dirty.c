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
struct vmcs12 {int virtual_apic_page_addr; int posted_intr_desc_addr; } ;
struct kvm_vcpu {int dummy; } ;
typedef  int gfn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_BASED_TPR_SHADOW ; 
 int PAGE_SHIFT ; 
 struct vmcs12* get_vmcs12 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_vcpu_mark_page_dirty (struct kvm_vcpu*,int) ; 
 scalar_t__ nested_cpu_has (struct vmcs12*,int /*<<< orphan*/ ) ; 
 scalar_t__ nested_cpu_has_posted_intr (struct vmcs12*) ; 

__attribute__((used)) static void nested_mark_vmcs12_pages_dirty(struct kvm_vcpu *vcpu)
{
	struct vmcs12 *vmcs12 = get_vmcs12(vcpu);
	gfn_t gfn;

	/*
	 * Don't need to mark the APIC access page dirty; it is never
	 * written to by the CPU during APIC virtualization.
	 */

	if (nested_cpu_has(vmcs12, CPU_BASED_TPR_SHADOW)) {
		gfn = vmcs12->virtual_apic_page_addr >> PAGE_SHIFT;
		kvm_vcpu_mark_page_dirty(vcpu, gfn);
	}

	if (nested_cpu_has_posted_intr(vmcs12)) {
		gfn = vmcs12->posted_intr_desc_addr >> PAGE_SHIFT;
		kvm_vcpu_mark_page_dirty(vcpu, gfn);
	}
}