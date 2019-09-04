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
 int /*<<< orphan*/  CPUHP_SH_SH3X_PREPARE ; 
 int /*<<< orphan*/  cpuhp_setup_state_nocalls (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shx3_cpu_prepare ; 

__attribute__((used)) static int register_shx3_cpu_notifier(void)
{
	cpuhp_setup_state_nocalls(CPUHP_SH_SH3X_PREPARE, "sh/shx3:prepare",
				  shx3_cpu_prepare, NULL);
	return 0;
}