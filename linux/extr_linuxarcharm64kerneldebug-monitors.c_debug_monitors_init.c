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
 int /*<<< orphan*/  CPUHP_AP_ARM64_DEBUG_MONITORS_STARTING ; 
 int /*<<< orphan*/  clear_os_lock ; 
 int cpuhp_setup_state (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int debug_monitors_init(void)
{
	return cpuhp_setup_state(CPUHP_AP_ARM64_DEBUG_MONITORS_STARTING,
				 "arm64/debug_monitors:starting",
				 clear_os_lock, NULL);
}