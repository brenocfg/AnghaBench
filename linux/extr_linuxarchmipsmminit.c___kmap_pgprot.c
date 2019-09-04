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
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pgprot_t ;
typedef  enum fixed_addresses { ____Placeholder_fixed_addresses } fixed_addresses ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ FIX_CMAP_END ; 
 int FIX_N_COLOURS ; 
 int PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  Page_dcache_dirty (struct page*) ; 
 unsigned long __fix_to_virt (scalar_t__) ; 
 scalar_t__ in_interrupt () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mk_pte (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtc0_tlbw_hazard () ; 
 int num_wired_entries () ; 
 int /*<<< orphan*/  pagefault_disable () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 unsigned long pte_to_entrylo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_val (int /*<<< orphan*/ ) ; 
 unsigned long read_c0_entryhi () ; 
 int /*<<< orphan*/  tlb_write_indexed () ; 
 int /*<<< orphan*/  tlbw_use_hazard () ; 
 int /*<<< orphan*/  write_c0_entryhi (unsigned long) ; 
 int /*<<< orphan*/  write_c0_entrylo0 (unsigned long) ; 
 int /*<<< orphan*/  write_c0_entrylo1 (unsigned long) ; 
 int /*<<< orphan*/  write_c0_index (int) ; 
 int /*<<< orphan*/  write_c0_wired (int) ; 

__attribute__((used)) static void *__kmap_pgprot(struct page *page, unsigned long addr, pgprot_t prot)
{
	enum fixed_addresses idx;
	unsigned long vaddr, flags, entrylo;
	unsigned long old_ctx;
	pte_t pte;
	int tlbidx;

	BUG_ON(Page_dcache_dirty(page));

	preempt_disable();
	pagefault_disable();
	idx = (addr >> PAGE_SHIFT) & (FIX_N_COLOURS - 1);
	idx += in_interrupt() ? FIX_N_COLOURS : 0;
	vaddr = __fix_to_virt(FIX_CMAP_END - idx);
	pte = mk_pte(page, prot);
#if defined(CONFIG_XPA)
	entrylo = pte_to_entrylo(pte.pte_high);
#elif defined(CONFIG_PHYS_ADDR_T_64BIT) && defined(CONFIG_CPU_MIPS32)
	entrylo = pte.pte_high;
#else
	entrylo = pte_to_entrylo(pte_val(pte));
#endif

	local_irq_save(flags);
	old_ctx = read_c0_entryhi();
	write_c0_entryhi(vaddr & (PAGE_MASK << 1));
	write_c0_entrylo0(entrylo);
	write_c0_entrylo1(entrylo);
#ifdef CONFIG_XPA
	if (cpu_has_xpa) {
		entrylo = (pte.pte_low & _PFNX_MASK);
		writex_c0_entrylo0(entrylo);
		writex_c0_entrylo1(entrylo);
	}
#endif
	tlbidx = num_wired_entries();
	write_c0_wired(tlbidx + 1);
	write_c0_index(tlbidx);
	mtc0_tlbw_hazard();
	tlb_write_indexed();
	tlbw_use_hazard();
	write_c0_entryhi(old_ctx);
	local_irq_restore(flags);

	return (void*) vaddr;
}