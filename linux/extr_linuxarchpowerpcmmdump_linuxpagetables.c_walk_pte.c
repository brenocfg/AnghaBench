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
struct pg_state {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 unsigned int PAGE_SIZE ; 
 unsigned int PTRS_PER_PTE ; 
 int /*<<< orphan*/  note_page (struct pg_state*,unsigned long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_val (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void walk_pte(struct pg_state *st, pmd_t *pmd, unsigned long start)
{
	pte_t *pte = pte_offset_kernel(pmd, 0);
	unsigned long addr;
	unsigned int i;

	for (i = 0; i < PTRS_PER_PTE; i++, pte++) {
		addr = start + i * PAGE_SIZE;
		note_page(st, addr, 4, pte_val(*pte));

	}
}