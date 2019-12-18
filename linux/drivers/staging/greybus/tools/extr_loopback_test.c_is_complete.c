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
struct loopback_test {int device_count; int iteration_max; TYPE_1__* devices; } ;
struct TYPE_2__ {int /*<<< orphan*/  sysfs_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_enabled (struct loopback_test*,int) ; 
 int read_sysfs_int (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int is_complete(struct loopback_test *t)
{
	int iteration_count;
	int i;

	for (i = 0; i < t->device_count; i++) {
		if (!device_enabled(t, i))
			continue;

		iteration_count = read_sysfs_int(t->devices[i].sysfs_entry,
						 "iteration_count");

		/* at least one device did not finish yet */
		if (iteration_count != t->iteration_max)
			return 0;
	}

	return 1;
}