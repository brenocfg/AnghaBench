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
struct mm_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  is_lazy; int /*<<< orphan*/  loaded_mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 TYPE_1__ cpu_tlbstate ; 
 struct mm_struct init_mm ; 
 int /*<<< orphan*/  switch_mm (int /*<<< orphan*/ *,struct mm_struct*,int /*<<< orphan*/ *) ; 
 struct mm_struct* this_cpu_read (int /*<<< orphan*/ ) ; 

void leave_mm(int cpu)
{
	struct mm_struct *loaded_mm = this_cpu_read(cpu_tlbstate.loaded_mm);

	/*
	 * It's plausible that we're in lazy TLB mode while our mm is init_mm.
	 * If so, our callers still expect us to flush the TLB, but there
	 * aren't any user TLB entries in init_mm to worry about.
	 *
	 * This needs to happen before any other sanity checks due to
	 * intel_idle's shenanigans.
	 */
	if (loaded_mm == &init_mm)
		return;

	/* Warn if we're not lazy. */
	WARN_ON(!this_cpu_read(cpu_tlbstate.is_lazy));

	switch_mm(NULL, &init_mm, NULL);
}