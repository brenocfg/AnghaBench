#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct kvm_vcpu {TYPE_2__* kvm; } ;
struct TYPE_5__ {int /*<<< orphan*/  mmu_recycled; } ;
struct TYPE_6__ {TYPE_1__ stat; } ;

/* Variables and functions */
 int ENOSPC ; 
 scalar_t__ KVM_MIN_FREE_MMU_PAGES ; 
 scalar_t__ KVM_REFILL_PAGES ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invalid_list ; 
 scalar_t__ kvm_mmu_available_pages (TYPE_2__*) ; 
 int /*<<< orphan*/  kvm_mmu_commit_zap_page (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  prepare_zap_oldest_mmu_page (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int make_mmu_pages_available(struct kvm_vcpu *vcpu)
{
	LIST_HEAD(invalid_list);

	if (likely(kvm_mmu_available_pages(vcpu->kvm) >= KVM_MIN_FREE_MMU_PAGES))
		return 0;

	while (kvm_mmu_available_pages(vcpu->kvm) < KVM_REFILL_PAGES) {
		if (!prepare_zap_oldest_mmu_page(vcpu->kvm, &invalid_list))
			break;

		++vcpu->kvm->stat.mmu_recycled;
	}
	kvm_mmu_commit_zap_page(vcpu->kvm, &invalid_list);

	if (!kvm_mmu_available_pages(vcpu->kvm))
		return -ENOSPC;
	return 0;
}