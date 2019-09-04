#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dcdbas_attr_group ; 
 int /*<<< orphan*/  dcdbas_reboot_nb ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_reboot_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dcdbas_remove(struct platform_device *dev)
{
	unregister_reboot_notifier(&dcdbas_reboot_nb);
	sysfs_remove_group(&dev->dev.kobj, &dcdbas_attr_group);

	return 0;
}