#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int dummy; } ;
struct mm_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  is_lazy; int /*<<< orphan*/  loaded_mm; } ;

/* Variables and functions */
 TYPE_1__ cpu_tlbstate ; 
 int /*<<< orphan*/  init_mm ; 
 int /*<<< orphan*/  switch_mm (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_write (int /*<<< orphan*/ ,int) ; 
 scalar_t__ tlb_defer_switch_to_init_mm () ; 

void enter_lazy_tlb(struct mm_struct *mm, struct task_struct *tsk)
{
	if (this_cpu_read(cpu_tlbstate.loaded_mm) == &init_mm)
		return;

	if (tlb_defer_switch_to_init_mm()) {
		/*
		 * There's a significant optimization that may be possible
		 * here.  We have accurate enough TLB flush tracking that we
		 * don't need to maintain coherence of TLB per se when we're
		 * lazy.  We do, however, need to maintain coherence of
		 * paging-structure caches.  We could, in principle, leave our
		 * old mm loaded and only switch to init_mm when
		 * tlb_remove_page() happens.
		 */
		this_cpu_write(cpu_tlbstate.is_lazy, true);
	} else {
		switch_mm(NULL, &init_mm, NULL);
	}
}