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
struct list_head {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  KMMIO_PAGE_HASH_BITS ; 
 size_t hash_long (unsigned long,int /*<<< orphan*/ ) ; 
 struct list_head* kmmio_page_table ; 
 int /*<<< orphan*/ * lookup_address (unsigned long,unsigned int*) ; 
 unsigned long page_level_mask (unsigned int) ; 

__attribute__((used)) static struct list_head *kmmio_page_list(unsigned long addr)
{
	unsigned int l;
	pte_t *pte = lookup_address(addr, &l);

	if (!pte)
		return NULL;
	addr &= page_level_mask(l);

	return &kmmio_page_table[hash_long(addr, KMMIO_PAGE_HASH_BITS)];
}