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
 unsigned long __pa_symbol (void*) ; 
 unsigned long** mcpm_entry_vectors ; 
 int /*<<< orphan*/  sync_cache_w (unsigned long*) ; 

void mcpm_set_entry_vector(unsigned cpu, unsigned cluster, void *ptr)
{
	unsigned long val = ptr ? __pa_symbol(ptr) : 0;
	mcpm_entry_vectors[cluster][cpu] = val;
	sync_cache_w(&mcpm_entry_vectors[cluster][cpu]);
}