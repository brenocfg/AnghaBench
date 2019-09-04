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
 int /*<<< orphan*/  R4K_HIT ; 
 scalar_t__ in_atomic () ; 
 int /*<<< orphan*/  local_r4k_flush_data_cache_page (void*) ; 
 int /*<<< orphan*/  r4k_on_each_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (void*),void*) ; 

__attribute__((used)) static void r4k_flush_data_cache_page(unsigned long addr)
{
	if (in_atomic())
		local_r4k_flush_data_cache_page((void *)addr);
	else
		r4k_on_each_cpu(R4K_HIT, local_r4k_flush_data_cache_page,
				(void *) addr);
}