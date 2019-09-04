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
typedef  int /*<<< orphan*/  efi_system_table_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_ALLOC_ALIGN ; 
 unsigned long EFI_PAGE_SIZE ; 
 int /*<<< orphan*/  efi_call_early (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  free_pages ; 
 unsigned long round_up (unsigned long,int /*<<< orphan*/ ) ; 

void efi_free(efi_system_table_t *sys_table_arg, unsigned long size,
	      unsigned long addr)
{
	unsigned long nr_pages;

	if (!size)
		return;

	nr_pages = round_up(size, EFI_ALLOC_ALIGN) / EFI_PAGE_SIZE;
	efi_call_early(free_pages, addr, nr_pages);
}