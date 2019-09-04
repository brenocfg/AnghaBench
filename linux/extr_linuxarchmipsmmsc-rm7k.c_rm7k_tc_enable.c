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
 int /*<<< orphan*/  BUG_ON (int) ; 
 int RM7K_CONF_TE ; 
 int /*<<< orphan*/  __rm7k_tc_enable ; 
 int read_c0_config () ; 
 int /*<<< orphan*/  run_uncached (int /*<<< orphan*/ ) ; 
 scalar_t__ tcache_size ; 

__attribute__((used)) static void rm7k_tc_enable(void)
{
	if (read_c0_config() & RM7K_CONF_TE)
		return;

	BUG_ON(tcache_size == 0);

	run_uncached(__rm7k_tc_enable);
}