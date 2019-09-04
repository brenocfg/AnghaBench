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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUHP_AP_ARM_SDEI_STARTING ; 
 int NOTIFY_OK ; 
 int /*<<< orphan*/  cpuhp_remove_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdei_platform_reset () ; 

__attribute__((used)) static int sdei_reboot_notifier(struct notifier_block *nb, unsigned long action,
				void *data)
{
	/*
	 * We are going to reset the interface, after this there is no point
	 * doing work when we take CPUs offline.
	 */
	cpuhp_remove_state(CPUHP_AP_ARM_SDEI_STARTING);

	sdei_platform_reset();

	return NOTIFY_OK;
}