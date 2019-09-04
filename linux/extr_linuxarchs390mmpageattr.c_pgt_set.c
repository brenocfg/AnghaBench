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
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
struct TYPE_2__ {int /*<<< orphan*/  kernel_asce; } ;

/* Variables and functions */
#define  CRDTE_DTT_PAGE 130 
#define  CRDTE_DTT_REGION3 129 
#define  CRDTE_DTT_SEGMENT 128 
 scalar_t__ MACHINE_HAS_EDAT2 ; 
 scalar_t__ MACHINE_HAS_IDTE ; 
 int PTRS_PER_PMD ; 
 int PTRS_PER_PTE ; 
 int PTRS_PER_PUD ; 
 TYPE_1__ S390_lowcore ; 
 int /*<<< orphan*/  crdte (unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csp (unsigned int*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  cspg (unsigned long*,unsigned long,unsigned long) ; 

__attribute__((used)) static void pgt_set(unsigned long *old, unsigned long new, unsigned long addr,
		    unsigned long dtt)
{
	unsigned long table, mask;

	mask = 0;
	if (MACHINE_HAS_EDAT2) {
		switch (dtt) {
		case CRDTE_DTT_REGION3:
			mask = ~(PTRS_PER_PUD * sizeof(pud_t) - 1);
			break;
		case CRDTE_DTT_SEGMENT:
			mask = ~(PTRS_PER_PMD * sizeof(pmd_t) - 1);
			break;
		case CRDTE_DTT_PAGE:
			mask = ~(PTRS_PER_PTE * sizeof(pte_t) - 1);
			break;
		}
		table = (unsigned long)old & mask;
		crdte(*old, new, table, dtt, addr, S390_lowcore.kernel_asce);
	} else if (MACHINE_HAS_IDTE) {
		cspg(old, *old, new);
	} else {
		csp((unsigned int *)old + 1, *old, new);
	}
}