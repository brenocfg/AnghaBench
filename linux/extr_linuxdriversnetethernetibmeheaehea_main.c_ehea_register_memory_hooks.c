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
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int crash_shutdown_register (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehea_crash_handler ; 
 int ehea_create_busmap () ; 
 int /*<<< orphan*/  ehea_mem_nb ; 
 int /*<<< orphan*/  ehea_memory_hooks_registered ; 
 int /*<<< orphan*/  ehea_reboot_nb ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int register_memory_notifier (int /*<<< orphan*/ *) ; 
 int register_reboot_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_memory_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_reboot_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ehea_register_memory_hooks(void)
{
	int ret = 0;

	if (atomic_inc_return(&ehea_memory_hooks_registered) > 1)
		return 0;

	ret = ehea_create_busmap();
	if (ret) {
		pr_info("ehea_create_busmap failed\n");
		goto out;
	}

	ret = register_reboot_notifier(&ehea_reboot_nb);
	if (ret) {
		pr_info("register_reboot_notifier failed\n");
		goto out;
	}

	ret = register_memory_notifier(&ehea_mem_nb);
	if (ret) {
		pr_info("register_memory_notifier failed\n");
		goto out2;
	}

	ret = crash_shutdown_register(ehea_crash_handler);
	if (ret) {
		pr_info("crash_shutdown_register failed\n");
		goto out3;
	}

	return 0;

out3:
	unregister_memory_notifier(&ehea_mem_nb);
out2:
	unregister_reboot_notifier(&ehea_reboot_nb);
out:
	atomic_dec(&ehea_memory_hooks_registered);
	return ret;
}