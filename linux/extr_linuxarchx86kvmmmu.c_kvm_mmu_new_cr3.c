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
struct kvm_vcpu {int dummy; } ;
typedef  int /*<<< orphan*/  gpa_t ;

/* Variables and functions */
 int /*<<< orphan*/  __kvm_mmu_new_cr3 (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kvm_mmu_calc_root_page_role (struct kvm_vcpu*) ; 

void kvm_mmu_new_cr3(struct kvm_vcpu *vcpu, gpa_t new_cr3, bool skip_tlb_flush)
{
	__kvm_mmu_new_cr3(vcpu, new_cr3, kvm_mmu_calc_root_page_role(vcpu),
			  skip_tlb_flush);
}