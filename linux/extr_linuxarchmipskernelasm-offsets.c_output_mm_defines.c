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
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLANK () ; 
 int /*<<< orphan*/  COMMENT (char*) ; 
 int /*<<< orphan*/  DEFINE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MM_CONTEXT ; 
 int /*<<< orphan*/  MM_PGD ; 
 int /*<<< orphan*/  MM_USERS ; 
 int /*<<< orphan*/  OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int PGDIR_SHIFT ; 
 int PGD_ORDER ; 
 int PGD_T_LOG2 ; 
 int PMD_ORDER ; 
 int PMD_SHIFT ; 
 int PMD_T_LOG2 ; 
 int PTE_ORDER ; 
 int PTE_T_LOG2 ; 
 int PTRS_PER_PGD ; 
 int PTRS_PER_PMD ; 
 int PTRS_PER_PTE ; 
 int /*<<< orphan*/  STRUCT_PAGE_SIZE ; 
 int /*<<< orphan*/  _PAGE_SHIFT ; 
 int /*<<< orphan*/  _PAGE_SIZE ; 
 int /*<<< orphan*/  _PGDIR_SHIFT ; 
 int /*<<< orphan*/  _PGD_ORDER ; 
 int /*<<< orphan*/  _PGD_T_LOG2 ; 
 int /*<<< orphan*/  _PGD_T_SIZE ; 
 int /*<<< orphan*/  _PMD_ORDER ; 
 int /*<<< orphan*/  _PMD_SHIFT ; 
 int /*<<< orphan*/  _PMD_T_LOG2 ; 
 int /*<<< orphan*/  _PMD_T_SIZE ; 
 int /*<<< orphan*/  _PTE_ORDER ; 
 int /*<<< orphan*/  _PTE_T_LOG2 ; 
 int /*<<< orphan*/  _PTE_T_SIZE ; 
 int /*<<< orphan*/  _PTRS_PER_PGD ; 
 int /*<<< orphan*/  _PTRS_PER_PMD ; 
 int /*<<< orphan*/  _PTRS_PER_PTE ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  mm_struct ; 
 int /*<<< orphan*/  mm_users ; 
 int /*<<< orphan*/  pgd ; 

void output_mm_defines(void)
{
	COMMENT("Size of struct page");
	DEFINE(STRUCT_PAGE_SIZE, sizeof(struct page));
	BLANK();
	COMMENT("Linux mm_struct offsets.");
	OFFSET(MM_USERS, mm_struct, mm_users);
	OFFSET(MM_PGD, mm_struct, pgd);
	OFFSET(MM_CONTEXT, mm_struct, context);
	BLANK();
	DEFINE(_PGD_T_SIZE, sizeof(pgd_t));
	DEFINE(_PMD_T_SIZE, sizeof(pmd_t));
	DEFINE(_PTE_T_SIZE, sizeof(pte_t));
	BLANK();
	DEFINE(_PGD_T_LOG2, PGD_T_LOG2);
#ifndef __PAGETABLE_PMD_FOLDED
	DEFINE(_PMD_T_LOG2, PMD_T_LOG2);
#endif
	DEFINE(_PTE_T_LOG2, PTE_T_LOG2);
	BLANK();
	DEFINE(_PGD_ORDER, PGD_ORDER);
#ifndef __PAGETABLE_PMD_FOLDED
	DEFINE(_PMD_ORDER, PMD_ORDER);
#endif
	DEFINE(_PTE_ORDER, PTE_ORDER);
	BLANK();
	DEFINE(_PMD_SHIFT, PMD_SHIFT);
	DEFINE(_PGDIR_SHIFT, PGDIR_SHIFT);
	BLANK();
	DEFINE(_PTRS_PER_PGD, PTRS_PER_PGD);
	DEFINE(_PTRS_PER_PMD, PTRS_PER_PMD);
	DEFINE(_PTRS_PER_PTE, PTRS_PER_PTE);
	BLANK();
	DEFINE(_PAGE_SHIFT, PAGE_SHIFT);
	DEFINE(_PAGE_SIZE, PAGE_SIZE);
	BLANK();
}