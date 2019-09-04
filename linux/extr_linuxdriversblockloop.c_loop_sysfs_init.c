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
struct loop_device {int sysfs_inited; int /*<<< orphan*/  lo_disk; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 TYPE_1__* disk_to_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  loop_attribute_group ; 
 int /*<<< orphan*/  sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void loop_sysfs_init(struct loop_device *lo)
{
	lo->sysfs_inited = !sysfs_create_group(&disk_to_dev(lo->lo_disk)->kobj,
						&loop_attribute_group);
}