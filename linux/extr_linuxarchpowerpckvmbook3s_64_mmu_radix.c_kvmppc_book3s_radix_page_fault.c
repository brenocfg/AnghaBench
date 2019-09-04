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
struct page {int dummy; } ;
struct TYPE_4__ {int fault_gpa; int /*<<< orphan*/  pgdir; } ;
struct kvm_vcpu {TYPE_2__ arch; struct kvm* kvm; } ;
struct kvm_run {int dummy; } ;
struct kvm_memory_slot {int flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  pgtable; } ;
struct kvm {unsigned long mmu_notifier_seq; int /*<<< orphan*/  mmu_lock; TYPE_1__ arch; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 unsigned long DSISR_BADACCESS ; 
 unsigned long DSISR_BAD_FAULT_64S ; 
 unsigned long DSISR_ISSTORE ; 
 unsigned long DSISR_NOHPTE ; 
 unsigned long DSISR_PROTFAULT ; 
 unsigned long DSISR_PRTABLE_FAULT ; 
 unsigned long DSISR_SET_RC ; 
 unsigned long DSISR_UNSUPP_MMU ; 
 long EAGAIN ; 
 int EFAULT ; 
 int KVM_MEMSLOT_INVALID ; 
 int KVM_MEM_READONLY ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 unsigned int PMD_SHIFT ; 
 unsigned long PMD_SIZE ; 
 unsigned int PUD_SHIFT ; 
 unsigned long PUD_SIZE ; 
 scalar_t__ PageReserved (struct page*) ; 
 int RESUME_GUEST ; 
 int _PAGE_ACCESSED ; 
 unsigned long _PAGE_DIRTY ; 
 int _PAGE_EXEC ; 
 int _PAGE_WRITE ; 
 int /*<<< orphan*/ * __find_linux_pte (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,unsigned int*) ; 
 int __get_user_pages_fast (unsigned long,int,int,struct page**) ; 
 unsigned long __gfn_to_pfn_memslot (struct kvm_memory_slot*,unsigned long,int,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  __pte (int) ; 
 unsigned long gfn_to_hva_memslot (struct kvm_memory_slot*,unsigned long) ; 
 struct kvm_memory_slot* gfn_to_memslot (struct kvm*,unsigned long) ; 
 scalar_t__ is_error_noslot_pfn (unsigned long) ; 
 int /*<<< orphan*/  kvmppc_core_queue_data_storage (struct kvm_vcpu*,unsigned long,unsigned long) ; 
 long kvmppc_create_pte (struct kvm*,int /*<<< orphan*/ ,unsigned long,unsigned int,unsigned long) ; 
 int kvmppc_hv_emulate_mmio (struct kvm_run*,struct kvm_vcpu*,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  kvmppc_radix_update_pte (struct kvm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,unsigned long,unsigned int) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 struct page* pfn_to_page (unsigned long) ; 
 scalar_t__ pfn_valid (unsigned long) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 scalar_t__ pte_present (int /*<<< orphan*/ ) ; 
 int pte_val (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_page_dirty_lock (struct page*) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int kvmppc_book3s_radix_page_fault(struct kvm_run *run, struct kvm_vcpu *vcpu,
				   unsigned long ea, unsigned long dsisr)
{
	struct kvm *kvm = vcpu->kvm;
	unsigned long mmu_seq;
	unsigned long gpa, gfn, hva;
	struct kvm_memory_slot *memslot;
	struct page *page = NULL;
	long ret;
	bool writing;
	bool upgrade_write = false;
	bool *upgrade_p = &upgrade_write;
	pte_t pte, *ptep;
	unsigned long pgflags;
	unsigned int shift, level;

	/* Check for unusual errors */
	if (dsisr & DSISR_UNSUPP_MMU) {
		pr_err("KVM: Got unsupported MMU fault\n");
		return -EFAULT;
	}
	if (dsisr & DSISR_BADACCESS) {
		/* Reflect to the guest as DSI */
		pr_err("KVM: Got radix HV page fault with DSISR=%lx\n", dsisr);
		kvmppc_core_queue_data_storage(vcpu, ea, dsisr);
		return RESUME_GUEST;
	}

	/* Translate the logical address and get the page */
	gpa = vcpu->arch.fault_gpa & ~0xfffUL;
	gpa &= ~0xF000000000000000ul;
	gfn = gpa >> PAGE_SHIFT;
	if (!(dsisr & DSISR_PRTABLE_FAULT))
		gpa |= ea & 0xfff;
	memslot = gfn_to_memslot(kvm, gfn);

	/* No memslot means it's an emulated MMIO region */
	if (!memslot || (memslot->flags & KVM_MEMSLOT_INVALID)) {
		if (dsisr & (DSISR_PRTABLE_FAULT | DSISR_BADACCESS |
			     DSISR_SET_RC)) {
			/*
			 * Bad address in guest page table tree, or other
			 * unusual error - reflect it to the guest as DSI.
			 */
			kvmppc_core_queue_data_storage(vcpu, ea, dsisr);
			return RESUME_GUEST;
		}
		return kvmppc_hv_emulate_mmio(run, vcpu, gpa, ea,
					      dsisr & DSISR_ISSTORE);
	}

	writing = (dsisr & DSISR_ISSTORE) != 0;
	if (memslot->flags & KVM_MEM_READONLY) {
		if (writing) {
			/* give the guest a DSI */
			dsisr = DSISR_ISSTORE | DSISR_PROTFAULT;
			kvmppc_core_queue_data_storage(vcpu, ea, dsisr);
			return RESUME_GUEST;
		}
		upgrade_p = NULL;
	}

	if (dsisr & DSISR_SET_RC) {
		/*
		 * Need to set an R or C bit in the 2nd-level tables;
		 * since we are just helping out the hardware here,
		 * it is sufficient to do what the hardware does.
		 */
		pgflags = _PAGE_ACCESSED;
		if (writing)
			pgflags |= _PAGE_DIRTY;
		/*
		 * We are walking the secondary page table here. We can do this
		 * without disabling irq.
		 */
		spin_lock(&kvm->mmu_lock);
		ptep = __find_linux_pte(kvm->arch.pgtable,
					gpa, NULL, &shift);
		if (ptep && pte_present(*ptep) &&
		    (!writing || pte_write(*ptep))) {
			kvmppc_radix_update_pte(kvm, ptep, 0, pgflags,
						gpa, shift);
			dsisr &= ~DSISR_SET_RC;
		}
		spin_unlock(&kvm->mmu_lock);
		if (!(dsisr & (DSISR_BAD_FAULT_64S | DSISR_NOHPTE |
			       DSISR_PROTFAULT | DSISR_SET_RC)))
			return RESUME_GUEST;
	}

	/* used to check for invalidations in progress */
	mmu_seq = kvm->mmu_notifier_seq;
	smp_rmb();

	/*
	 * Do a fast check first, since __gfn_to_pfn_memslot doesn't
	 * do it with !atomic && !async, which is how we call it.
	 * We always ask for write permission since the common case
	 * is that the page is writable.
	 */
	hva = gfn_to_hva_memslot(memslot, gfn);
	if (upgrade_p && __get_user_pages_fast(hva, 1, 1, &page) == 1) {
		upgrade_write = true;
	} else {
		unsigned long pfn;

		/* Call KVM generic code to do the slow-path check */
		pfn = __gfn_to_pfn_memslot(memslot, gfn, false, NULL,
					   writing, upgrade_p);
		if (is_error_noslot_pfn(pfn))
			return -EFAULT;
		page = NULL;
		if (pfn_valid(pfn)) {
			page = pfn_to_page(pfn);
			if (PageReserved(page))
				page = NULL;
		}
	}

	/*
	 * Read the PTE from the process' radix tree and use that
	 * so we get the shift and attribute bits.
	 */
	local_irq_disable();
	ptep = __find_linux_pte(vcpu->arch.pgdir, hva, NULL, &shift);
	/*
	 * If the PTE disappeared temporarily due to a THP
	 * collapse, just return and let the guest try again.
	 */
	if (!ptep) {
		local_irq_enable();
		if (page)
			put_page(page);
		return RESUME_GUEST;
	}
	pte = *ptep;
	local_irq_enable();

	/* Get pte level from shift/size */
	if (shift == PUD_SHIFT &&
	    (gpa & (PUD_SIZE - PAGE_SIZE)) ==
	    (hva & (PUD_SIZE - PAGE_SIZE))) {
		level = 2;
	} else if (shift == PMD_SHIFT &&
		   (gpa & (PMD_SIZE - PAGE_SIZE)) ==
		   (hva & (PMD_SIZE - PAGE_SIZE))) {
		level = 1;
	} else {
		level = 0;
		if (shift > PAGE_SHIFT) {
			/*
			 * If the pte maps more than one page, bring over
			 * bits from the virtual address to get the real
			 * address of the specific single page we want.
			 */
			unsigned long rpnmask = (1ul << shift) - PAGE_SIZE;
			pte = __pte(pte_val(pte) | (hva & rpnmask));
		}
	}

	pte = __pte(pte_val(pte) | _PAGE_EXEC | _PAGE_ACCESSED);
	if (writing || upgrade_write) {
		if (pte_val(pte) & _PAGE_WRITE)
			pte = __pte(pte_val(pte) | _PAGE_DIRTY);
	} else {
		pte = __pte(pte_val(pte) & ~(_PAGE_WRITE | _PAGE_DIRTY));
	}

	/* Allocate space in the tree and write the PTE */
	ret = kvmppc_create_pte(kvm, pte, gpa, level, mmu_seq);

	if (page) {
		if (!ret && (pte_val(pte) & _PAGE_WRITE))
			set_page_dirty_lock(page);
		put_page(page);
	}

	if (ret == 0 || ret == -EAGAIN)
		ret = RESUME_GUEST;
	return ret;
}