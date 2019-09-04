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
 int /*<<< orphan*/  RM7K_CONF_SE ; 
 int /*<<< orphan*/  clear_c0_config (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rm7k_tc_disable () ; 
 scalar_t__ rm7k_tcache_init ; 

__attribute__((used)) static void rm7k_sc_disable(void)
{
	clear_c0_config(RM7K_CONF_SE);

	if (rm7k_tcache_init)
		rm7k_tc_disable();
}