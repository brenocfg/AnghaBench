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
struct loop_device {int /*<<< orphan*/  lo_disk; } ;
struct kobject {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int MINOR (int /*<<< orphan*/ ) ; 
 struct kobject* get_disk_and_module (int /*<<< orphan*/ ) ; 
 int loop_add (struct loop_device**,int) ; 
 int /*<<< orphan*/  loop_ctl_mutex ; 
 int loop_lookup (struct loop_device**,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int part_shift ; 

__attribute__((used)) static struct kobject *loop_probe(dev_t dev, int *part, void *data)
{
	struct loop_device *lo;
	struct kobject *kobj;
	int err;

	mutex_lock(&loop_ctl_mutex);
	err = loop_lookup(&lo, MINOR(dev) >> part_shift);
	if (err < 0)
		err = loop_add(&lo, MINOR(dev) >> part_shift);
	if (err < 0)
		kobj = NULL;
	else
		kobj = get_disk_and_module(lo->lo_disk);
	mutex_unlock(&loop_ctl_mutex);

	*part = 0;
	return kobj;
}