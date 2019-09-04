#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pte_t ;
struct TYPE_3__ {int* pmdv; } ;
typedef  TYPE_1__ pmd_t ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int PTRS_PER_PTE ; 
 int SRMMU_PTD_PMASK ; 
 void* __nocache_va (int) ; 

pte_t *pte_offset_kernel(pmd_t *dir, unsigned long address)
{
	void *pte;

	pte = __nocache_va((dir->pmdv[0] & SRMMU_PTD_PMASK) << 4);
	return (pte_t *) pte +
	    ((address >> PAGE_SHIFT) & (PTRS_PER_PTE - 1));
}