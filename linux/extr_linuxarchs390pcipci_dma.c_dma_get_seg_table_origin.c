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
 unsigned long* dma_alloc_cpu_table () ; 
 int /*<<< orphan*/  entry_clr_protected (unsigned long*) ; 
 unsigned long* get_rt_sto (unsigned long) ; 
 scalar_t__ reg_entry_isvalid (unsigned long) ; 
 int /*<<< orphan*/  set_rt_sto (unsigned long*,unsigned long*) ; 
 int /*<<< orphan*/  validate_rt_entry (unsigned long*) ; 

__attribute__((used)) static unsigned long *dma_get_seg_table_origin(unsigned long *entry)
{
	unsigned long *sto;

	if (reg_entry_isvalid(*entry))
		sto = get_rt_sto(*entry);
	else {
		sto = dma_alloc_cpu_table();
		if (!sto)
			return NULL;

		set_rt_sto(entry, sto);
		validate_rt_entry(entry);
		entry_clr_protected(entry);
	}
	return sto;
}