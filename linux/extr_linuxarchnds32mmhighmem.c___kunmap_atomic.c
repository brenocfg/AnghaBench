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
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 scalar_t__ FIXADDR_START ; 
 int /*<<< orphan*/  __nds32__isb () ; 
 int /*<<< orphan*/  __nds32__tlbop_inv (unsigned long) ; 
 int /*<<< orphan*/  kmap_atomic_idx_pop () ; 
 int /*<<< orphan*/  pagefault_enable () ; 
 int /*<<< orphan*/  pmd_off_k (unsigned long) ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/ * pte_offset_kernel (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  set_pte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void __kunmap_atomic(void *kvaddr)
{
	if (kvaddr >= (void *)FIXADDR_START) {
		unsigned long vaddr = (unsigned long)kvaddr;
		pte_t *ptep;
		kmap_atomic_idx_pop();
		__nds32__tlbop_inv(vaddr);
		__nds32__isb();
		ptep = pte_offset_kernel(pmd_off_k(vaddr), vaddr);
		set_pte(ptep, 0);
	}
	pagefault_enable();
	preempt_enable();
}