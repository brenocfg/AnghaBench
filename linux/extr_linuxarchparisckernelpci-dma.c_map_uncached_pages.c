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
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned long PGDIR_SIZE ; 
 scalar_t__ map_pmd_uncached (int /*<<< orphan*/ *,unsigned long,unsigned long,unsigned long*) ; 
 int /*<<< orphan*/ * pgd_offset_k (unsigned long) ; 
 int /*<<< orphan*/ * pmd_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline int map_uncached_pages(unsigned long vaddr, unsigned long size,
		unsigned long paddr)
{
	pgd_t * dir;
	unsigned long end = vaddr + size;

	dir = pgd_offset_k(vaddr);
	do {
		pmd_t *pmd;
		
		pmd = pmd_alloc(NULL, dir, vaddr);
		if (!pmd)
			return -ENOMEM;
		if (map_pmd_uncached(pmd, vaddr, end - vaddr, &paddr))
			return -ENOMEM;
		vaddr = vaddr + PGDIR_SIZE;
		dir++;
	} while (vaddr && (vaddr < end));
	return 0;
}