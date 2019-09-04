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
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */

__attribute__((used)) static inline void resume_init_first_level_page_table(pgd_t *pg_dir)
{
#ifdef CONFIG_X86_PAE
	int i;

	/* Init entries of the first-level page table to the zero page */
	for (i = 0; i < PTRS_PER_PGD; i++)
		set_pgd(pg_dir + i,
			__pgd(__pa(empty_zero_page) | _PAGE_PRESENT));
#endif
}