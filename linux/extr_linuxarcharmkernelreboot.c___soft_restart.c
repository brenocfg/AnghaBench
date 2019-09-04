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
typedef  int /*<<< orphan*/  (* phys_reset_t ) (unsigned long,int /*<<< orphan*/ ) ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  cpu_proc_fin () ; 
 int /*<<< orphan*/  cpu_reset ; 
 int /*<<< orphan*/  flush_cache_all () ; 
 int /*<<< orphan*/  is_hyp_mode_available () ; 
 int /*<<< orphan*/  setup_mm_for_reboot () ; 
 scalar_t__ virt_to_idmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __soft_restart(void *addr)
{
	phys_reset_t phys_reset;

	/* Take out a flat memory mapping. */
	setup_mm_for_reboot();

	/* Clean and invalidate caches */
	flush_cache_all();

	/* Turn off caching */
	cpu_proc_fin();

	/* Push out any further dirty data, and ensure cache is empty */
	flush_cache_all();

	/* Switch to the identity mapping. */
	phys_reset = (phys_reset_t)virt_to_idmap(cpu_reset);

	/* original stub should be restored by kvm */
	phys_reset((unsigned long)addr, is_hyp_mode_available());

	/* Should never get here. */
	BUG();
}