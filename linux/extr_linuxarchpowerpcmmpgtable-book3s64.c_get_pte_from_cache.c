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
struct TYPE_2__ {void* pte_frag; } ;
struct mm_struct {int /*<<< orphan*/  page_table_lock; TYPE_1__ context; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 int PTE_FRAG_SIZE ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static pte_t *get_pte_from_cache(struct mm_struct *mm)
{
	void *pte_frag, *ret;

	spin_lock(&mm->page_table_lock);
	ret = mm->context.pte_frag;
	if (ret) {
		pte_frag = ret + PTE_FRAG_SIZE;
		/*
		 * If we have taken up all the fragments mark PTE page NULL
		 */
		if (((unsigned long)pte_frag & ~PAGE_MASK) == 0)
			pte_frag = NULL;
		mm->context.pte_frag = pte_frag;
	}
	spin_unlock(&mm->page_table_lock);
	return (pte_t *)ret;
}