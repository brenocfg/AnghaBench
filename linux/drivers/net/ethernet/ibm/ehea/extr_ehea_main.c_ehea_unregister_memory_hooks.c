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
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ crash_shutdown_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehea_crash_handler ; 
 int /*<<< orphan*/  ehea_mem_nb ; 
 int /*<<< orphan*/  ehea_memory_hooks_registered ; 
 int /*<<< orphan*/  ehea_reboot_nb ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  unregister_memory_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_reboot_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ehea_unregister_memory_hooks(void)
{
	/* Only remove the hooks if we've registered them */
	if (atomic_read(&ehea_memory_hooks_registered) == 0)
		return;

	unregister_reboot_notifier(&ehea_reboot_nb);
	if (crash_shutdown_unregister(ehea_crash_handler))
		pr_info("failed unregistering crash handler\n");
	unregister_memory_notifier(&ehea_mem_nb);
}