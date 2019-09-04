#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct fmc_device {TYPE_1__ dev; int /*<<< orphan*/  devarray; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_del (TYPE_1__*) ; 
 int /*<<< orphan*/  fmc_debug_exit (struct fmc_device*) ; 
 int /*<<< orphan*/  fmc_eeprom_attr ; 
 int /*<<< orphan*/  fmc_free_id_info (struct fmc_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int /*<<< orphan*/  sysfs_remove_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void fmc_device_unregister_n(struct fmc_device **devs, int n)
{
	int i;

	if (n < 1)
		return;

	/* Free devarray first, not used by the later loop */
	kfree(devs[0]->devarray);

	for (i = 0; i < n; i++) {
		fmc_debug_exit(devs[i]);
		sysfs_remove_bin_file(&devs[i]->dev.kobj, &fmc_eeprom_attr);
		device_del(&devs[i]->dev);
		fmc_free_id_info(devs[i]);
		put_device(&devs[i]->dev);
	}
}