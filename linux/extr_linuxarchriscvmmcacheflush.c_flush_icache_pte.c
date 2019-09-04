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
struct page {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  PG_dcache_clean ; 
 int /*<<< orphan*/  flush_icache_all () ; 
 struct page* pte_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void flush_icache_pte(pte_t pte)
{
	struct page *page = pte_page(pte);

	if (!test_and_set_bit(PG_dcache_clean, &page->flags))
		flush_icache_all();
}