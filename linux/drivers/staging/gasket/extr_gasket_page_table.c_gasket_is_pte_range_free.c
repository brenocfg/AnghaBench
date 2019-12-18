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
typedef  int uint ;
struct gasket_page_table_entry {scalar_t__ status; } ;

/* Variables and functions */
 scalar_t__ PTE_FREE ; 

__attribute__((used)) static bool gasket_is_pte_range_free(struct gasket_page_table_entry *ptes,
				     uint num_entries)
{
	int i;

	for (i = 0; i < num_entries; i++) {
		if (ptes[i].status != PTE_FREE)
			return false;
	}

	return true;
}