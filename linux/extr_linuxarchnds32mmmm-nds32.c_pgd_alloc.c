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
struct mm_struct {int dummy; } ;
typedef  int pgd_t ;

/* Variables and functions */
 int FIRST_KERNEL_PGD_NR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NR_PAGETABLE ; 
 int PTRS_PER_PGD ; 
 scalar_t__ __get_free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_dcache_wb_range (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  inc_zone_page_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int* pgd_offset_k (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_page (unsigned long*) ; 

pgd_t *pgd_alloc(struct mm_struct *mm)
{
	pgd_t *new_pgd, *init_pgd;
	int i;

	new_pgd = (pgd_t *) __get_free_pages(GFP_KERNEL, 0);
	if (!new_pgd)
		return NULL;
	for (i = 0; i < PTRS_PER_PGD; i++) {
		(*new_pgd) = 1;
		new_pgd++;
	}
	new_pgd -= PTRS_PER_PGD;

	init_pgd = pgd_offset_k(0);

	memcpy(new_pgd + FIRST_KERNEL_PGD_NR, init_pgd + FIRST_KERNEL_PGD_NR,
	       (PTRS_PER_PGD - FIRST_KERNEL_PGD_NR) * sizeof(pgd_t));

	cpu_dcache_wb_range((unsigned long)new_pgd,
			    (unsigned long)new_pgd +
			    PTRS_PER_PGD * sizeof(pgd_t));
	inc_zone_page_state(virt_to_page((unsigned long *)new_pgd),
			    NR_PAGETABLE);

	return new_pgd;
}