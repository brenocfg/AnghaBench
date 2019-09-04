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
struct devfreq_event_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  node; int /*<<< orphan*/  enable_count; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devfreq_event_list_lock ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int devfreq_event_remove_edev(struct devfreq_event_dev *edev)
{
	if (!edev)
		return -EINVAL;

	WARN_ON(edev->enable_count);

	mutex_lock(&devfreq_event_list_lock);
	list_del(&edev->node);
	mutex_unlock(&devfreq_event_list_lock);

	device_unregister(&edev->dev);

	return 0;
}