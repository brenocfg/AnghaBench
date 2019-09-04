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
struct mmu_notifier {int dummy; } ;
struct mm_struct {int dummy; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  __mn_flush_page (struct mmu_notifier*,unsigned long) ; 

__attribute__((used)) static int mn_clear_flush_young(struct mmu_notifier *mn,
				struct mm_struct *mm,
				unsigned long start,
				unsigned long end)
{
	for (; start < end; start += PAGE_SIZE)
		__mn_flush_page(mn, start);

	return 0;
}