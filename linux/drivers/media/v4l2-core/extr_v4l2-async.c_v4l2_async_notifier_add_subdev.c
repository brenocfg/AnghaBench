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
struct v4l2_async_subdev {int /*<<< orphan*/  asd_list; } ;
struct v4l2_async_notifier {int /*<<< orphan*/  asd_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int v4l2_async_notifier_asd_valid (struct v4l2_async_notifier*,struct v4l2_async_subdev*,int) ; 

int v4l2_async_notifier_add_subdev(struct v4l2_async_notifier *notifier,
				   struct v4l2_async_subdev *asd)
{
	int ret;

	mutex_lock(&list_lock);

	ret = v4l2_async_notifier_asd_valid(notifier, asd, -1);
	if (ret)
		goto unlock;

	list_add_tail(&asd->asd_list, &notifier->asd_list);

unlock:
	mutex_unlock(&list_lock);
	return ret;
}