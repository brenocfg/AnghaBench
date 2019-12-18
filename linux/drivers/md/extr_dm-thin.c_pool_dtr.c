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
struct pool_c {int /*<<< orphan*/  data_dev; int /*<<< orphan*/  metadata_dev; int /*<<< orphan*/  pool; } ;
struct dm_target {struct pool_c* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  __pool_dec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_put_device (struct dm_target*,int /*<<< orphan*/ ) ; 
 TYPE_1__ dm_thin_pool_table ; 
 int /*<<< orphan*/  kfree (struct pool_c*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unbind_control_target (int /*<<< orphan*/ ,struct dm_target*) ; 

__attribute__((used)) static void pool_dtr(struct dm_target *ti)
{
	struct pool_c *pt = ti->private;

	mutex_lock(&dm_thin_pool_table.mutex);

	unbind_control_target(pt->pool, ti);
	__pool_dec(pt->pool);
	dm_put_device(ti, pt->metadata_dev);
	dm_put_device(ti, pt->data_dev);
	kfree(pt);

	mutex_unlock(&dm_thin_pool_table.mutex);
}