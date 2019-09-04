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
struct page_change_data {void* clear_mask; void* set_mask; } ;
typedef  void* pgprot_t ;

/* Variables and functions */
 int apply_to_page_range (int /*<<< orphan*/ *,unsigned long,unsigned long,int /*<<< orphan*/ ,struct page_change_data*) ; 
 int /*<<< orphan*/  change_page_range ; 
 int /*<<< orphan*/  flush_tlb_kernel_range (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  init_mm ; 

__attribute__((used)) static int __change_memory_common(unsigned long start, unsigned long size,
				pgprot_t set_mask, pgprot_t clear_mask)
{
	struct page_change_data data;
	int ret;

	data.set_mask = set_mask;
	data.clear_mask = clear_mask;

	ret = apply_to_page_range(&init_mm, start, size, change_page_range,
					&data);

	flush_tlb_kernel_range(start, start + size);
	return ret;
}