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
struct dm_dev {int /*<<< orphan*/  name; int /*<<< orphan*/ * bdev; int /*<<< orphan*/  mode; } ;
struct table_device {struct dm_dev dm_dev; int /*<<< orphan*/  count; int /*<<< orphan*/  list; } ;
struct mapped_device {int /*<<< orphan*/  table_devices_lock; int /*<<< orphan*/  table_devices; int /*<<< orphan*/  numa_node_id; } ;
typedef  int /*<<< orphan*/  fmode_t ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct table_device* find_table_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_dev_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct table_device*) ; 
 struct table_device* kmalloc_node (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int open_table_device (struct table_device*,int /*<<< orphan*/ ,struct mapped_device*) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 

int dm_get_table_device(struct mapped_device *md, dev_t dev, fmode_t mode,
			struct dm_dev **result)
{
	int r;
	struct table_device *td;

	mutex_lock(&md->table_devices_lock);
	td = find_table_device(&md->table_devices, dev, mode);
	if (!td) {
		td = kmalloc_node(sizeof(*td), GFP_KERNEL, md->numa_node_id);
		if (!td) {
			mutex_unlock(&md->table_devices_lock);
			return -ENOMEM;
		}

		td->dm_dev.mode = mode;
		td->dm_dev.bdev = NULL;

		if ((r = open_table_device(td, dev, md))) {
			mutex_unlock(&md->table_devices_lock);
			kfree(td);
			return r;
		}

		format_dev_t(td->dm_dev.name, dev);

		refcount_set(&td->count, 1);
		list_add(&td->list, &md->table_devices);
	} else {
		refcount_inc(&td->count);
	}
	mutex_unlock(&md->table_devices_lock);

	*result = &td->dm_dev;
	return 0;
}