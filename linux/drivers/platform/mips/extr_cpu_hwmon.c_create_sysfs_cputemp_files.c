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
struct kobject {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * hwmon_cputemp ; 
 int nr_packages ; 
 int sysfs_create_files (struct kobject*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int create_sysfs_cputemp_files(struct kobject *kobj)
{
	int i, ret = 0;

	for (i=0; i<nr_packages; i++)
		ret = sysfs_create_files(kobj, hwmon_cputemp[i]);

	return ret;
}