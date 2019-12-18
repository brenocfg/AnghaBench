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
struct mapped_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 TYPE_1__* disk_to_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_disk (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_kobject (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_ktype ; 
 int kobject_init_and_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*) ; 

int dm_sysfs_init(struct mapped_device *md)
{
	return kobject_init_and_add(dm_kobject(md), &dm_ktype,
				    &disk_to_dev(dm_disk(md))->kobj,
				    "%s", "dm");
}