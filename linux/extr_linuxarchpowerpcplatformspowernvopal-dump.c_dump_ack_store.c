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
struct dump_obj {int /*<<< orphan*/  kobj; int /*<<< orphan*/  id; } ;
struct dump_attribute {int /*<<< orphan*/  attr; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  dump_send_ack (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_file_self (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t dump_ack_store(struct dump_obj *dump_obj,
			      struct dump_attribute *attr,
			      const char *buf,
			      size_t count)
{
	dump_send_ack(dump_obj->id);
	sysfs_remove_file_self(&dump_obj->kobj, &attr->attr);
	kobject_put(&dump_obj->kobj);
	return count;
}