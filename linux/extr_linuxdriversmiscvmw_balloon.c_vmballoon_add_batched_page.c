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
typedef  int u64 ;
struct vmballoon {int /*<<< orphan*/  batch_page; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 scalar_t__ page_to_pfn (struct page*) ; 
 int /*<<< orphan*/  vmballoon_batch_set_pa (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void vmballoon_add_batched_page(struct vmballoon *b, int idx,
				struct page *p)
{
	vmballoon_batch_set_pa(b->batch_page, idx,
			(u64)page_to_pfn(p) << PAGE_SHIFT);
}