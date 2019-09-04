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
struct kvm_mmu_memory_cache {int dummy; } ;
struct TYPE_2__ {struct kvm_mmu_memory_cache mmu_page_cache; } ;
struct kvm_vcpu {TYPE_1__ arch; struct kvm* kvm; } ;
struct kvm {unsigned long mmu_notifier_seq; int /*<<< orphan*/  srcu; int /*<<< orphan*/  mmu_lock; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  kvm_pfn_t ;
typedef  unsigned long gfn_t ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  KVM_MMU_CACHE_MIN_PAGES ; 
 int /*<<< orphan*/  KVM_NR_MEM_OBJS ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long _PAGE_PRESENT ; 
 unsigned long _PAGE_WRITE ; 
 unsigned long __READABLE ; 
 unsigned long __WRITEABLE ; 
 int /*<<< orphan*/  __pgprot (unsigned long) ; 
 int _kvm_mips_map_page_fast (struct kvm_vcpu*,unsigned long,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned long _page_cachable_default ; 
 int /*<<< orphan*/  gfn_to_pfn_prot (struct kvm*,unsigned long,int,int*) ; 
 scalar_t__ is_error_noslot_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kvm_mips_pte_for_gpa (struct kvm*,struct kvm_mmu_memory_cache*,unsigned long) ; 
 int /*<<< orphan*/  kvm_release_pfn_clean (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_set_pfn_accessed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_set_pfn_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_page_dirty (struct kvm*,unsigned long) ; 
 scalar_t__ mmu_notifier_retry (struct kvm*,unsigned long) ; 
 int mmu_topup_memory_cache (struct kvm_mmu_memory_cache*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfn_pte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ptep_buddy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_pte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int kvm_mips_map_page(struct kvm_vcpu *vcpu, unsigned long gpa,
			     bool write_fault,
			     pte_t *out_entry, pte_t *out_buddy)
{
	struct kvm *kvm = vcpu->kvm;
	struct kvm_mmu_memory_cache *memcache = &vcpu->arch.mmu_page_cache;
	gfn_t gfn = gpa >> PAGE_SHIFT;
	int srcu_idx, err;
	kvm_pfn_t pfn;
	pte_t *ptep, entry, old_pte;
	bool writeable;
	unsigned long prot_bits;
	unsigned long mmu_seq;

	/* Try the fast path to handle old / clean pages */
	srcu_idx = srcu_read_lock(&kvm->srcu);
	err = _kvm_mips_map_page_fast(vcpu, gpa, write_fault, out_entry,
				      out_buddy);
	if (!err)
		goto out;

	/* We need a minimum of cached pages ready for page table creation */
	err = mmu_topup_memory_cache(memcache, KVM_MMU_CACHE_MIN_PAGES,
				     KVM_NR_MEM_OBJS);
	if (err)
		goto out;

retry:
	/*
	 * Used to check for invalidations in progress, of the pfn that is
	 * returned by pfn_to_pfn_prot below.
	 */
	mmu_seq = kvm->mmu_notifier_seq;
	/*
	 * Ensure the read of mmu_notifier_seq isn't reordered with PTE reads in
	 * gfn_to_pfn_prot() (which calls get_user_pages()), so that we don't
	 * risk the page we get a reference to getting unmapped before we have a
	 * chance to grab the mmu_lock without mmu_notifier_retry() noticing.
	 *
	 * This smp_rmb() pairs with the effective smp_wmb() of the combination
	 * of the pte_unmap_unlock() after the PTE is zapped, and the
	 * spin_lock() in kvm_mmu_notifier_invalidate_<page|range_end>() before
	 * mmu_notifier_seq is incremented.
	 */
	smp_rmb();

	/* Slow path - ask KVM core whether we can access this GPA */
	pfn = gfn_to_pfn_prot(kvm, gfn, write_fault, &writeable);
	if (is_error_noslot_pfn(pfn)) {
		err = -EFAULT;
		goto out;
	}

	spin_lock(&kvm->mmu_lock);
	/* Check if an invalidation has taken place since we got pfn */
	if (mmu_notifier_retry(kvm, mmu_seq)) {
		/*
		 * This can happen when mappings are changed asynchronously, but
		 * also synchronously if a COW is triggered by
		 * gfn_to_pfn_prot().
		 */
		spin_unlock(&kvm->mmu_lock);
		kvm_release_pfn_clean(pfn);
		goto retry;
	}

	/* Ensure page tables are allocated */
	ptep = kvm_mips_pte_for_gpa(kvm, memcache, gpa);

	/* Set up the PTE */
	prot_bits = _PAGE_PRESENT | __READABLE | _page_cachable_default;
	if (writeable) {
		prot_bits |= _PAGE_WRITE;
		if (write_fault) {
			prot_bits |= __WRITEABLE;
			mark_page_dirty(kvm, gfn);
			kvm_set_pfn_dirty(pfn);
		}
	}
	entry = pfn_pte(pfn, __pgprot(prot_bits));

	/* Write the PTE */
	old_pte = *ptep;
	set_pte(ptep, entry);

	err = 0;
	if (out_entry)
		*out_entry = *ptep;
	if (out_buddy)
		*out_buddy = *ptep_buddy(ptep);

	spin_unlock(&kvm->mmu_lock);
	kvm_release_pfn_clean(pfn);
	kvm_set_pfn_accessed(pfn);
out:
	srcu_read_unlock(&kvm->srcu, srcu_idx);
	return err;
}