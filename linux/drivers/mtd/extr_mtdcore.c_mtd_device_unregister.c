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
struct mtd_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  reboot_notifier; scalar_t__ _reboot; } ;

/* Variables and functions */
 int del_mtd_device (struct mtd_info*) ; 
 int del_mtd_partitions (struct mtd_info*) ; 
 int /*<<< orphan*/  device_is_registered (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_reboot_notifier (int /*<<< orphan*/ *) ; 

int mtd_device_unregister(struct mtd_info *master)
{
	int err;

	if (master->_reboot)
		unregister_reboot_notifier(&master->reboot_notifier);

	err = del_mtd_partitions(master);
	if (err)
		return err;

	if (!device_is_registered(&master->dev))
		return 0;

	return del_mtd_device(master);
}