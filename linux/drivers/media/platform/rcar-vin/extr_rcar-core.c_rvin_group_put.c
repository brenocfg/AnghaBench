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
struct rvin_group {int /*<<< orphan*/  refcount; int /*<<< orphan*/  lock; struct rvin_dev** vin; } ;
struct TYPE_2__ {int /*<<< orphan*/ * mdev; } ;
struct rvin_dev {size_t id; TYPE_1__ v4l2_dev; struct rvin_group* group; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rvin_group_release ; 

__attribute__((used)) static void rvin_group_put(struct rvin_dev *vin)
{
	struct rvin_group *group = vin->group;

	mutex_lock(&group->lock);

	vin->group = NULL;
	vin->v4l2_dev.mdev = NULL;

	if (WARN_ON(group->vin[vin->id] != vin))
		goto out;

	group->vin[vin->id] = NULL;
out:
	mutex_unlock(&group->lock);

	kref_put(&group->refcount, rvin_group_release);
}