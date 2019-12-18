#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct knav_pool {int /*<<< orphan*/  name; int /*<<< orphan*/  list; int /*<<< orphan*/  region_inst; scalar_t__ num_desc; TYPE_1__* region; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  used_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct knav_pool*) ; 
 int /*<<< orphan*/  kdesc_empty_pool (struct knav_pool*) ; 
 TYPE_2__* kdev ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  knav_dev_lock ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void knav_pool_destroy(void *ph)
{
	struct knav_pool *pool = ph;

	if (!pool)
		return;

	if (!pool->region)
		return;

	kdesc_empty_pool(pool);
	mutex_lock(&knav_dev_lock);

	pool->region->used_desc -= pool->num_desc;
	list_del(&pool->region_inst);
	list_del(&pool->list);

	mutex_unlock(&knav_dev_lock);
	kfree(pool->name);
	devm_kfree(kdev->dev, pool);
}