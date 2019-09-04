#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {int dummy; } ;
struct tlb_info {unsigned long long next; unsigned long long last; unsigned long long first; } ;
struct TYPE_4__ {unsigned long long pte_low; } ;
typedef  TYPE_1__ pte_t ;
struct TYPE_5__ {struct tlb_info dtlb; struct tlb_info itlb; } ;

/* Variables and functions */
 unsigned int FAULT_CODE_ITLB ; 
 unsigned long MMU_VPN_MASK ; 
 unsigned long long PTEH_ASID_SHIFT ; 
 unsigned long long PTEH_VALID ; 
 unsigned long long TLB_STEP ; 
 unsigned long long _PAGE_FLAGS_HARDWARE_MASK ; 
 int /*<<< orphan*/  __flush_tlb_slot (unsigned long long) ; 
 TYPE_2__* cpu_data ; 
 unsigned long long get_asid () ; 
 unsigned int get_thread_fault_code () ; 
 unsigned long long neff_sign_extend (unsigned long) ; 

void __update_tlb(struct vm_area_struct *vma, unsigned long address, pte_t pte)
{
	unsigned long long ptel;
	unsigned long long pteh=0;
	struct tlb_info *tlbp;
	unsigned long long next;
	unsigned int fault_code = get_thread_fault_code();

	/* Get PTEL first */
	ptel = pte.pte_low;

	/*
	 * Set PTEH register
	 */
	pteh = neff_sign_extend(address & MMU_VPN_MASK);

	/* Set the ASID. */
	pteh |= get_asid() << PTEH_ASID_SHIFT;
	pteh |= PTEH_VALID;

	/* Set PTEL register, set_pte has performed the sign extension */
	ptel &= _PAGE_FLAGS_HARDWARE_MASK; /* drop software flags */

	if (fault_code & FAULT_CODE_ITLB)
		tlbp = &cpu_data->itlb;
	else
		tlbp = &cpu_data->dtlb;

	next = tlbp->next;
	__flush_tlb_slot(next);
	asm volatile ("putcfg %0,1,%2\n\n\t"
		      "putcfg %0,0,%1\n"
		      :  : "r" (next), "r" (pteh), "r" (ptel) );

	next += TLB_STEP;
	if (next > tlbp->last)
		next = tlbp->first;
	tlbp->next = next;
}