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

/* Variables and functions */
 scalar_t__ arch_test_page_nodat (struct page*) ; 
 scalar_t__ page_address (struct page*) ; 
 scalar_t__ page_get_storage_key (unsigned long) ; 
 struct page* pfn_to_page (unsigned long) ; 

void page_key_read(unsigned long *pfn)
{
	struct page *page;
	unsigned long addr;
	unsigned char key;

	page = pfn_to_page(*pfn);
	addr = (unsigned long) page_address(page);
	key = (unsigned char) page_get_storage_key(addr) & 0x7f;
	if (arch_test_page_nodat(page))
		key |= 0x80;
	*(unsigned char *) pfn = key;
}