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
 int /*<<< orphan*/  cpu_has_dc_aliases ; 
 int /*<<< orphan*/  tx39_blast_dcache () ; 

__attribute__((used)) static inline void tx39_flush_cache_all(void)
{
	if (!cpu_has_dc_aliases)
		return;

	tx39_blast_dcache();
}