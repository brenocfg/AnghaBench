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
struct loopback_test {int device_count; int us_wait; int size; int iteration_max; int async_timeout; int async_outstanding_operations; TYPE_1__* devices; scalar_t__ use_async; scalar_t__ stop_all; } ;
struct TYPE_2__ {int /*<<< orphan*/  sysfs_entry; } ;

/* Variables and functions */
 scalar_t__ device_enabled (struct loopback_test*,int) ; 
 int /*<<< orphan*/  write_sysfs_val (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void prepare_devices(struct loopback_test *t)
{
	int i;

	/*
	 * Cancel any running tests on enabled devices. If
	 * stop_all option is given, stop test on all devices.
	 */
	for (i = 0; i < t->device_count; i++)
		if (t->stop_all || device_enabled(t, i))
			write_sysfs_val(t->devices[i].sysfs_entry, "type", 0);


	for (i = 0; i < t->device_count; i++) {
		if (!device_enabled(t, i))
			continue;

		write_sysfs_val(t->devices[i].sysfs_entry, "us_wait",
				t->us_wait);

		/* Set operation size */
		write_sysfs_val(t->devices[i].sysfs_entry, "size", t->size);

		/* Set iterations */
		write_sysfs_val(t->devices[i].sysfs_entry, "iteration_max",
				t->iteration_max);

		if (t->use_async) {
			write_sysfs_val(t->devices[i].sysfs_entry, "async", 1);
			write_sysfs_val(t->devices[i].sysfs_entry,
					"timeout", t->async_timeout);
			write_sysfs_val(t->devices[i].sysfs_entry,
					"outstanding_operations_max",
					t->async_outstanding_operations);
		} else
			write_sysfs_val(t->devices[i].sysfs_entry, "async", 0);
	}
}