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
 int /*<<< orphan*/  GFP_ATOMIC ; 
 unsigned long ZPCI_PTE_INVALID ; 
 int ZPCI_PT_ENTRIES ; 
 int /*<<< orphan*/  dma_page_table_cache ; 
 unsigned long* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long *dma_alloc_page_table(void)
{
	unsigned long *table, *entry;

	table = kmem_cache_alloc(dma_page_table_cache, GFP_ATOMIC);
	if (!table)
		return NULL;

	for (entry = table; entry < table + ZPCI_PT_ENTRIES; entry++)
		*entry = ZPCI_PTE_INVALID;
	return table;
}