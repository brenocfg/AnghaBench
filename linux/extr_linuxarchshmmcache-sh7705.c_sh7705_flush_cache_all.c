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
 int /*<<< orphan*/  back_to_cached () ; 
 int /*<<< orphan*/  cache_wback_all () ; 
 int /*<<< orphan*/  jump_to_uncached () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static void sh7705_flush_cache_all(void *args)
{
	unsigned long flags;

	local_irq_save(flags);
	jump_to_uncached();

	cache_wback_all();
	back_to_cached();
	local_irq_restore(flags);
}