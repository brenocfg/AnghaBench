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
struct rvin_group {int /*<<< orphan*/  lock; int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  media_device_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rvin_group_cleanup(struct rvin_group *group)
{
	media_device_unregister(&group->mdev);
	media_device_cleanup(&group->mdev);
	mutex_destroy(&group->lock);
}