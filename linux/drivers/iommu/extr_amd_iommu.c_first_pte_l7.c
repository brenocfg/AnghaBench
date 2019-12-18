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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 unsigned long PAGE_SIZE_PTE_COUNT (unsigned long) ; 
 unsigned long PTE_PAGE_SIZE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 *first_pte_l7(u64 *pte, unsigned long *page_size,
			 unsigned long *count)
{
	unsigned long pte_mask, pg_size, cnt;
	u64 *fpte;

	pg_size  = PTE_PAGE_SIZE(*pte);
	cnt      = PAGE_SIZE_PTE_COUNT(pg_size);
	pte_mask = ~((cnt << 3) - 1);
	fpte     = (u64 *)(((unsigned long)pte) & pte_mask);

	if (page_size)
		*page_size = pg_size;

	if (count)
		*count = cnt;

	return fpte;
}