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
struct mapped_device {int dummy; } ;
struct file {int dummy; } ;
struct dm_table {int dummy; } ;
struct dm_ioctl {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  __dev_status (struct mapped_device*,struct dm_ioctl*) ; 
 struct dm_table* dm_get_live_or_inactive_table (struct mapped_device*,struct dm_ioctl*,int*) ; 
 int /*<<< orphan*/  dm_put (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_put_live_table (struct mapped_device*,int) ; 
 struct mapped_device* find_device (struct dm_ioctl*) ; 
 int /*<<< orphan*/  retrieve_deps (struct dm_table*,struct dm_ioctl*,size_t) ; 

__attribute__((used)) static int table_deps(struct file *filp, struct dm_ioctl *param, size_t param_size)
{
	struct mapped_device *md;
	struct dm_table *table;
	int srcu_idx;

	md = find_device(param);
	if (!md)
		return -ENXIO;

	__dev_status(md, param);

	table = dm_get_live_or_inactive_table(md, param, &srcu_idx);
	if (table)
		retrieve_deps(table, param, param_size);
	dm_put_live_table(md, srcu_idx);

	dm_put(md);

	return 0;
}