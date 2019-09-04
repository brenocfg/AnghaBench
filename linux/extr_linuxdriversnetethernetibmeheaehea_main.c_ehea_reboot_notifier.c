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
 int NOTIFY_DONE ; 
 unsigned long SYS_RESTART ; 
 int /*<<< orphan*/  ehea_driver ; 
 int /*<<< orphan*/  ibmebus_unregister_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static int ehea_reboot_notifier(struct notifier_block *nb,
				unsigned long action, void *unused)
{
	if (action == SYS_RESTART) {
		pr_info("Reboot: freeing all eHEA resources\n");
		ibmebus_unregister_driver(&ehea_driver);
	}
	return NOTIFY_DONE;
}