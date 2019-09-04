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
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 scalar_t__ FIX_KMAP_BEGIN ; 
 int KM_TYPE_NR ; 
 unsigned long __fix_to_virt (scalar_t__) ; 
 int /*<<< orphan*/  arch_flush_lazy_mmu_mode () ; 
 int kmap_atomic_idx_push () ; 
 scalar_t__ kmap_pte ; 
 int /*<<< orphan*/  pagefault_disable () ; 
 int /*<<< orphan*/  pfn_pte (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  set_pte (scalar_t__,int /*<<< orphan*/ ) ; 
 int smp_processor_id () ; 

void *kmap_atomic_prot_pfn(unsigned long pfn, pgprot_t prot)
{
	unsigned long vaddr;
	int idx, type;

	preempt_disable();
	pagefault_disable();

	type = kmap_atomic_idx_push();
	idx = type + KM_TYPE_NR * smp_processor_id();
	vaddr = __fix_to_virt(FIX_KMAP_BEGIN + idx);
	set_pte(kmap_pte - idx, pfn_pte(pfn, prot));
	arch_flush_lazy_mmu_mode();

	return (void *)vaddr;
}