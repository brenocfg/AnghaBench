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
 scalar_t__ cpum_cf_avail () ; 
 scalar_t__ cpum_sf_avail () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  print_debug_cf () ; 
 int /*<<< orphan*/  print_debug_sf () ; 

void perf_event_print_debug(void)
{
	unsigned long flags;

	local_irq_save(flags);
	if (cpum_cf_avail())
		print_debug_cf();
	if (cpum_sf_avail())
		print_debug_sf();
	local_irq_restore(flags);
}