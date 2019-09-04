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
struct TYPE_2__ {int /*<<< orphan*/  mmu_valid_gen; } ;
struct kvm {int /*<<< orphan*/  mmu_lock; TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_reload_remote_mmus (struct kvm*) ; 
 int /*<<< orphan*/  kvm_zap_obsolete_pages (struct kvm*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_kvm_mmu_invalidate_zap_all_pages (struct kvm*) ; 

void kvm_mmu_invalidate_zap_all_pages(struct kvm *kvm)
{
	spin_lock(&kvm->mmu_lock);
	trace_kvm_mmu_invalidate_zap_all_pages(kvm);
	kvm->arch.mmu_valid_gen++;

	/*
	 * Notify all vcpus to reload its shadow page table
	 * and flush TLB. Then all vcpus will switch to new
	 * shadow page table with the new mmu_valid_gen.
	 *
	 * Note: we should do this under the protection of
	 * mmu-lock, otherwise, vcpu would purge shadow page
	 * but miss tlb flush.
	 */
	kvm_reload_remote_mmus(kvm);

	kvm_zap_obsolete_pages(kvm);
	spin_unlock(&kvm->mmu_lock);
}