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

/* Variables and functions */
 int DIV_ROUND_UP (size_t,int /*<<< orphan*/ ) ; 
 int OPTEE_MSG_NONCONTIG_PAGE_SIZE ; 
 int /*<<< orphan*/  PAGELIST_ENTRIES_PER_PAGE ; 

__attribute__((used)) static size_t get_pages_list_size(size_t num_entries)
{
	int pages = DIV_ROUND_UP(num_entries, PAGELIST_ENTRIES_PER_PAGE);

	return pages * OPTEE_MSG_NONCONTIG_PAGE_SIZE;
}