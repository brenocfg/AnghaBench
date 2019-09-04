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
 int /*<<< orphan*/  firmware_kobj ; 
 int /*<<< orphan*/  memconsole_bin_attr ; 
 int /*<<< orphan*/  sysfs_remove_bin_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void memconsole_exit(void)
{
	sysfs_remove_bin_file(firmware_kobj, &memconsole_bin_attr);
}