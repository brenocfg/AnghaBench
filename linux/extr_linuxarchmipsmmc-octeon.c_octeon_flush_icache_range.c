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
 int /*<<< orphan*/  octeon_flush_icache_all_cores (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void octeon_flush_icache_range(unsigned long start, unsigned long end)
{
	octeon_flush_icache_all_cores(NULL);
}