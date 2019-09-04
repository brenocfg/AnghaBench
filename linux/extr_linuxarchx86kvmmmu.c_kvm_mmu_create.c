#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint ;
struct TYPE_5__ {int /*<<< orphan*/ * prev_roots; int /*<<< orphan*/  translate_gpa; int /*<<< orphan*/  root_hpa; } ;
struct TYPE_4__ {int /*<<< orphan*/  translate_gpa; } ;
struct TYPE_6__ {TYPE_2__ mmu; TYPE_1__ nested_mmu; TYPE_2__* walk_mmu; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_PAGE ; 
 size_t KVM_MMU_NUM_PREV_ROOTS ; 
 int /*<<< orphan*/  KVM_MMU_ROOT_INFO_INVALID ; 
 int alloc_mmu_pages (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  translate_gpa ; 
 int /*<<< orphan*/  translate_nested_gpa ; 

int kvm_mmu_create(struct kvm_vcpu *vcpu)
{
	uint i;

	vcpu->arch.walk_mmu = &vcpu->arch.mmu;
	vcpu->arch.mmu.root_hpa = INVALID_PAGE;
	vcpu->arch.mmu.translate_gpa = translate_gpa;
	vcpu->arch.nested_mmu.translate_gpa = translate_nested_gpa;

	for (i = 0; i < KVM_MMU_NUM_PREV_ROOTS; i++)
		vcpu->arch.mmu.prev_roots[i] = KVM_MMU_ROOT_INFO_INVALID;

	return alloc_mmu_pages(vcpu);
}